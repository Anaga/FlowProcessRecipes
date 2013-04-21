#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDialog"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_New_clicked()
{

}

void MainWindow::on_pushButton_Save_clicked()
{

}

void MainWindow::on_pushButton_Open_clicked()
{

}

void MainWindow::on_pushButton_Run_clicked()
{

}
