#pragma once

class Matrix
{
    class ROW
    {
        int *r;
        int len;

    public:
        ROW(int* m, int cols);
        int& operator[](int col);
    };

    int cols;
    int rows;
    int*m;

public:
    Matrix(int num_rows, int num_cols);
    ~Matrix();
    int getRows() const;
    int getColumns() const;
    void operator*=(int n);
    bool operator==(const Matrix& other) const;
    bool operator!=(const Matrix& other) const;
    ROW operator[](int row);
};




