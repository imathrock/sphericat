#include "matrix\matrix.hpp"
#include <cstdlib>
#include <ctime>
#include "clankerfuncs.h"

float potential(float x){
    return x*x;
}
using namespace std;
// Testing simple matricies
int main(){
    int N = 100;
    // int M = 5;
    
    tri_diag_matrix A = generate_hamiltonian(N, 5.0f, 2.5f, potential);
    
    cout << "=== Original Tridiagonal Matrix A ===\n";
    // print_T_matrix(A);
    cout << "\n";
    
    cout << "=== random vector ===\n";
    fvec v = randvector(N);
    for(int i = 0; i< N; i++){
        cout<< v[i] <<"\n";
    }
    cout << "=== Post transformation vector ===\n";
    fvec w = TDmat_vec_mul(A,v);
    for(int i = 0; i< N; i++){
        cout<< w[i] <<"\n";
    }

    

    // cout << "=== Running Arnoldi Iteration (M=" << M << ") ===\n";
    // Arnoldi_matrices arnoldi(M, A);
    
    // cout << "\n=== Arnoldi Q Matrix (Orthonormal basis) ===\n";
    // print_matrix(arnoldi.Q);
    
    // cout << "\n=== Arnoldi H Matrix (Upper Hessenberg) ===\n";
    // print_matrix(arnoldi.H);
    
    // cout << "done\n";
}