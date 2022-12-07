#ifndef MATRIX_H
#define MATRIX_H
#include <vector>

class Point
{
public:
    Point(double x, double y, double z);
    double getParameter(int index) const;
private:
    double data[4];
};

class Matrix
{
public:
    enum class MatrixType
    {
        Translate,
        Rotate,
        Scale,
        ProjectionOXY,
        ProjectionOXZ,
        ProjectionOYZ,
        Dimetric,
    };
    static Matrix MatrixFactoryWithoutParameters(MatrixType type);
    static Matrix MatrixFactoryWithParameters(MatrixType type, std::vector<double> const& params);
    static Matrix ComposeFromPoints(std::vector<Point> const& points);
    Matrix operator=(Matrix&& other);
    Matrix operator=(Matrix const& other);
    Matrix operator*(Matrix const& other);
    Matrix(Matrix const& other);
    Matrix(Matrix&& other);
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
