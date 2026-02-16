#ifndef MATRIX_H
#define MATRIX_H

#include <cmath>
#include <iostream>
#include <vector>

typedef std::vector<float> fvec;

struct matrix {
    int cols, rows;
    fvec data;

    matrix(int c, int r) : cols(c), rows(r), data(c * r, 0.0f) {}

    inline float& at(int c, int r) { return data[c * rows + r]; }
    inline const float& at(int c, int r) const { return data[c * rows + r]; }
};

struct tridiag {
    int size, cols, rows;
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

// =============================================================================
// From Archive: additional functions and structs to port (headers in commented form)
// =============================================================================
// Total: 10 free functions + 7 inline/helpers + 4 structs (21 items)
// Naming: Archive used tri_diag_matrix → current type is tridiag.
// -----------------------------------------------------------------------------
// In-place matrix ops (A = A op B)
// void add_ip(matrix& A, matrix& B);
// void sub_ip(matrix& A, matrix& B);
// -----------------------------------------------------------------------------
// Norms (in-place normalize; return norm)
// float norm(matrix& M);       // Frobenius; normalizes M
// float normvec(fvec& v);     // L2; normalizes v
// -----------------------------------------------------------------------------
// Hamiltonian (1D finite-difference TISE)
// tridiag generate_hamiltonian(int size, float L, float offset, float (*potential)(float));
// -----------------------------------------------------------------------------
// QR and eigensolver
// float dotprod(matrix& a, matrix& b, int i, int j);   // dot of column i of a, column j of b
// float vecnorm(matrix& a, int i);                     // normalize column i of a, return norm
// void subvecs(matrix& a, int i, int j, float scale); // column i -= scale * column j
// struct QR_thin { matrix Q, R; QR_thin(matrix& A); };
// bool allclose(matrix& A, matrix& B);
// void QR_decompose(QR_thin& QR, matrix& A);
// QR_thin QR_algorithm(matrix& A);
// matrix Transpose(matrix& A);
// struct eigen { fvec eigenvalues; std::vector<fvec> eigenvectors; eigen(matrix& A); };
// -----------------------------------------------------------------------------
// Vector helpers and tridiag matvec alias
// fvec randvector(int N);
// void scale_fvec(float f, fvec& v);
// void append_mtx(matrix& Q, fvec f, int col);         // copy f into column col of Q
// fvec getcol(matrix& Q, int col);                     // return column col as fvec
// void subfvecs(fvec& f, const fvec& g, float scale);  // f -= scale * g
// fvec TDmat_vec_mul(tridiag& A, fvec q);             // same as mul(tridiag&, fvec&)
// -----------------------------------------------------------------------------
// Krylov solvers (need randvector, getcol, append_mtx, subfvecs, normvec, TDmat_vec_mul / mul(tridiag, fvec))
// struct Arnoldi_matrices { matrix Q, H; Arnoldi_matrices(int M, tridiag& A); };
// struct Lanczos_result { matrix Q; fvec alpha; fvec beta; Lanczos_result(int M, tridiag& A); };
// =============================================================================

#endif
