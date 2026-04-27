#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "fractalwidget.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Fractal Generator");
    setCentralWidget(new FractalWidget(this));
    resize(600, 400);
    setMinimumSize(500, 300);
}

MainWindow::~MainWindow()
{
    delete ui;
}
