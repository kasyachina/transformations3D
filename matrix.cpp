#include "matrix.h"
#include <cassert>


Point::Point(double x, double y, double z)
{
    data[0] = x;
    data[1] = y;
    data[2] = z;
    data[3] = 1;
}
Matrix::Matrix(int _n, int _m)
{
    AllocateMemory(_n, _m);
}
Matrix::Matrix(Matrix const& other)
{
    if (&other != this)
    {
        FreeMemory();
        AllocateMemory(other.n, other.m);
        CopyValues(other);
    }
}
Matrix::Matrix(Matrix&& other)
{
    if (&other != this)
    {
        FreeMemory();
        array = other.array;
        other.array = nullptr;
        other.n = 0;
        other.m = 0;
        n = other.n;
        m = other.m;
    }
}
Matrix Matrix::operator=(Matrix&& other)
{
    if (&other != this)
    {
        FreeMemory();
        array = other.array;
        other.array = nullptr;
        other.n = 0;
        other.m = 0;
        n = other.n;
        m = other.m;
    }
    return *this;
}
Matrix Matrix::operator=(Matrix const& other)
{
    if (&other != this)
    {
        FreeMemory();
        AllocateMemory(other.n, other.m);
        CopyValues(other);
    }
    return *this;
}
Matrix Matrix::operator*(Matrix const& other)
{
    assert(m == other.n);
    Matrix res(n, other.m);
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < other.m; ++j)
        {
            for (int k = 0; k < m; ++k)
            {
                res.array[i][j] += array[i][k] * other.array[k][j];
            }
        }
    }
    return res;
}
Matrix Matrix::MatrixFactoryWithoutParameters(MatrixType type)
{
    Matrix ans(4, 4);
    switch(type)
    {
        case MatrixType::Dimetric:
        ans.array[0][0] = 0.935;
        ans.array[0][1] = -0.118;
        ans.array[0][2] = 0;

        ans.array[1][0] = 0;
        ans.array[1][1] = 0.943;
        ans.array[1][2] = 0;

        ans.array[2][0] = -0.354;
        ans.array[2][1] = 0.312;
        ans.array[2][2] = 0;
    }
    return ans;
}
void Matrix::AllocateMemory(int _n, int _m)
{
    n = _n;
    m = _m;
    array = new double*[n];
    for (int i = 0; i < n; ++i)
    {
        array[i] = new double[m];
    }
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            array[i][j] = 0;
        }
    }
}
void Matrix::FreeMemory()
{
    for (int i = 0; i < n; ++i)
    {
        delete[] array[i];
    }
    delete[] array;
}
void Matrix::CopyValues(Matrix const& other)
{
    for (int i = 0; i < other.n; ++i)
    {
        for (int j = 0; j < other.m; ++j)
        {
            array[i][j] = other.array[i][j];
        }
    }
}
Matrix::~Matrix()
{
    FreeMemory();
}
