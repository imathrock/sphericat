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

#endif