#ifndef PLOTAREA_H
#define PLOTAREA_H

#include <QPainter>
#include <QWidget>
#include <vector>
#include "matrix.h"

class PlotArea : public QWidget
{
    Q_OBJECT
public:
    explicit PlotArea(QWidget *parent = nullptr);
    void SetFigurePoints(const std::vector<Point>& data);
    void TransformFigure(Matrix const& transform);
    QPointF Adjust(const Point& p);
    void Clear();
    void SetUnit(int nu);
    int getUnit() const;
private:
    bool mousePressed = false;
    QPointF lastMousePos;
    double angleX = 19.47 / 180 * 3.14;
    double angleY = -20.7 / 180 * 3.14;
    double angleZ = 0;
    double angleShift = 0.005;
    std::vector<Point> axis;
    Matrix AksonometricMatrix;
    int u; // unit size
    int min_unit = 5;
    int max_unit = 40;
    int delta_unit = 1;
    double tick_length = 1;
    int grid_line_width = 1;
    int axis_width = 2;
    int box_offset = 1;
    int box_width = 1;
    int pixel_width = 1;
    int line_width = 3;
    int axis_length = 20;
    int zx = 0;
    int zy = 0;
    std::vector<Point> figure;
    QColor XColor = Qt::blue;
    QColor YColor = Qt::green;
    QColor ZColor = Qt::magenta;
    QColor gridColor = Qt::gray;
    QColor axisColor = Qt::black;
    QColor boxColor = Qt::gray;
    void recalculateAxis();
    void inline drawBox(QPainter(&p));
    void inline drawGrid(QPainter& p);
    void inline drawAxis(QPainter& p);
    void inline drawTicks(QPainter& p);
    void inline drawArrows(QPainter& p);
    void inline drawFigure(QPainter& p);
    void paintEvent(QPaintEvent* event) override;
    virtual void mousePressEvent(QMouseEvent* event) override;
    virtual void mouseReleaseEvent(QMouseEvent* event) override;
    virtual void mouseMoveEvent(QMouseEvent* event) override;
    virtual void wheelEvent(QWheelEvent* event) override;
};

#endif // PLOTAREA_H
