#include"matrix.hpp"

// a = a+b
void addM_ip(matrix& a, const matrix& b){ 
    if(a.rows != b.rows || a.cols != b.cols) {
        std::cout << "addM_ip : a and b dimension mismatch" << std::endl;
        return;
    }
    for(int r = 0; r < a.rows; ++r){ 
        for(int c = 0; c < a.cols; ++c){
            a.at(r,c) += b.at(r,c);
        }
    }
}
// a = a-b
void subM_ip(matrix& a, const matrix& b){
    if(a.rows != b.rows || a.cols != b.cols) {
        std::cout << "subM_ip : a and b dimension mismatch" << std::endl;
    }
    for(int r = 0; r < a.rows; ++r){
        for(int c = 0; c < a.cols; ++c){
            a.at(r,c) -= b.at(r,c);
        }
    }
}

// res = a+b
matrix addM(const matrix& a, const matrix& b){
    if(a.rows != b.rows || a.cols != b.cols) {
        std::cout << "addM : a and b dimension mismatch" << std::endl;  
        std::abort();
    }
    matrix res(a.rows, a.cols); 
    for(int r = 0; r < a.rows; ++r){
        for(int c = 0; c < a.cols; ++c){
            res.at(r,c) = a.at(r,c) + b.at(r,c);
        }
    }
    return res; 
}

// res = a-b
matrix subM(const matrix& a, const matrix& b){
    if(a.rows != b.rows || a.cols != b.cols) {
        std::cout << "subM : a and b dimension mismatch" << std::endl;
        std::abort();
    }
    matrix res(a.rows, a.cols);
    for(int r = 0; r < a.rows; ++r){
        for(int c = 0; c < a.cols; ++c){
            res.at(r,c) = a.at(r,c) - b.at(r,c);
        }
    }
    return res; 
}


// I will write some conditions so that this is 
// offloaded to GPU using openCL, till then I will keep it naive and on CPU

/*
Rules of matrix multiplication
mxn X nxp = mxp
*/
matrix mulM(matrix a, matrix b){
    if(a.cols != b.rows){
        std::cout << "mulM: sizes of matiricies do not match" << "\n";
        std::abort();
    }
    matrix out(a.rows,b.cols);

    for(int i = 0; i < out.rows;++i){
        for(int k = 0; k < a.cols; ++k){
            for(int j = 0; j < out.cols; ++j){
                out.at(i,j) += a.at(i,k)*b.at(k,j);
            }
        }
    }
    return out;
}

// Creates a hamiltonian matrix

matrixH create_hamiltonian(int N, float L, float offset, float (*potential)(float)){
    float dx = L/N;
    matrixH m(N);
    for(int i = 0; i < N; i++){
        m.atH(i,i) = -2+potential(dx*i-offset);
    }
    for(int i = 0; i < N-1; i++){
        m.atH(i,i+1) = 1;
        m.atH(i+1,i) = 1;
    }
    return m;
}