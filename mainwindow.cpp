#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "horariodisp.h"

MainWindow::MainWindow(QWidget *parent, QString data)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mess=data;
    ui->username->setText(data);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_25_clicked()
{

}

void MainWindow::on_pushButton_37_clicked()
{
    horariodisp *horario = new horariodisp();
    horario->show();
    close();
}

void MainWindow::on_pushButton_38_clicked()
{
    horariodisp *horario = new horariodisp();
    horario->show();
    close();
}

void MainWindow::on_pushButton_39_clicked()
{
    horariodisp *horario = new horariodisp();
    horario->show();
    close();
}

void MainWindow::on_pushButton_40_clicked()
{
    horariodisp *horario = new horariodisp();
    horario->show();
    close();
}

void MainWindow::on_pushButton_41_clicked()
{
    horariodisp *horario = new horariodisp();
    horario->show();
    close();
}

void MainWindow::on_pushButton_42_clicked()
{
    horariodisp *horario = new horariodisp();
    horario->show();
    close();
}

void MainWindow::on_pushButton_31_clicked()
{
    horariodisp *horario = new horariodisp();
    horario->show();
    close();
}

void MainWindow::on_pushButton_32_clicked()
{
    horariodisp *horario = new horariodisp();
    horario->show();
    close();
}

void MainWindow::on_pushButton_33_clicked()
{
    horariodisp *horario = new horariodisp();
    horario->show();
    close();
}

void MainWindow::on_pushButton_34_clicked()
{
    horariodisp *horario = new horariodisp();
    horario->show();
    close();
}

void MainWindow::on_pushButton_35_clicked()
{
    horariodisp *horario = new horariodisp();
    horario->show();
    close();
}

void MainWindow::on_pushButton_36_clicked()
{
    horariodisp *horario = new horariodisp();
    horario->show();
    close();
}
