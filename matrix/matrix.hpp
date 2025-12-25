#ifndef MATRIX_HPP
#define MATRIX_HPP

#include<iostream>
#include<vector>
#include<cstdlib>

// Row major default format
struct matrix{
    int rows, cols, size;
    std::vector<float> data;

    // Constructor, 
    matrix(int r, int c) : rows(r), cols(c), size(r*c), data(r*c,0.0f) {}

    float& at(int r,int c){
        return data[r*cols+c];
    }
    
    const float& at(int r,int c) const{
        return data[r*cols+c];
    }
};

void addM_ip(matrix& a, const matrix& b);
void subM_ip(matrix& a, const matrix& b);

matrix addM(const matrix& a, const matrix& b);
matrix subM(const matrix& a, const matrix& b);

matrix mulM(matrix a, matrix b);
#endif