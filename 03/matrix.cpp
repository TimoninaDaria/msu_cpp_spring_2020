#include <stdio.h>
#include <stdint.h>
#include <iostream>
#include <ctype.h>
#include <cassert>
#include "matrix.h"

using namespace std;

Matrix::Row::Row(int* m, size_t cols){
            r = m;
            len = cols;
        }

int& Matrix::Row::operator[](size_t col){
           if (col > len)
               throw out_of_range("");
           return *(r+col);
        }

int Matrix::Row::operator[](size_t col) const{
           if (col > len)
               throw out_of_range("");
           return *(r+col);
        }

Matrix::Matrix(size_t num_rows, size_t num_cols){
        m = (int*)(malloc(num_rows*num_cols*sizeof(int)));
        if(m == NULL)
            throw bad_alloc();
        cols = num_cols;
        rows = num_rows;
    }

Matrix::~Matrix(){
        free(m);
    }

size_t Matrix::getRows() const{
        return rows;
    }

size_t Matrix::getColumns() const{
        return cols;
    }

const Matrix& Matrix::operator*=(int n){
        for (size_t i = 0; i < cols*rows; ++i){
            m[i] = m[i]*n;
        }
        return *this;
    }

bool Matrix::operator==(const Matrix& other) const{
        if(cols != other.cols || rows != other.rows)
            return false;
        if (this == &other)
            return true;
        for (size_t i = 0; i < cols*rows; ++i)
            if (m[i] != other.m[i])
                return false;
        return true;
    }

bool Matrix::operator!=(const Matrix& other) const{
        return !(*this == other);
    }

Matrix::Row Matrix::operator[](size_t row){
        if (row > rows)
            throw out_of_range("");
        return Row(m+row*cols, cols);
    }

Matrix::Row Matrix::operator[](size_t row) const{
        if (row > rows)
            throw out_of_range("");
        return Row(m+row*cols, cols);
    }



