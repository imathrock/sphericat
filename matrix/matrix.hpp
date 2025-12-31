#ifndef MATRIX_HPP
#define MATRIX_HPP

#include<iostream>
#include<vector>
#include<cstdlib>
#include<cmath>

// Row major default format
struct matrix{
    int rows, cols, size;
    std::vector<float> data;
    
    matrix(int r, int c) : rows(r), cols(c), size(r*c), data(r*c,0.0f) {}
    
    float& at(int r,int c){
        if(r<0 || r>rows || c<0 || c>cols){
            std::cout<< "Accessing matrix out of bounds"<<std::endl;
            std::abort();
        }
        return data[r*cols+c];
    }
    
    const float& at(int r,int c) const{
        if(r<0 || r>rows || c<0 || c>cols){
            std::cout<< "Accessing matrix out of bounds"<<std::endl;
            std::abort();
        }
        return data[r*cols+c];
    }
    
};

struct matrixH{
    int rows, cols, size;
    std::vector<float> data;
    float zero_ret = 0.0f;// To ensure I return a float's address instead of 0 value.
    matrixH(int N) : rows(N), cols(N), size((3*N)-2), data((3*N)-2) {}
    
    float& at(int r,int c){
        if(r<0 || r>rows || c<0 || c>cols){
            std::cout<< "Accessing matrixH out of bounds"<<std::endl;
            std::abort();
        }
        if(std::abs(r-c) >= 2) { 
            zero_ret = 0.0f;
            return zero_ret; 
        }
        return data[2*r+c];
    }
    
    const float& at(int r,int c) const{
        if(r<0 || r>rows || c<0 || c>cols){
            std::cout<< "Accessing matrixH out of bounds"<<std::endl;
            std::abort();
        }
        if(std::abs(r-c) >= 2) { return zero_ret; }
        return data[2*r+c];
    }

};

struct vector{
    int size;
    std::vector<float> data;

    vector(int N): size(N), data(N) {}

    float& at(int n){
        if(n<0 || n>size){
            std::cout << "vector access out of bounds" << std::endl;
            std::abort();
        }
        return data[n];
    }

    const float& at(int n) const{
        if(n<0 || n>size){
            std::cout << "vector access out of bounds" << std::endl;
            std::abort();
        }
        return data[n];
    }
};

float Normalize(matrix& M);

void addM_ip(matrix& a, const matrix& b);
void subM_ip(matrix& a, const matrix& b);

matrix addM(const matrix& a, const matrix& b);
matrix subM(const matrix& a, const matrix& b);

matrix mulM(matrix a, matrix b);

matrixH create_hamiltonian(int N, float L, float offset, float (*potential)(float));

std::vector<float> find_eigenvalues(matrixH H, matrix M);

#endif