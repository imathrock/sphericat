#include "matrix.hpp"

// Testing simple matricies
int main(){
    matrix m(5,5);
    for(int i = 0;i<5;i++){
        for(int j = 0;j<5;j++){
            m.at(i,j) = i*j;
        }
    }

    for(int i = 0;i<5;i++){
        for(int j = 0;j<5;j++){
            std::cout << m.at(i,j) << " ";
        }
        std::cout << "\n";
    }
    
}

