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
