#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <level.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::MainWindow)
{
    _ui->setupUi(this);

    _ui->graphicsView->setScene(new Level());
    _ui->graphicsView->scale(2, 2);
}

MainWindow::~MainWindow()
{
    delete _ui;
}
