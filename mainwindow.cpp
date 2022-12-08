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
    g -> addWidget(area);
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

