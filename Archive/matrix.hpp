// #ifndef MATRIX_H
// #define MATRIX_H

// #include<cmath>
// #include<iostream>
// #include<vector>
// #include<cstdlib>
// #include<algorithm>
// #include<random>

// typedef std::vector<float> fvec;

// // Column major format
// struct matrix{
//     int cols, rows, size;
//     fvec data;

//     matrix(int c, int r) : cols(c), rows(r), size(r*c), data(c*r,0.0f){}

//     inline float& at(int c, int r){
//         return data[c*rows+r];
//     }
//     inline const float& at(int c, int r) const{
//         return data[c*rows+r];
//     }

// };

// struct tri_diag_matrix{
//     int size;
//     fvec diag;
//     fvec sub_diag;
//     fvec sup_diag;
//     float zero_ret = 0.0f;

//     tri_diag_matrix(int N) : size(N*N), diag(N,0.0f), sub_diag(N-1,0.0f), sup_diag(N-1,0.0f){}

//     inline float& at(int c, int r){
//         if(c==r){ return diag[c]; }
//         if(c==r+1){ return sub_diag[r]; }
//         if(c+1==r){ return sup_diag[c]; }
//         return zero_ret;
//     }
//     inline const float at(int c, int r) const{
//         if(c==r){ return diag[c]; }
//         if(c==r+1){ return sub_diag[r]; }
//         if(c+1==r){ return sup_diag[c]; }
//         return 0.0f;
//     }

// };

// // Generates a hamiltonian matrix given potential function.
// tri_diag_matrix generate_hamiltonian(int size,float L, float offset, float (*potential)(float));

//   //------------//
//  // A = A op B //
// //------------//
// void add_ip(matrix& A,matrix& B);
// void sub_ip(matrix& A,matrix& B);

//   //------------//
//  // C = A op B //
// //------------//
// matrix add(matrix& A,matrix& B);
// matrix sub(matrix& A,matrix& B);

//   //------------//
//  // C = A x B  //
// //------------//
// matrix mul(matrix& A,matrix& B);

// float dot(fvec& A, fvec& B);

// // Normalization function, returns frobenius norm of the whole matrix, vecized for performance
// float norm(matrix& M);
// // fvec normalization
// float normvec(fvec& v);

// //-----------------------//
// //   QR decomposition    //
// //-----------------------//
// inline float dotprod(matrix&a, matrix&b, int i, int j){
//     float res = 0; 
//     for(int k = 0; k < b.rows; k++){ res += a.at(i,k)*b.at(j,k); }
//     return res;
// }

// inline float vecnorm(matrix&a, int i){
//     float res = 0.0f;
//     for(int k = 0; k < a.rows; k++){ res += a.at(i,k)*a.at(i,k); }
//     res = sqrt(res);
//     float div = 1/res;
//     for(int k = 0; k < a.rows; k++){ a.at(i,k) *= div; }
//     return res;
// }

// inline void subvecs(matrix&a, int i, int j, float scale){
//     for(int k = 0; k < a.rows; k++){ a.at(i,k) -= a.at(j,k)*scale; }
// }


// // To do FULL QR decompositon check the dimensions of matrix Q, If it is tall, dimensions of R is the same as A and Q is a square matrix.
// struct QR_thin {
//     matrix Q, R;
//     QR_thin(matrix& A) : Q(A.cols, A.rows) , R(A.cols, A.cols) {
//         for(int i = 0; i < A.cols; i++){

//             for(int k = 0; k < A.rows; k++) { Q.at(i,k) = A.at(i,k);}

//             for(int j = 0; j < i; j++){
//                 float dot = dotprod(Q, Q, j, i);
//                 R.at(j,i) = dot;
//                 subvecs(Q,i,j,dot);
//             }
//             R.at(i,i) = vecnorm(Q, i);
//         }
//     }
// };

// bool allclose(matrix&A, matrix& B);

// void QR_decompose(QR_thin& QR, matrix& A);

// QR_thin QR_algorithm(matrix&A);

// matrix Transpose(matrix& A);

// struct eigen{
//     fvec eigenvalues;
//     std::vector<fvec> eigenvectors;
//     eigen(matrix& A) {
//         QR_thin qr = QR_algorithm(A);
//         matrix QT = Transpose(qr.Q);
//         eigenvalues.resize(A.cols);
//         eigenvectors.resize(A.cols, fvec(A.cols));
//         matrix B = mul(A,QT);
//         B = mul(qr.Q,B);
//         for(int i = 0; i < B.cols; i++){ eigenvalues[i] = B.at(i,i); }
//         for(int i = 0; i < qr.Q.cols; i++){
//             for(int j = 0; j < qr.Q.rows; j++){
//                 eigenvectors[i][j] = qr.Q.at(i,j);
//             }
//         }
//     }
// };

// // Okay so for a lanczos eigenvalue problem I need a randomized normalized eigenvector. 
// // I need a randomized vector generator
// fvec randvector(int N);

// fvec TDmat_vec_mul(tri_diag_matrix& A, fvec q);

// inline void scale_fvec(float f, fvec& v){
//     for(int i = 0; i< v.size(); i++){ v[i]*=f;}
// }

// static inline void append_mtx(matrix&Q, fvec f, int col){
//     for(int i = 0; i < Q.rows; i++){Q.at(col,i) = f[i];}
// }

// static inline fvec getcol(matrix& Q, int col){
//     fvec f(Q.rows);
//     for(int i = 0; i < Q.rows; i++){ f[i] = Q.at(col, i); }
//     return f;
// }

// // f -= scale * g (in place)
// static inline void subfvecs(fvec& f, const fvec& g, float scale){
//     for(size_t i = 0; i < f.size(); i++){ f[i] -= scale * g[i]; }
// }

// struct Arnoldi_matrices{
//     matrix Q, H;
//     Arnoldi_matrices(int M, tri_diag_matrix& A) : Q(M, static_cast<int>(std::sqrt(static_cast<double>(A.size)))), H(M, M) {
//         const int N = static_cast<int>(std::sqrt(static_cast<double>(A.size)));
//         if (M > N) { std::cerr << "Arnoldi: M must be <= N\n"; std::abort(); }
//         fvec q0 = randvector(N);
//         append_mtx(Q, q0, 0);
//         for (int j = 0; j < M; j++) {
//             fvec v = TDmat_vec_mul(A, getcol(Q, j));
//             for (int i = 0; i <= j; i++) {
//                 fvec qi = getcol(Q, i);
//                 H.at(i, j) = dot(qi, v);
//                 subfvecs(v, qi, H.at(i, j));
//             }
//             if (j + 1 >= M) break;
//             float beta = normvec(v);
//             if (beta < 1e-15f) break;
//             H.at(j + 1, j) = beta;
//             append_mtx(Q, v, j + 1);
//         }
//     }
// };

// // Lanczos for symmetric tridiagonal A: produces orthonormal Q and symmetric tridiagonal T.
// // T is stored as diagonal alpha and subdiagonal beta (beta[j] below alpha[j]).
// struct Lanczos_result{
//     matrix Q;       // N x M, columns are Lanczos vectors
//     fvec alpha;     // diagonal of T, length M
//     fvec beta;      // subdiagonal of T, length M-1 (beta[j] = T(j+1,j))
//     Lanczos_result(int M, tri_diag_matrix& A) : Q(M, static_cast<int>(std::sqrt(static_cast<double>(A.size)))), alpha(M), beta((M > 0 ? M - 1 : 0), 0.0f) {
//         const int N = static_cast<int>(std::sqrt(static_cast<double>(A.size)));
//         if (M > N) { std::cerr << "Lanczos: M must be <= N\n"; std::abort(); }
//         if (M <= 0) return;
//         fvec q0 = randvector(N);
//         append_mtx(Q, q0, 0);
//         float beta_prev = 0.0f;
//         fvec q_prev(N, 0.0f);
//         for (int j = 0; j < M; j++) {
//             fvec qj = getcol(Q, j);
//             fvec u = TDmat_vec_mul(A, qj);
//             alpha[j] = dot(qj, u);
//             subfvecs(u, qj, alpha[j]);
//             if (j > 0) subfvecs(u, q_prev, beta_prev);
//             beta_prev = normvec(u);
//             if (j < M - 1) beta[j] = beta_prev;
//             if (j + 1 >= M) break;
//             if (beta_prev < 1e-15f) break;
//             append_mtx(Q, u, j + 1);
//             q_prev = u;
//         }
//     }
// };

// #endif