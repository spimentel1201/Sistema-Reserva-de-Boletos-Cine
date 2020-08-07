#include "dialogloading.h"
#include "ui_dialogloading.h"

DialogLoading::DialogLoading(QString title, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogLoading)
{
    ui->setupUi(this);

    this->setWindowTitle(title);
    ui->progressBar->setValue(0);
    //nj=new ThreadLoading(loa, this);
    //nj->start(QThread::HighestPriority);
}

DialogLoading::~DialogLoading()
{
    delete ui;
}

void DialogLoading::actualizar(int value){
    if (value==100 || value==70){
        this->move(1000, 1000);
        ui->progressBar->setValue(0);
        return;
    }
    ui->progressBar->setValue(value);
}
