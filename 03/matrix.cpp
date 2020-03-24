#include <stdio.h>
#include <stdint.h>
#include <iostream>
#include <ctype.h>
#include <cassert>
#include "matrix.h"

using namespace std;

Matrix::ROW::ROW(int* m, int cols){
            r = m;
            len = cols;
        }

int& Matrix::ROW::operator[](int col){
           if (col > len)
               throw out_of_range("");
           return *(r+col);
        }

Matrix::Matrix(int num_rows, int num_cols){
        m = (int*)(malloc(num_rows*num_cols*sizeof(int)));
        cols = num_cols;
        rows = num_rows;
    }

Matrix::~Matrix(){
        free(m);
    }

int Matrix::getRows() const{
        return rows;
    }

int Matrix::getColumns() const{
        return cols;
    }

void Matrix::operator*=(int n){
        for (int i = 0; i < cols*rows; ++i){
            m[i] = m[i]*n;
        }
        return;
    }

bool Matrix::operator==(const Matrix& other) const{
        if(cols != other.cols || rows != other.rows)
            return false;
        if (this == &other)
            return true;
        for (int i = 0; i < cols*rows; ++i)
            if (m[i] != other.m[i])
                return false;
        return true;
    }

bool Matrix::operator!=(const Matrix& other) const{
        return !(*this == other);
    }

Matrix::ROW Matrix::operator[](int row){
        if (row > rows)
            throw out_of_range("");
        return ROW(m+row*cols, cols);
    }



