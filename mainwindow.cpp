#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGridLayout>
#include <cmath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QGridLayout *g = new QGridLayout;
    area = new PlotArea;
    setStyleSheet("background-color: white");
    g -> addWidget(area,                    0, 0, 15, 8);
    g -> addWidget(ui -> RotationLabel,     0, 8, 1, 2);
    g -> addWidget(ui -> OX,                1, 8, 1, 2);
    g -> addWidget(ui -> OXLeft,            2, 8, 1, 1);
    g -> addWidget(ui -> OXRight,           2, 9, 1, 1);
    g -> addWidget(ui -> OY,                3, 8, 1, 2);
    g -> addWidget(ui -> OYLeft,            4, 8, 1, 1);
    g -> addWidget(ui -> OYRight,           4, 9, 1, 1);
    g -> addWidget(ui -> OZ,                5, 8, 1, 2);
    g -> addWidget(ui -> OZLeft,            6, 8, 1, 1);
    g -> addWidget(ui -> OZRight,           6, 9, 1, 1);
    g -> addWidget(ui -> ScaleButton,       7, 8, 1, 2);
    g -> addWidget(ui -> TranslateButton,   8, 8, 1, 2);
    g -> addWidget(ui -> ProjectionButton,  9, 8, 1, 2);
    centralWidget()->setLayout(g);
    area -> SetFigurePoints(
    {Point(1, 1, 0), Point(1, 5, 0), Point(2, 5, 0), Point(2, 4, 0), Point(3.5, 5, 0), Point(5, 5, 0), Point(2, 3, 0),
     Point(5, 1, 0), Point(3.5, 1, 0), Point(2, 2, 0), Point(2, 1, 0), Point(1, 1, 0),
     Point(1, 1, 1), Point(1, 5, 1), Point(2, 5, 1), Point(2, 4, 1), Point(3.5, 5, 1), Point(5, 5, 1), Point(2, 3, 1),
     Point(5, 1, 1), Point(3.5, 1, 1), Point(2, 2, 1), Point(2, 1, 1), Point(1, 1, 1)});
}

MainWindow::~MainWindow()
{
    delete ui;
    delete area;
}


void MainWindow::on_OXLeft_clicked()
{
    area -> TransformFigure(Matrix::GetRotationMatrix(Matrix::RotationType::RotationOX, -rotationAngle));
    area -> repaint();
}


void MainWindow::on_OXRight_clicked()
{
    area -> TransformFigure(Matrix::GetRotationMatrix(Matrix::RotationType::RotationOX, rotationAngle));
    area -> repaint();
}


void MainWindow::on_OYLeft_clicked()
{
    area -> TransformFigure(Matrix::GetRotationMatrix(Matrix::RotationType::RotationOY, -rotationAngle));
    area -> repaint();
}


void MainWindow::on_OYRight_clicked()
{
    area -> TransformFigure(Matrix::GetRotationMatrix(Matrix::RotationType::RotationOY, rotationAngle));
    area -> repaint();
}


void MainWindow::on_OZLeft_clicked()
{
    area -> TransformFigure(Matrix::GetRotationMatrix(Matrix::RotationType::RotationOZ, -rotationAngle));
    area -> repaint();
}


void MainWindow::on_OZRight_clicked()
{
    area -> TransformFigure(Matrix::GetRotationMatrix(Matrix::RotationType::RotationOZ, rotationAngle));
    area -> repaint();
}

