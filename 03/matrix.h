#pragma once
#include <cstdlib>

class Matrix
{
    class Row
    {
        int *r;
        size_t len;

    public:
        Row(int* m, size_t cols);
        int& operator[](size_t col);
        int operator[](size_t col) const;
    };

    size_t cols;
    size_t rows;
    int*m;

public:
    Matrix(size_t num_rows, size_t num_cols);
    ~Matrix();
    size_t getRows() const;
    size_t getColumns() const;
    const Matrix& operator*=(int n);
    bool operator==(const Matrix& other) const;
    bool operator!=(const Matrix& other) const;
    Row operator[](size_t row);
    Row operator[](size_t row) const;
};




