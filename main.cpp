#include "matrix\matrix.hpp"
#include <cstdlib>
#include <ctime>

float potential(float x){
    return x*x;
}
using namespace std;
// Testing simple matricies
int main(){
    srand(time(0));
    int N = 10;
    matrix m(N,N);
    matrix v(N,1);
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            m.at(i,j) = ((float)rand()/RAND_MAX);
            // cout << m.at(i,j) << " ";
        }
        v.at(i,0) = 1.0f;
        // cout << "\n";
    }
    int k = 10;
    for(int i = 0; i < k; i++){
        v = mulM(m,v);
        cout<< Normalize(v);
        cout<<"\n";
    }



    cout << "Done\n";
}