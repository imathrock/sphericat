#include "matrix\matrix.hpp"

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
    std::cout << "Done\n";
}

