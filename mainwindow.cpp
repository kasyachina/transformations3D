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
}

MainWindow::~MainWindow()
{
    delete ui;
    delete area;
}

