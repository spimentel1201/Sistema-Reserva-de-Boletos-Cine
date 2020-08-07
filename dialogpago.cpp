#include "dialogpago.h"
#include "ui_dialogpago.h"
#include <QDebug>
#include <validatorexception.h>

dialogPago::dialogPago(Cliente *cliinto, bool* exito, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialogPago)
{
    ui->setupUi(this);

    //validaciones a nivel vista
    ui->numerotarjeta->setInputMask("9999-9999-9999-9999");
    ui->codigoseg->setValidator(new QIntValidator());
    ui->codigoseg->setMaxLength(4);

    QDate da;
    da.setDate(2020, 1, 1);
    ui->dateEdit->setDate(da);

    user=cliinto;
    exitof=exito;
}

dialogPago::~dialogPago()
{
    delete ui;
}

void dialogPago::on_pushButton_clicked()
{
    QString tipo=ui->comboBox->currentText();
    QString nom=ui->nombre->text();
    QString ape=ui->apellido->text();
    QString tar=ui->numerotarjeta->text();
    QString fven=QString::number(ui->dateEdit->date().year())+"-"+
            QString::number(ui->dateEdit->date().month())+"-"+QString::number(ui->dateEdit->date().day());
    QString cod=ui->codigoseg->text();

    //validaciones antes de insertar
    try {
        if(nom.isEmpty()){
            throw ValidatorException("Nombre vacio");
        }
        if(ape.isEmpty()){
            throw ValidatorException("Apellido vacio");
        }

        if(tar.length()!=19){
            throw ValidatorException("Numero de tarjeta incorrecto");
        }
        if(cod.length()!=4){
            throw ValidatorException("Codigo de seguridad incorrecto");
        }

        //guardamos la tarjeta
        *exitof=user->guardar_tarjeta(tar, tipo, nom, fven, cod, ape);

        this->close();


    } catch (ValidatorException& v) {
       v.view();
    }
}

void dialogPago::on_pushButton_2_clicked()
{
    this->close();
}
