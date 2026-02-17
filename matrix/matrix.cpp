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
    for(size_t i = 0;  i < B.size(); i++){ C[i] = A[i]+B[i]; }
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
    for(size_t i = 0;  i < B.size(); i++){ C[i] = A[i]-B[i]; }
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

fvec mul(tridiag& A,fvec& q){
    if(sqrt(A.size) != q.size()){
        std::cout << "Matrix and vector dimensions do not match \n";
        std::abort();
    }
    int N = static_cast<int>(q.size());
    fvec w(N);
    w[0] = A.at(0,0)*q[0] + A.at(1,0)*q[1];
    w[N-1] = A.at(N-2, N-1)*q[N-2] + A.at(N-1, N-1)*q[N-1];
    for(int i = 1; i < N-1; i++){
        w[i] = A.at(i-1,i)*q[i-1] + A.at(i,i)*q[i] + A.at(i+1,i)*q[i+1];
    }
    return w;
}

float dot(matrix&A, matrix&B, int i, int j){
    float res = 0;
    const float* a_ptr = &A.data[i * A.rows];
    const float* b_ptr = &B.data[j * B.rows];
    for(int k = 0; k < B.rows; k++){
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

float norm(fvec& v, bool normalize){
    float sqsum = 0;
    for(int i = 0; i < (int)v.size(); i++){
        sqsum+=v[i]*v[i];
    }
    sqsum = sqrt(sqsum);
    if(normalize){
        float invsqsum = 1/sqsum;
        for(int i = 0; i < (int)v.size(); i++){
            v[i] *= invsqsum;
        }
    }
    return sqsum;
}

float norm(matrix&a, int i){
    float res = 0.0f;
    for(int k = 0; k < a.rows; k++){ res += a.at(i,k)*a.at(i,k); }
    res = sqrt(res);
    float div = 1/res;
    for(int k = 0; k < a.rows; k++){ a.at(i,k) *= div; }
    return res;
}

fvec randvector(int N){
    fvec v(N);
    std::mt19937 gen(42);
    std::normal_distribution<float> dist(0.0, 1.0);
    for(int i = 0; i < N; i++){
        v[i] = dist(gen);
    }
    norm(v, true);
    return v;
}

bool allclose(matrix&A, matrix& B){ 
    for(int i = 0; i < A.cols; i++){
        float d = dot(A, B, i, i);
        if(std::abs(std::abs(d) - 1.0f) > 1e-6){ return false; }
    }
    return true;
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

tridiag generate_hamiltonian(int size, float L, float offset, float (*potential)(float)) {
    tridiag H(size);
    float dx = L / static_cast<float>(size);
    float inv_dx2 = 1.0f / (dx * dx);
    std::fill(H.subdiag.begin(), H.subdiag.end(), inv_dx2);
    std::fill(H.supdiag.begin(), H.supdiag.end(), inv_dx2);
    for (int i = 0; i < size; i++)
        H.diag[i] = -2.0f * inv_dx2 + potential(offset + static_cast<float>(i) * dx);
    return H;
}

void QR_decompose(QR_thin& QR, matrix& A){
    std::copy(A.data.begin(),A.data.end(), QR.Q.data.begin());
    for(int i = 0; i < A.cols; i++){
        for(int j = 0; j < i; j++){
            float dotval = dot(QR.Q, QR.Q, j, i);
            QR.R.at(j,i) = dotval;
            sub(QR.Q,i,j,dotval);
        }
        QR.R.at(i,i) = norm(QR.Q, i);
    }
}

QR_thin QR_algorithm(matrix&A){
    QR_thin qr(A);
    matrix Q_(qr.Q.cols,qr.Q.rows);
    matrix B(A.cols, A.rows);
    int iter = 2000;
    while(iter--){
        Q_ = qr.Q;
        B = mul(qr.Q,A);
        QR_decompose(qr,B);
        if(allclose(Q_,qr.Q)){break;}
    }
    return qr;
}

