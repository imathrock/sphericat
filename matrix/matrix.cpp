#include "matrix.hpp"
#include "immintrin.h"

matrix add(matrix& A,matrix& B){
    if(A.cols != B.cols || A.rows != B.rows){
        std::cout << "Matrices dimensions do not match, Function: add\n\n";
        std::abort();
    }
    matrix C(A.cols,A.rows);
    for(int i = 0; i < A.rows; i++){
        for(int j = 0; j < A.cols; j++){
            C.at(i,j) = A.at(i,j)+B.at(i,j);
        }
    }
    return C;
}

void add(matrix&a, int i, int j, float scale){
    for(int k = 0; k < a.rows; k++){ a.at(i,k) += a.at(j,k)*scale; }
}

fvec add(fvec& A,fvec& B){
    if(A.size()!= B.size()){
        std::cout << "vector dimensions do not match, Function: add\n\n";
        std::abort();
    }
    fvec C(A.size());
    for(int i = 0;  i < B.size(); i++){ C[i] = A[i]+B[i]; }
    return C;
}

matrix sub(matrix& A,matrix& B){
    if(A.cols != B.cols || A.rows != B.rows){
        std::cout << "Matrices dimensions do not match, Function: sub\n\n";
        std::abort();
    }
    matrix C(A.cols,A.rows);
    for(int i = 0; i < A.rows; i++){
        for(int j = 0; j < A.cols; j++){
            C.at(i,j) = A.at(i,j)+B.at(i,j);
        }
    }
    return C;
}

void sub(matrix&a, int i, int j, float scale){
    for(int k = 0; k < a.rows; k++){ a.at(i,k) -= a.at(j,k)*scale; }
}

fvec sub(fvec& A,fvec& B){
    if(A.size()!= B.size()){
        std::cout << "vector dimensions do not match, Function: sub\n\n";
        std::abort();
    }
    fvec C(A.size());
    for(int i = 0;  i < B.size(); i++){ C[i] = A[i]-B[i]; }
    return C;
}

// Rules of matrix multiplication
// mxn x nxp = mxp
matrix mul(matrix& A,matrix& B){
    if(A.cols != B.rows){
        std::cout << "A.cols != B.rows, Function: mul(A,B)\n\n";
        std::abort();
    }
    matrix res(A.rows, B.cols);
    for (int i = 0; i < B.cols; i++) {
        for (int k = 0; k < A.cols; k++) {
            float scalar = B.at(i, k);
            for (int j = 0; j < A.rows; j++) {
                res.at(i, j) += A.at(k, j) * scalar;
            }
        }
    }
    return res;
}

fvec mul(matrix& A,fvec& B){
    if(A.cols != B.size()){
        std::cout << "A.cols != B.size, Function: mul(A,B)\n\n";
        std::abort();
    }
    fvec res(A.rows);
    for(int i = 0; i < A.cols; i++){
        float Bi = B[i];
        for(int j = 0; j < A.rows; j++){
            res[j] += A.at(i,j)*Bi;
        }
    }
    return res;
}

fvec mul(tridiag& A,fvec& B){
    if(A.cols != B.size()){
        std::cout << "A.cols != B.size, Function: mul(A,B)\n\n";
        std::abort();
    }
    fvec res(A.rows);
    for(int i = 0; i < A.cols; i++){
        float Bi = B[i];
        for(int j = 0; j < A.rows; j++){
            res[j] += A.at(i,j)*Bi;
        }
    }
    return res;
}

float dot(matrix&A, matrix&B, int i, int j){
    float res = 0;
    const float* a_ptr = &A.data[i * A.rows];
    const float* b_ptr = &B.data[j * B.rows];
    for(size_t k = 0; k < B.rows; k++){
        res += a_ptr[k]*b_ptr[k];
    }
    return res;
}

float dot(fvec&A, fvec&B){
    if(A.size() != B.size()){
        std::cout << "vector dot product arguments of incorrect size\n";
        std::abort();
    }
    float res = 0;
    for(size_t i = 0; i < A.size(); i++){
        res += A[i]*B[i];
    }
    return res;
}
