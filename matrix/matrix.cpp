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

// A function to QR decompose again
void QR_decompose(QR_thin& QR, matrix& A){
    for(int i = 0; i < A.cols; i++){

        for(int k = 0; k < A.rows; k++) { QR.Q.at(i,k) = A.at(i,k);}

        for(int j = 0; j < i; j++){
            float dot = dotprod(QR.Q, QR.Q, j, i);
            QR.R.at(j,i) = dot;
            subvecs(QR.Q,i,j,dot);
        }
        float norm = vecnorm(QR.Q, i);
        QR.R.at(i,i) = norm;
    }
}

matrix Transpose(matrix& A){
    matrix AT(A.rows, A.cols);
    for(int i = 0; i < A.cols; i++){        
        for(int j = 0; j < A.rows; j++){
            AT.at(j,i) = A.at(i,j);
        }
    }
    return AT;
}

// Column vector wise comparision to check if dot products are converging
bool allclose(matrix&A, matrix& B){ 
    for(int i = 0; i < A.cols; i++){
        float dot = dotprod(A, B, i,i);
        if(std::abs(std::abs(dot) - 1.0f) > 1e-6){ return false; }
    }
    return true;
}

QR_thin QR_algorithm(matrix&A){
    QR_thin qr(A);

    matrix Q_prev(qr.Q.cols, qr.Q.rows);
    matrix B(A.cols,A.rows);

    int iter = 2000;
    while(iter--){
        Q_prev = qr.Q;
        B = mul(qr.Q,A);
        QR_decompose(qr, B);
        std::cout<<iter<<"\n";
        if(allclose(Q_prev, qr.Q)){ break; }
    }
    // print_matrix(Q_prev);
    // print_matrix(qr.Q);
    return qr;
}

// Now I need somethign that will return me the eigenvalues. 
