#include "matrix\matrix.hpp"
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <iomanip>

float potential(float x) {
    return x * x;
}

using namespace std;

void print_eigen(eigen& A){
    cout << "=========Eigenvalues==========\n";
    for(int i = 0; i < A.eigenvalues.size(); i++){ cout << A.eigenvalues[i] << "\n"; }
}

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

int main(){
    int N = 5;
    matrix A(N,N);

    for(int i = 0; i< N; i++){ A.at(i,i) = i; }
    eigen eigen = QR_algorithm(A);
    print_eigen(eigen);
    
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            if (i == j) A.at(i, j) = 2.0f;
            else if (abs(i - j) == 1) A.at(i, j) = -1.0f;
            else A.at(i, j) = 0.0f;
        }
    }
    eigen = QR_algorithm(A);
    print_eigen(eigen);
    
    // All 1s Matrix (Outer product of vector of 1s)
    // Size N = 5
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            A.at(i, j) = 1.0f; 
        }
    }
    eigen = QR_algorithm(A);
    print_eigen(eigen);
    
    // Size N = 5
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            if (i == j) {
                A.at(i, j) = (float)(i + 1); // Diagonal: 1, 2, 3, 4, 5
            } else if (j > i) {
                A.at(i, j) = 1.0f; // Fill upper triangle with dummy 1s
            } else {
                A.at(i, j) = 0.0f; // strictly lower triangular is 0
            }
        }
    }

    eigen = QR_algorithm(A);
    print_eigen(eigen);


    cout << "done\n";
}