#include "matrix\matrix.hpp"
#include <cstdlib>
#include <ctime>
#include "clankerfuncs.h"

using namespace std;
// Testing simple matricies
int main(){
    int N = 50;
    matrix A(N,N);
    matrix B(N,N);
    for(int i = 0; i< N; i++){        
        for(int j = 0; j< N; j++){
            A.at(i,j) = i+j; 
            if (i == j) A.at(i,j) += N; // Diagonal Dominance -> Full Rank
        }
    }
    matrix c = mul(A,A);
    cout << norm(c) << "\n";
    QR_thin qr = QR_algorithm(c);
    // print_matrix(qr.Q);
    matrix QT = Transpose(qr.Q);
    B = mul(c,QT);
    B = mul(qr.Q,B);
    print_matrix(B); 
    cout << "done\n";
}