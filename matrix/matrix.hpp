#ifndef MATRIX_H
#define MATRIX_H

#include<cmath>
#include<iostream>
#include<vector>
#include<cstdlib>


// Column major format
struct matrix{
    int cols, rows, size;
    std::vector<float> data;

    matrix(int c, int r) : cols(c), rows(r), size(r*c), data(c*r,0.0f){}

    inline float& at(int c, int r){
        return data[c*rows+r];
    }
    inline const float& at(int c, int r) const{
        return data[c*rows+r];
    }

    /*
        Probably can write a at_transpose function that returns value at transposed index to prevent memory allocation. 
    */
};

  //------------//
 // A = A op B //
//------------//
void add_ip(matrix& A,matrix& B);
void sub_ip(matrix& A,matrix& B);

  //------------//
 // C = A op B //
//------------//
matrix add(matrix& A,matrix& B);
matrix sub(matrix& A,matrix& B);

  //------------//
 // C = A x B  //
//------------//
matrix mul(matrix& A,matrix& B);

// Normalization function, returns norm of the whole matrix, Vectorized for performance
float norm(matrix& M);

//-----------------------//
//   QR decomposition    //
//-----------------------//
inline float dotprod(matrix&a, matrix&b, int i, int j){
    float res = 0; 
    for(int k = 0; k < b.rows; k++){ res += a.at(i,k)*b.at(j,k); }
    return res;
}

inline float vecnorm(matrix&a, int i){
    float res = 0.0f;
    for(int k = 0; k < a.rows; k++){ res += a.at(i,k)*a.at(i,k); }
    res = sqrt(res);
    float div = 1/res;
    for(int k = 0; k < a.rows; k++){ a.at(i,k) *= div; }
    return res;
}

inline void subvecs(matrix&a, int i, int j, float scale){
    for(int k = 0; k < a.rows; k++){ a.at(i,k) -= a.at(j,k)*scale; }
}

struct QR_thin {
    matrix Q, R;
    QR_thin(matrix& A) : Q(A.cols, A.rows) , R(A.cols, A.cols) {
        for(int i = 0; i < A.cols; i++){

            for(int k = 0; k < A.rows; k++) { Q.at(i,k) = A.at(i,k);}

            for(int j = 0; j < i; j++){
                float dot = dotprod(Q, Q, j, i);
                R.at(j,i) = dot;
                subvecs(Q,i,j,dot);
            }
            R.at(i,i) = vecnorm(Q, i);
        }
    }
};

bool allclose(matrix&A, matrix& B);

void QR_decompose(QR_thin& QR, matrix& A);

QR_thin QR_algorithm(matrix&A);

matrix Transpose(matrix& A);

struct eigen{
    std::vector<float> eigenvalues;
    std::vector<std::vector<float>> eigenvectors;
    eigen(matrix& A) {
        QR_thin qr = QR_algorithm(A);
        matrix QT = Transpose(qr.Q);
        eigenvalues.resize(A.cols);
        eigenvectors.resize(A.cols, std::vector<float>(A.cols));
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

#endif