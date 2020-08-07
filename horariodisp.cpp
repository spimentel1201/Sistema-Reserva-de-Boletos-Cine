#include "horariodisp.h"
#include "ui_horariodisp.h"

horariodisp::horariodisp(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::horariodisp)
{
    ui->setupUi(this);
}

horariodisp::~horariodisp()
{
    delete ui;
}

void horariodisp::on_aceptar_clicked()
{

}
