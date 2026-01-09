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
    // Rely on diag size for the dimension N
    int N = m.diag.size(); 

    std::cout << std::fixed << std::setprecision(1); // formatting

    for (int r = 0; r < N; ++r) {
        std::cout << "[";
        for (int c = 0; c < N; ++c) {
            float val = 0.0f;

            if (r == c) {
                // Main Diagonal
                val = m.diag[r];
            } 
            else if (r == c + 1) {
                // Sub-diagonal (Lower) -> usually mapped to index c
                val = m.sub_diag[c]; 
            } 
            else if (c == r + 1) {
                // Super-diagonal (Upper) -> usually mapped to index r
                val = m.sup_diag[r]; 
            }

            std::cout << std::setw(2) << val << ",";
        }
        std::cout << "]\n";
    }
}

#endif