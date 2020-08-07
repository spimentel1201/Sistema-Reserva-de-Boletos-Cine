#include "dialogaddsala.h"
#include "ui_dialogaddsala.h"
#include "conexionmysql.h"
#include <QDebug>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>
#include <validatorexception.h>
#include <databaseexception.h>

DialogAddSala::DialogAddSala(QSqlDatabase dbinto, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddSala)
{
    ui->setupUi(this);

    ui->lineEdit->setValidator(new QIntValidator(0, 127));
    ui->lineEdit->setMaxLength(3);
    ui->lineEdit_2->setValidator(new QIntValidator(0, 300));
    ui->lineEdit_2->setMaxLength(3);

    db=dbinto;

}

DialogAddSala::~DialogAddSala()
{
    delete ui;
}


void DialogAddSala::on_pushButtonGuardar_clicked()
{
    QString id=ui->lineEdit->text();
    QString csillas=ui->lineEdit_2->text();
    int t=ui->comboBox->currentIndex();

    QString tipo;
    if(t==0){
        tipo="A";
    }else{
        tipo="B";
    }


    try {
        if(id.isEmpty())    throw ValidatorException("Id vacio\t\t");

        else if(csillas.isEmpty())  throw ValidatorException("Cantidad de sillas vacia\t\t");

        else if(csillas.toInt()>80)    throw ValidatorException("Cantidad de sillas invalida \n debe ser menor a 80\t\t");

        else if(id.toInt()>127)    throw ValidatorException("Id invalido \n debe ser menor a 127\t\t");

        QSqlQuery query;
        query.prepare("INSERT INTO sala (id_sala, totalsillas, tiposala) VALUES("+id+", "+csillas+", '"+tipo+"')");
        if(query.exec()){
               QMessageBox::information(nullptr, tr("Informacion"), tr("Sala\t\nAgregada\t"),QMessageBox::Ok);

               this->close();

        }else   throw DatabaseException(query.lastError().text());

    } catch (ValidatorException& v) {
        v.view();
        return;
    } catch (DatabaseException& d){
        d.view();
    }
}
