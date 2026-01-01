#include"matrix.hpp"
#include <immintrin.h>
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
        m.at(i,i) = -2+potential(dx*i-offset);
    }
    for(int i = 0; i < N-1; i++){
        m.at(i,i+1) = 1;
        m.at(i+1,i) = 1;
    }
    return m;
}

float Normalize(matrix& M){
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
    if(sqsum < 1e-15){
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

matrix Transpose(matrix& M){
    matrix MT(M.cols, M.rows);
    for(int i = 0; i<M.rows; i++){
        for(int j = 0; j<M.cols; j++){
            MT.at(j,i) = M.at(i,j);
        }
    }
    MT.transpose ^= 1;
    return MT;
}

std::vector<float> column_vector(matrix& M,int i){
    std::vector<float> vec = std::vector<float>;
    if(M.transpose){
        std::memcpy(&vec,&M.at(i,0),M.rows*sizeof(float));
        return vec;
    }else{
        
        return ;
    }
}

// // QR decomposition
// QR_t QR_GS(matrix& M){
//     QR_t QR;
    
// }