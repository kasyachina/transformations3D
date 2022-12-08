#ifndef PLOTAREA_H
#define PLOTAREA_H

#include <QPainter>
#include <QWidget>
#include <vector>
#include "matrix.h"

class LineSegmentData
{
public:
    explicit LineSegmentData(const QPointF& p1, const QPointF& p2, const QColor& color);
    qreal x1() const;
    qreal x2() const;
    qreal y1() const;
    qreal y2() const;
    QPointF p1() const;
    QPointF p2() const;
    QColor color() const;
private:
    QPointF _p1, _p2;
    QColor _color;
};

class PlotArea : public QWidget
{
    Q_OBJECT
public:
    explicit PlotArea(QWidget *parent = nullptr);
    void AddLineSegment(const LineSegmentData& data);
    QPointF Adjust(const QPointF& p);
    void Clear();
    void SetUnit(int nu);
    int getUnit() const;
private:
    double angleX = 19.47 / 180 * 3.14;
    double angleY = -20.7 / 180 * 3.14;
    double angleZ = 0;
    Matrix AksonometricMatrix;
    int u; // unit size
    int tick_length = 4;
    int grid_line_width = 1;
    int axis_width = 2;
    int box_offset = 1;
    int box_width = 1;
    int pixel_width = 1;
    int line_width = 3;
    int zx = 0;
    int zy = 0;
    std::vector<LineSegmentData> segments;
    QColor axisColor = Qt::black;
    QColor gridColor = Qt::gray;
    QColor boxColor = Qt::gray;
    void inline drawBox(QPainter(&p));
    void inline drawGrid(QPainter& p);
    void inline drawAxis(QPainter& p);
    void inline drawTicks(QPainter& p);
    void inline drawArrows(QPainter& p);
    void inline drawLineSegments(QPainter& p);
    void paintEvent(QPaintEvent* event) override;
};

#endif // PLOTAREA_H
