#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGridLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QGridLayout *g = new QGridLayout;
    area = new PlotArea;
    g -> addWidget(area);
    centralWidget()->setLayout(g);
    Matrix mat = Matrix::MatrixFactoryWithoutParameters(Matrix::MatrixType::Dimetric);
    Matrix axes = Matrix::ComposeFromPoints({Point(0, 0, 5), Point(0, 5, 0), Point(5, 0, 0)});

}

MainWindow::~MainWindow()
{
    delete ui;
    delete area;
}

