#ifndef CLANKER_H
#define CLANKER_H
#include<cmath>
#include<iostream>
#include<vector>
#include<cstdlib>
#include <iomanip>
#include "matrix\matrix.hpp"

void print_matrix(const matrix& A) {
    for (int r = 0; r < A.rows; r++) {
        std::cout << "[ ";
        for (int c = 0; c < A.cols; c++) {
            // Access is at(col, row)
            std::cout << A.at(c, r) << "\t";
        }
        std::cout << "]\n";
    }
    std::cout << "\n";
}

void print_eigen(const eigen& e) {
    std::cout << "\n=== EIGEN DECOMPOSITION RESULTS ===\n";
    for (size_t i = 0; i < e.eigenvalues.size(); i++) {
        std::cout << "Mode " << i << ":\n";
        std::cout << "  Eigenvalue: " << e.eigenvalues[i] << "\n";
        std::cout << "  Eigenvector: [ ";
        for (float val : e.eigenvectors[i]) {
            std::cout << val << " ";
        }
        std::cout << "]\n\n";
    }
}
void print_T_matrix(const tri_diag_matrix& m) {
    int N = m.diag.size();
    std::cout << std::fixed << std::setprecision(1);
    for (int r = 0; r < N; ++r) {
        std::cout << "[";
        for (int c = 0; c < N; ++c) {
            float val = 0.0f;
            if (r == c) val = m.diag[r];
            else if (r == c + 1) val = m.sub_diag[c];
            else if (c == r + 1) val = m.sup_diag[r];
            std::cout << std::setw(2) << val << ",";
        }
        std::cout << "]\n";
    }
}

// ----- Arnoldi tests -----
void print_Arnoldi(const Arnoldi_matrices& arn) {
    std::cout << "=== Arnoldi Q (orthonormal basis, " << arn.Q.rows << " x " << arn.Q.cols << ") ===\n";
    print_matrix(arn.Q);
    std::cout << "=== Arnoldi H (upper Hessenberg, " << arn.H.rows << " x " << arn.H.cols << ") ===\n";
    print_matrix(arn.H);
}

void test_Arnoldi_orthogonality(const Arnoldi_matrices& arn) {
    const int M = arn.Q.cols;
    float max_off = 0.0f, max_diag_err = 0.0f;
    for (int i = 0; i < M; i++) {
        fvec qi = getcol(const_cast<matrix&>(arn.Q), i);
        for (int j = 0; j < M; j++) {
            fvec qj = getcol(const_cast<matrix&>(arn.Q), j);
            float d = dot(qi, qj);
            if (i == j) max_diag_err = std::max(max_diag_err, std::abs(d - 1.0f));
            else max_off = std::max(max_off, std::abs(d));
        }
    }
    std::cout << "[Arnoldi orthogonality] max |Q^T Q - I|_diag " << max_diag_err << ", max off-diag " << max_off << "\n";
}

void test_Arnoldi_relation(tri_diag_matrix& A, Arnoldi_matrices& arn) {
    const int M = arn.Q.cols, N = arn.Q.rows;
    matrix AQ(M, N), QH(M, N);
    for (int j = 0; j < M; j++) {
        fvec qj = getcol(arn.Q, j);
        fvec aqj = TDmat_vec_mul(A, qj);
        for (int r = 0; r < N; r++) AQ.at(j, r) = aqj[r];
    }
    QH = mul(arn.Q, arn.H);
    float max_res = 0.0f;
    for (int c = 0; c < M; c++)
        for (int r = 0; r < N; r++)
            max_res = std::max(max_res, std::abs(AQ.at(c, r) - QH.at(c, r)));
    std::cout << "[Arnoldi relation A*Q ~ Q*H] max |A*Q - Q*H| " << max_res << "\n";
}

// ----- Lanczos tests -----
void print_Lanczos(const Lanczos_result& lanc) {
    std::cout << "=== Lanczos Q (" << lanc.Q.rows << " x " << lanc.Q.cols << ") ===\n";
    print_matrix(lanc.Q);
    std::cout << "=== Lanczos T (alpha, beta) ===\n";
    std::cout << "  alpha: ";
    for (size_t i = 0; i < lanc.alpha.size(); i++) std::cout << lanc.alpha[i] << " ";
    std::cout << "\n  beta:  ";
    for (size_t i = 0; i < lanc.beta.size(); i++) std::cout << lanc.beta[i] << " ";
    std::cout << "\n";
    int M = static_cast<int>(lanc.alpha.size());
    if (M <= 10) {
        std::cout << "  T matrix:\n";
        for (int r = 0; r < M; r++) {
            std::cout << "  [";
            for (int c = 0; c < M; c++) {
                float val = 0.0f;
                if (r == c) val = lanc.alpha[c];
                else if (r == c + 1) val = lanc.beta[c];
                else if (c == r + 1) val = lanc.beta[r];
                std::cout << std::setw(8) << std::setprecision(4) << val << " ";
            }
            std::cout << "]\n";
        }
    }
}

void test_Lanczos_orthogonality(const Lanczos_result& lanc) {
    const int M = lanc.Q.cols;
    float max_off = 0.0f, max_diag_err = 0.0f;
    for (int i = 0; i < M; i++) {
        fvec qi = getcol(const_cast<matrix&>(lanc.Q), i);
        for (int j = 0; j < M; j++) {
            fvec qj = getcol(const_cast<matrix&>(lanc.Q), j);
            float d = dot(qi, qj);
            if (i == j) max_diag_err = std::max(max_diag_err, std::abs(d - 1.0f));
            else max_off = std::max(max_off, std::abs(d));
        }
    }
    std::cout << "[Lanczos orthogonality] max |Q^T Q - I|_diag " << max_diag_err << ", max off-diag " << max_off << "\n";
}

void test_Lanczos_relation(tri_diag_matrix& A, Lanczos_result& lanc) {
    const int M = lanc.Q.cols, N = lanc.Q.rows;
    matrix AQ(M, N), QT(M, N);
    for (int j = 0; j < M; j++) {
        fvec qj = getcol(lanc.Q, j);
        fvec aqj = TDmat_vec_mul(A, qj);
        for (int r = 0; r < N; r++) AQ.at(j, r) = aqj[r];
    }
    for (int j = 0; j < M; j++) {
        for (int r = 0; r < N; r++) {
            float v = lanc.alpha[j] * lanc.Q.at(j, r);
            if (j > 0) v += lanc.beta[j - 1] * lanc.Q.at(j - 1, r);
            if (j < M - 1) v += lanc.beta[j] * lanc.Q.at(j + 1, r);
            QT.at(j, r) = v;
        }
    }
    float max_res = 0.0f;
    for (int c = 0; c < M; c++)
        for (int r = 0; r < N; r++)
            max_res = std::max(max_res, std::abs(AQ.at(c, r) - QT.at(c, r)));
    std::cout << "[Lanczos relation A*Q ~ Q*T] max |A*Q - Q*T| " << max_res << "\n";
}

#endif