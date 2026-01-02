#include "matrix\matrix.hpp"
#include <cstdlib>
#include <ctime>
#include <iomanip>

//--------------------------------------------------------------------------------------//
//                        Start of CLANKER functions                                    //
//--------------------------------------------------------------------------------------//

void print_matrix(matrix& m) {
    // Usually we print row by row, but your storage seems to be column-major 
    // (at(i,k) is col i, row k). Let's print normally (Rows then Cols).
    for(int k = 0; k < m.rows; k++) {
        std::cout << "[ ";
        for(int i = 0; i < m.cols; i++) {
            std::cout << std::fixed << std::setprecision(4) << m.at(i,k) << " ";
        }
        std::cout << "]\n";
    }
    std::cout << "\n";
}

void check_QR(matrix& A, matrix& Q, matrix& R) {
    std::cout << "--- Correctness Check (A vs Q*R) ---\n";
    // Reconstruct A_prime = Q * R
    // Q is (Rows x Cols), R is (Cols x Cols) -> Result (Rows x Cols)
    
    float error_sum = 0.0f;

    for (int r = 0; r < A.rows; r++) { // Iterate rows of result
        for (int c = 0; c < A.cols; c++) { // Iterate cols of result
            float val = 0.0f;
            // Matrix Multiply: Row r of Q * Col c of R
            for (int k = 0; k < A.cols; k++) {
                // Q.at(col, row) accessing
                val += Q.at(k, r) * R.at(k, c); // Note R indices: R stored as at(col, row)? 
                // Based on your code R.at(j,i), R is likely stored as at(col, row) as well.
            }
            
            float original = A.at(c, r);
            float diff = std::abs(original - val);
            error_sum += diff;
        }
    }
    
    std::cout << "Total Reconstruction Error: " << error_sum << "\n";
    if(error_sum < 1e-4) std::cout << ">> SUCCESS: Decomposition is valid.\n";
    else std::cout << ">> FAILURE: Error too high.\n";
}

//--------------------------------------------------------------------------------------//
//                          END of CLANKER functions                                    //
//--------------------------------------------------------------------------------------//

using namespace std;
// Testing simple matricies
int main(){
    matrix A(5,5);
    matrix B(5,5);
    for(int i = 0; i< 5; i++){        
        for(int j = 0; j< 5; j++){
            A.at(i,j) = i+j;
            B.at(i,j) = i+j;
        }
    }
    matrix c = mul(A,B);
    cout << norm(c) << "\n";
    QR_thin qr(c);
    print_matrix(qr.Q);
    print_matrix(qr.R);
    check_QR(c,qr.Q,qr.R);
    cout << "done\n";
}