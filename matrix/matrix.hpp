#ifndef MATRIX_H
#define MATRIX_H

#include<cmath>
#include<iostream>
#include<vector>
#include<cstdlib>

// Column major format
struct matrix{
    int cols, rows, size;
    std::vector<float> data;

    matrix(int c, int r) : cols(c), rows(r), size(r*c), data(c*r,0.0f){}

    inline float& at(int c, int r){
        return data[c*rows+r];
    }
    inline const float& at(int c, int r) const{
        return data[c*rows+r];
    }
};

  //------------//
 // A = A op B //
//------------//
void add_ip(matrix& A,matrix& B);
void sub_ip(matrix& A,matrix& B);

  //------------//
 // C = A op B //
//------------//
matrix add(matrix& A,matrix& B);
matrix sub(matrix& A,matrix& B);

  //------------//
 // C = A x B  //
//------------//
matrix mul(matrix& A,matrix& B);

// Normalization function, returns norm of the whole matrix, Vectorized for performance
float norm(matrix& M);

#endif