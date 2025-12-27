#include "matrix\matrix.hpp"

float potential(float x){
    return x;
}

// Testing simple matricies
int main(){
    matrix a(512,512);
    for(int i = 0;i<5;i++){
        for(int j = 0;j<5;j++){
            a.at(i,j) = i*j;
        }
    }
    matrix b(512,512);
    for(int i = 0;i<5;i++){
        for(int j = 0;j<5;j++){
            b.at(i,j) = i+j;
        }
    }
    // matrix c = subM(a,b);
    matrix c = mulM(a,b);
    int N = 50;
    matrixH k = create_hamiltonian(N,50,50/2,potential);
    for(int i = 0; i <N; i++){
        for(int j = 0; j < N; j++){
            std::cout << k.atH(i,j) << " ";
        }
        std::cout << "\n";
    }

    std::cout << "Done\n";
}

