#include "matrix\matrix.hpp"
#include <cstdlib>
#include <ctime>

using namespace std;
// Testing simple matricies
int main(){
    matrix A(4000,4000);
    matrix B(4000,4000);
    for(int i = 0; i< 4000; i++){        
        for(int j = 0; j< 4000; j++){
            A.at(i,j) = i+j;
            B.at(i,j) = i+j;
        }
    }
    matrix c = mul(A,B);
    cout << norm(c) << "\n";
    cout << "done\n";
}