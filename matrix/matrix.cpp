#include "matrix.hpp"
#include "immintrin.h"

  //------------//
 // A = A op B //
//------------//
void add_ip(matrix& A,matrix& B){
    if(A.cols != B.cols || A.rows != B.rows){
        std::cout << "Matrices dimensions do not match, Function: add_ip\n\n";
        std::abort();
    }
    for(int i = 0; i < A.rows; i++){
        for(int j = 0; j < A.cols; j++){
            A.at(i,j) += B.at(i,j);
        }
    }
}

void sub_ip(matrix& A,matrix& B){
    if(A.cols != B.cols || A.rows != B.rows){
        std::cout << "Matrices dimensions do not match, Function: sub_ip\n\n";
        std::abort();
    }
    for(int i = 0; i < A.rows; i++){
        for(int j = 0; j < A.cols; j++){
            A.at(i,j) -= B.at(i,j);
        }
    }
}

  //------------//
 // C = A op B //
//------------//
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

  //------------//
 // C = A x B  //
//------------//
// Rules of matrix multiplication
// mxn x nxp = mxp
matrix mul(matrix& A,matrix& B){
    if(A.cols != B.rows){
        std::cout << "A.cols != B.rows, Function: mul(A,B)\n\n";
        std::abort();
    }
    matrix res(A.rows, B.cols);
    for(int i = 0; i < res.cols; i++){
        for(int k = 0; k < B.rows;k++){
            for(int j = 0; j < res.rows; j++){
                res.at(i,j) += A.at(i,k)*B.at(k,j);
            }
        }
    }
    return res;
}

// Vectorized Normalization function 
float norm(matrix& M){
    __m256 sqsum = _mm256_setzero_ps();
    __m256 sumvec = _mm256_setzero_ps();
    int i = 0;
    for(; i + 7 < M.size; i+=8){    
        sumvec = _mm256_loadu_ps(&M.data[i]);
        sqsum = _mm256_fmadd_ps(sumvec,sumvec,sqsum);
    }
    __m128 bottom = _mm256_castps256_ps128(sqsum);
    __m128 top = _mm256_extractf128_ps(sqsum,1);
    bottom = _mm_add_ps(top,bottom);
    bottom = _mm_hadd_ps(bottom,bottom);
    bottom = _mm_hadd_ps(bottom,bottom);
    float squsum = _mm_cvtss_f32(bottom);
    for(;i<M.size; i++){
        squsum += M.data[i]*M.data[i];
    }
    if(squsum < 1e-15){
        std::cout<< "Matrix norm is zero, Division by zero error\n";
        std::abort();
    }
    float ret = sqrt(squsum);
    squsum = 1/ret;
    sqsum = _mm256_set1_ps(squsum);
    i = 0;
    for(; i + 7 < M.size; i+=8){
        sumvec = _mm256_loadu_ps(&M.data[i]);
        sumvec = _mm256_mul_ps(sumvec,sqsum);
        _mm256_storeu_ps(&M.data[i],sumvec);
    }
    for(;i<M.size; i++){
        M.data[i] *= squsum;
    }
    return ret;
}