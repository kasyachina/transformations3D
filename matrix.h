#ifndef MATRIX_H
#define MATRIX_H


class Matrix
{
public:
    enum class MatrixType
    {
        Zero,
        Identity,
        Translate,
        Rotate,
        Scale,
        ProjectionOXY,
        ProjectionOXZ,
        ProjectionOYZ,
        Aksonometric,
    };
    static Matrix MatrixFactory(MatrixType type);
    void operator*=(Matrix const& other);
private:
    Matrix(int n, int m);
    double **a;
};

#endif // MATRIX_H
