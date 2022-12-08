#include "plotarea.h"
#include <QPainter>
#include <QPainterPath>
#include <QMessageBox>
#include <QMouseEvent>

LineSegmentData::LineSegmentData(const QPointF& p1, const QPointF& p2, const QColor& color)
{
    _p1 = p1;
    _p2 = p2;
    _color = color;
}

qreal LineSegmentData::x1() const
{
    return _p1.x();
}

qreal LineSegmentData::x2() const
{
    return _p2.x();
}

qreal LineSegmentData::y1() const
{
    return _p1.y();
}

qreal LineSegmentData::y2() const
{
    return _p2.y();
}
QPointF LineSegmentData::p1() const
{
    return _p1;
}
QPointF LineSegmentData::p2() const
{
    return _p2;
}
QColor LineSegmentData::color() const
{
    return _color;
}

PlotArea::PlotArea(QWidget *parent):QWidget(parent), AksonometricMatrix(Matrix::GetAksonometricMatrix(angleX, angleY, angleZ))
{
    u = std::min(width(), height()) / 20;
    recalculateAxis();
}

void PlotArea::recalculateAxis()
{
    axis = Matrix::DecomposeToPoints(AksonometricMatrix * Matrix::ComposeFromPoints({Point(1, 0, 0), Point(0, 1, 0), Point(0, 0, 1)}));
}
QPointF PlotArea::Adjust(const Point& _p)
{
    QPointF p = axis[0].toQPoint() * _p.getParameter(0) + axis[1].toQPoint() * _p.getParameter(1) + axis[2].toQPoint() * _p.getParameter(2);

    return QPointF(zx + p.x() * u, zy - p.y() * u);
}
void PlotArea::drawBox(QPainter& p)
{
    int h = height() - 2 * box_offset;
    int w = width() - 2 * box_offset;
    QPen boxPen(boxColor);
    boxPen.setWidth(box_width);
    p.setPen(boxPen);
    p.drawRect(box_offset, box_offset, w, h);
}
void PlotArea::drawGrid(QPainter& p)
{
    QPen gridPen(gridColor);
    gridPen.setWidth(grid_line_width);
    p.setPen(gridPen);
    int i = 0;
    while(zx + i * u <= width() - box_offset)
    {
        i++;
        p.drawLine(zx + i * u, box_offset, zx + i * u, height() - box_offset);
        p.drawLine(zx - i * u, box_offset, zx - i * u, height() - box_offset);
    }
    i = 0;
    while(zy + i * u < height())
    {
        i++;
        p.drawLine(box_offset, zy + i * u, width() - box_offset, zy + i * u);
        p.drawLine(box_offset, zy - i * u, width() - box_offset, zy - i * u);
    }
}
void PlotArea::drawAxis(QPainter& p)
{
    /*auto f = [this, &p](Point const& point, QColor color){
        double vx = point.getParameter(0);
        double vy = point.getParameter(1);
        double x = 0;
        double y = 0;
        if (vx == 0)
        {
            x = width() / 2;
            y = 0;
        }
        else
        {
            double t = -zx / vx;
            y = zy + vy * t;
            if (y < 0 || y > height())
            {
                if (vy == 0)
                {
                    y = zy;
                    x = 0;
                }
                else
                {
                    t = -zy / vy;
                    y = 0;
                    x = zx + vx * t;
                }
            }
        }
        QPen axisPen(color);
        axisPen.setWidth(axis_width);
        p.setPen(axisPen);
        p.drawLine(x, height() - y, width() - x, y);
    };*/
    //f(axis[0], Qt::blue);
    //f(axis[1], Qt::green);
    //f(axis[2], Qt::magenta);
    QPointF center(zx, zy);


    QPen axisPen(XColor);
    axisPen.setWidth(axis_width);
    p.setPen(axisPen);
    p.drawLine(Adjust(Point(-axis_length, 0, 0)), Adjust(Point(axis_length, 0, 0)));

    axisPen.setColor(YColor);
    p.setPen(axisPen);
    p.drawLine(Adjust(Point(0, -axis_length, 0)), Adjust(Point(0, axis_length, 0)));

    axisPen.setColor(ZColor);
    p.setPen(axisPen);
    p.drawLine(Adjust(Point(0, 0, -axis_length)), Adjust(Point(0, 0, axis_length)));

    axisPen.setColor(axisColor);
    p.setPen(axisPen);
    p.drawLine(center, Adjust({1, 0, 0}));
    p.drawLine(center, Adjust({0, 1, 0}));
    p.drawLine(center, Adjust({0, 0, 1}));

}
void PlotArea::drawTicks(QPainter& p)
{
    QPen ticksPen(axisColor);
    ticksPen.setWidth(axis_width);
    p.setPen(ticksPen);
    QFont font = p.font();
    font.setPixelSize(12);
    p.setFont(font);
    //ticks x
    int alignFlags = Qt::AlignRight | Qt::AlignTop;
    p.drawText(QRect{zx  - u + pixel_width, zy + pixel_width, u - pixel_width, u - pixel_width}, alignFlags, QString::number(0));
    for (int i = 1; i <= axis_length; ++i)
    {
        p.drawLine(Adjust(Point(i, 0, -0.5)), Adjust(Point(i, 0, 0.5)));
        p.drawLine(Adjust(Point(-i, 0, -0.5)), Adjust(Point(-i, 0, 0.5)));
    }
    //ticks y
    for (int i = 1; i <= axis_length; ++i)
    {
        p.drawLine(Adjust(Point(0, i, -0.5)), Adjust(Point(0, i, 0.5)));
        p.drawLine(Adjust(Point(0, -i, -0.5)), Adjust(Point(0, -i, 0.5)));
    }
    //ticks z
    for (int i = 1; i <= axis_length; ++i)
    {
        p.drawLine(Adjust(Point(-0.5, 0, i)), Adjust(Point(0.5, 0, i)));
        p.drawLine(Adjust(Point(-0.5, 0, -i)), Adjust(Point(0.5, 0, -i)));
    }
}
void PlotArea::drawArrows(QPainter& p)
{
    QPen arrowsPen(axisColor);
    arrowsPen.setWidth((axis_width));
    p.setBrush(QBrush(axisColor));
    p.setRenderHint(QPainter::RenderHint::Antialiasing);
    //arrow x
    QPainterPath px;
    px.moveTo(width() - u - 1, zy + 2 * tick_length);
    px.lineTo(width() - u - 1, zy - 2 * tick_length);
    px.lineTo(width() - 1, zy);
    px.lineTo(width() - u - 1, zy + 2 * tick_length);
    p.drawPath(px);
    p.drawText(QRect{width() - u / 2 - 1, zy + u / 2, u, u}, "X");
    //arrow y
    QPainterPath py;
    py.moveTo(zx + 2 * tick_length, u + 1);
    py.lineTo(zx - 2 * tick_length, u + 1);
    py.lineTo(zx, 1);
    py.lineTo(zx + 2 * tick_length, u + 1);
    p.drawPath(py);
    p.drawText(QRect{zx + u / 2, u / 2, u, u}, "Y");
}
void PlotArea::drawLineSegments(QPainter& p)
{
    for (const auto& segmentData : segments)
    {
        p.setPen(QPen(segmentData.color(), line_width));
        //p.drawLine(Adjust(segmentData.p1()), Adjust(segmentData.p2()));
    }
}
void PlotArea::Clear()
{
    segments.clear();
}
void PlotArea::AddLineSegment(const LineSegmentData& data)
{
    segments.push_back(data);
}
void PlotArea::paintEvent(QPaintEvent*)
{
    zx = width() / 2;
    zy = height() / 2;
    AksonometricMatrix = Matrix::GetAksonometricMatrix(angleX, angleY, angleZ);
    recalculateAxis();
    QPainter pt(this);
    drawBox(pt);
    drawAxis(pt);
    drawTicks(pt);

    //drawArrows(pt);
    //drawGrid(pt);
    //drawLineSegments(pt);
}
void PlotArea::mousePressEvent(QMouseEvent* event)
{
    lastMousePos = event->position();
    mousePressed = true;
}
void PlotArea::mouseMoveEvent(QMouseEvent* event)
{
    if (mousePressed)
    {
        QPointF pos = event->position();
        double deltaX = pos.x() - lastMousePos.x();
        double deltaY = pos.y() - lastMousePos.y();
        angleY += angleShift * deltaX;
        angleX += angleShift * deltaY;
        lastMousePos = pos;
        repaint();
    }
}
void PlotArea::mouseReleaseEvent(QMouseEvent* event)
{
    mousePressed = false;
}
int PlotArea::getUnit() const
{
    return u;
}
void PlotArea::SetUnit(int nu)
{
      u = nu;
}
