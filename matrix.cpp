#include "matrix.h"
#include <cassert>
#include <cmath>


Point::Point(double x, double y, double z)
{
    data[0] = x;
    data[1] = y;
    data[2] = z;
    data[3] = 1;
}
double Point::getParameter(int index) const
{
    return data[index];
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
std::ostream& operator<<(std::ostream& out, Matrix const& mat)
{
    out << std::fixed << std::setprecision(3);
    for (int i = 0; i < mat.n; ++i)
    {
        for (int j = 0; j < mat.m; ++j)
        {
            out << std::setw(8) << mat.array[i][j];
        }
        out << "\n";
    }
    return out;
}
Matrix Matrix::transpose() const
{
    Matrix res(m, n);
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            res.array[j][i] = array[i][j];
        }
    }
    return res;
}
Matrix Matrix::GetProjectionMatrix(MatrixType type)
{
    //todo
}
Matrix Matrix::GetAksonometricMatrix(double angleX, double angleY, double angleZ)
{
    Matrix res(4, 4);
    res.array[0][0] = cos(angleY) * cos(angleZ) - sin(angleX) * sin(angleY) * sin (angleZ);
    res.array[0][1] = cos(angleY) * sin(angleZ) + sin(angleX) * sin(angleY) * cos (angleZ);
    res.array[0][2] = 0;

    res.array[1][0] = -cos(angleX) * sin(angleZ);
    res.array[1][1] = cos(angleX) * cos(angleZ);
    res.array[1][2] = 0;

    res.array[2][0] = sin(angleY) * cos(angleZ) + sin(angleX) * cos(angleY) * sin(angleZ);
    res.array[2][1] = sin(angleY) * sin(angleZ) - sin(angleX) * cos(angleY) * cos(angleZ);
    res.array[2][2] = 0;

    res.array[3][3] = 1;
    return res;
}

Matrix Matrix::ComposeFromPoints(std::vector<Point> const& points)
{
    int n = 4;
    int m = points.size();
    Matrix res(n, m);
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            res.array[i][j] = points[j].getParameter(i);
        }
    }
    return res;
}
std::vector<Point> Matrix::DecomposeToPoints(Matrix const& matr)
{
    std::vector<Point> ans;
    for (int i = 0; i < matr.m; ++i)
    {
         ans.push_back(Point(matr.array[0][i], matr.array[1][i], matr.array[2][i], matr.array[3][i]));
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
