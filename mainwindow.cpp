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


    double x = 19.47 / 180 * 3.14;
    double y = -20.7 / 180 * 3.14;
    double z = 0;
    Matrix mat = Matrix::GetAksonometricMatrix(x, y, z);
    Matrix axes = Matrix::ComposeFromPoints({Point(1, 0, 0), Point(0, 1, 0), Point(0, 0, 1)});
    std::cout << mat << "\n" << axes << "\n" << mat * axes << "\n";
}

MainWindow::~MainWindow()
{
    delete ui;
    delete area;
}

