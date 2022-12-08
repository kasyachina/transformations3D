#ifndef MATRIX_H
#define MATRIX_H
#include <vector>
#include <iostream>
#include <iomanip>

class Point
{
public:
    Point(double x, double y, double z, double w = 1);
    double getParameter(int index) const;
private:
    double data[4];
};


class Matrix
{
public:
    enum class MatrixType
    {
        ProjectionOXY,
        ProjectionOXZ,
        ProjectionOYZ,
    };
    static Matrix GetProjectionMatrix(MatrixType type);
    static Matrix GetAksonometricMatrix(double angleX, double angleY, double angleZ);
    static Matrix ComposeFromPoints(std::vector<Point> const& points);
    static std::vector<Point> DecomposeToPoints(Matrix const& matr);
    Matrix operator=(Matrix&& other);
    Matrix operator=(Matrix const& other);
    Matrix operator*(Matrix const& other);
    Matrix transpose() const;
    Matrix(Matrix const& other);
    Matrix(Matrix&& other);
    friend std::ostream& operator<<(std::ostream& out, Matrix const& mat);
    ~Matrix();
private:
    Matrix(int _n, int _m);
    void FreeMemory();
    void AllocateMemory(int n, int m);
    void CopyValues(Matrix const& other);
    double **array;
    int n, m;
};

#endif // MATRIX_H
