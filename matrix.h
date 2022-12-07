#ifndef MATRIX_H
#define MATRIX_H
#include <vector>

class Point
{

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
        Aksonometric,
    };
    static Matrix MatrixFactoryWithoutParameters(MatrixType type);
    static Matrix MatrixFactoryWithParameters(MatrixType type, std::vector<double> const& params);
    static Matrix ComposeFromPoints(std::vector<Point> const& points);
    Matrix operator=(Matrix&& other);
    Matrix operator=(Matrix const& other);
    Matrix operator*=(Matrix const& other);
private:
    Matrix(int n, int m);
    double **a;
};

#endif // MATRIX_H
