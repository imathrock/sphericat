#include "matrix\matrix.hpp"
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <iomanip>

float potential(float x) {
    return x * x;
}
#define M_PI 3.141596
using namespace std;

void print_eigen(eigen& A){
    cout << "=========Eigenvalues==========\n";
    int size = A.eigenvalues.size();
    for(int i = 0; i < size; i++){ cout << A.eigenvalues[i] << "\n"; }
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

void compare_eigenvalues(const fvec& expected, const fvec& calculated, int M) {
    cout << setw(20) << "Expected" << setw(20) << "Calculated" << setw(20) << "Error\n";
    cout << string(60, '-') << "\n";
    for(int i = 0; i < M; i++) {
        float error = abs(expected[i] - calculated[i]);
        cout << setw(20) << expected[i] 
             << setw(20) << calculated[i] 
             << setw(20) << error << "\n";
    }
}

int main(){
    cout << "=== Arnoldi Tests (M < 10) ===\n\n";
    
    // Test 1: 500x500 diagonal matrix, find 5 largest eigenvalues
    cout << "Test 1: 500x500 Diagonal Matrix (M=5)\n";
    cout << "Finding 5 largest eigenvalues\n";
    tridiag T1(1000);
    for(int i = 0; i < 1000; i++) T1.diag[i] = (float)(i + 1);
    arnoldi ar1(100, T1);
    ar1 = Arnoldi(100, T1, ar1);
    eigen e1 = QR_algorithm(ar1.H);
    fvec expected1 = {1000.0f, 999.0f, 998.0f, 997.0f, 996.0f};
    compare_eigenvalues(expected1, e1.eigenvalues, 5);
    
    // Test 2: 300x300 tridiagonal, M=6
    cout << "\nTest 2: 300x300 Tridiagonal Matrix (M=6)\n";
    cout << "Diagonal: 2, Off-diagonal: -1\n";
    tridiag T2(300);
    for(int i = 0; i < 300; i++) T2.diag[i] = 2.0f;
    for(int i = 0; i < 299; i++) { T2.subdiag[i] = -1.0f; T2.supdiag[i] = -1.0f; }
    arnoldi ar2(100, T2);
    ar2 = Arnoldi(100, T2, ar2);
    eigen e2 = QR_algorithm(ar2.H);
    // Expected: 2 - 2*cos(k*pi/(N+1)) for k=N, N-1, N-2... (largest)
    fvec expected2(6);
    for(int k = 0; k < 6; k++) {
        expected2[k] = 2.0f - 2.0f * cos((300 - k) * M_PI / 301.0f);
    }
    compare_eigenvalues(expected2, e2.eigenvalues, 6);
    
    // Test 3: 200x200 tridiagonal, M=8
    cout << "\nTest 3: 200x200 Tridiagonal Matrix (M=8)\n";
    cout << "Diagonal: 4, Off-diagonal: 1\n";
    tridiag T3(200);
    for(int i = 0; i < 200; i++) T3.diag[i] = 4.0f;
    for(int i = 0; i < 199; i++) { T3.subdiag[i] = 1.0f; T3.supdiag[i] = 1.0f; }
    arnoldi ar3(8, T3);
    ar3 = Arnoldi(8, T3, ar3);
    eigen e3 = QR_algorithm(ar3.H);
    // Expected: 4 + 2*cos(k*pi/(N+1)) for k=1,2,3... (largest first)
    fvec expected3(8);
    for(int k = 1; k <= 8; k++) {
        expected3[k-1] = 4.0f + 2.0f * cos(k * M_PI / 201.0f);
    }
    compare_eigenvalues(expected3, e3.eigenvalues, 8);
    
    // Test 4: 500x500 tridiagonal, M=9
    cout << "\nTest 4: 500x500 Tridiagonal Matrix (M=9)\n";
    cout << "Diagonal: -2, Off-diagonal: 1\n";
    tridiag T4(500);
    for(int i = 0; i < 500; i++) T4.diag[i] = -2.0f;
    for(int i = 0; i < 499; i++) { T4.subdiag[i] = 1.0f; T4.supdiag[i] = 1.0f; }
    arnoldi ar4(49, T4);
    ar4 = Arnoldi(49, T4, ar4);
    eigen e4 = QR_algorithm(ar4.H);
    // Expected: -2 + 2*cos(k*pi/(N+1)) for k=1,2,3... (largest first)
    fvec expected4(9);
    for(int k = 1; k <= 9; k++) {
        expected4[k-1] = -2.0f + 2.0f * cos(k * M_PI / 501.0f);
    }
    compare_eigenvalues(expected4, e4.eigenvalues, 9);

    cout << "\ndone\n";
}