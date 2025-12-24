#ifndef MATRIX_HPP
#define MATRIX_HPP

#include<iostream>
#include<vector>

// Row major default format
struct matrix{
    int rows, cols, size;
    std::vector<float> data;

    // Constructor, 
    matrix(int r, int c) : rows(r), cols(c), size(r*c), data(r*c,0.0f) {}

    float& at(int r,int c){
        return data[r*cols+c];
    }
};


#endif