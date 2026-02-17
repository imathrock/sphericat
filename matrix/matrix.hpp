#ifndef MATRIX_H
#define MATRIX_H

#include <cmath>
#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <random>

typedef std::vector<float> fvec;

struct matrix {
    int cols, rows, size;
    fvec data;
    
    matrix(int c, int r) : cols(c), rows(r), size(c * r), data(c * r, 0.0f) {}
    
    inline float& at(int c, int r) { return data[c * rows + r]; }
    inline const float& at(int c, int r) const { return data[c * rows + r]; }
};

struct tridiag {
    int cols, rows, size;
    fvec diag;
    fvec subdiag;
    fvec supdiag;
    float zero_ret = 0.0f;
    
    tridiag(int N) : cols(N), rows(N), size(N * N), diag(N, 0.0f), subdiag(N - 1, 0.0f), supdiag(N - 1, 0.0f) {}
    
    inline float& at(int c, int r) {
        if (c == r) return diag[c];
        if (c == r + 1) return subdiag[r];
        if (c + 1 == r) return supdiag[c];
        return zero_ret;
    }
    inline const float at(int c, int r) const {
        if (c == r) return diag[c];
        if (c == r + 1) return subdiag[r];
        if (c + 1 == r) return supdiag[c];
        return 0.0f;
    }
};

typedef std::vector<float> fvec;
typedef std::pair<float*, int> colview;
inline colview col(matrix& A, int j) { return { A.data.data() + j * A.rows, A.rows }; }
inline float dot(colview a, colview b) {
    float s = 0;
    for (int i = 0; i < a.second; i++) s += a.first[i] * b.first[i];
    return s;
}
// Matrix add/sub/mul
matrix add(matrix& A, matrix& B);
matrix sub(matrix& A, matrix& B);
matrix mul(matrix& A, matrix& B);

// In-place add/sub on matrix columns (a.col(i) += scale * a.col(j) etc.)
void add(matrix& a, int i, int j, float scale);
void sub(matrix& a, int i, int j, float scale);

// Vector add/sub
fvec add(fvec& A, fvec& B);
fvec sub(fvec& A, fvec& B);

// Matrix-vector and tridiag-vector
fvec mul(matrix& A, fvec& B);
fvec mul(tridiag& A, fvec& B);

// Dot products
float dot(matrix& A, matrix& B, int i, int j);
float dot(fvec& A, fvec& B);

// Norms (matrix: Frobenius, in-place normalize; vector: L2, optional normalize; column: normalize column i)
float norm(matrix& M);
float norm(fvec& v, bool normalize);
float norm(matrix& a, int i);

// Utilities
fvec randvector(int N);
bool allclose(matrix& A, matrix& B);

tridiag generate_hamiltonian(int size, float L, float offset, float (*potential)(float));

// -----------------------------------------------------------------------------
// Yet to implement
// -----------------------------------------------------------------------------
// 1D TISE Hamiltonian (finite difference)

// QR decomposition and eigensolver
struct QR_thin {
    matrix Q, R;
    QR_thin(matrix& A) : Q(A.cols, A.rows) , R(A.cols, A.cols){
        std::copy(A.data.begin(),A.data.end(), Q.data.begin());
        for(int i = 0; i < A.cols; i++){
            for(int j = 0; j < i; j++){
                float dotval = dot(Q, Q, j, i);
                R.at(j,i) = dotval;
                sub(Q,i,j,dotval);
            }
            float normval = norm(Q, i);
            R.at(i,i) = normval;
        }
    }
};

void QR_decompose(QR_thin& QR, matrix& A);

QR_thin QR_algorithm(matrix& A);

struct eigen {
    fvec eigenvalues;
    std::vector<fvec> eigenvectors;
    eigen(matrix& A){
        QR_thin qr = QR_algorithm(A);
        matrix QT = Transpose(qr.Q);
        eigenvalues.resize(A.cols);
        eigenvectors.resize(A.cols, fvec(A.cols));
        matrix B = mul(A,QT);
        B = mul(qr.Q,B);
        for(int i = 0; i < B.cols; i++){ eigenvalues[i] = B.at(i,i); }
        for(int i = 0; i < qr.Q.cols; i++){
            for(int j = 0; j < qr.Q.rows; j++){
                eigenvectors[i][j] = qr.Q.at(i,j);
            }
        }
    }
};

// Vector / matrix helpers
void scale_fvec(float f, fvec& v);
void append_mtx(matrix& Q, fvec f, int col);
fvec getcol(matrix& Q, int col);
void subfvecs(fvec& f, const fvec& g, float scale);

// Krylov solvers
struct Arnoldi_matrices {
    matrix Q, H;
    Arnoldi_matrices(int M, tridiag& A);
};
struct Lanczos_result {
    matrix Q;
    fvec alpha, beta;
    Lanczos_result(int M, tridiag& A);
};

#endif
