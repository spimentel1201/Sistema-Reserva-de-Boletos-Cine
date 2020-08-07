#include "dialogidioma.h"
#include "ui_dialogidioma.h"
#include "QDebug"
#include "QSqlDatabase"
#include "QSqlQuery"
#include "conexionmysql.h"
#include <QMessageBox>
#include <validatorexception.h>
#include <databaseexception.h>
#include <QSqlError>

QString temp2;

DialogIdioma::DialogIdioma(QSqlDatabase dbinto, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogIdioma)
{
    ui->setupUi(this);
    ui->pushButton_2->hide();
    ui->pushButton_3->hide();

    db=dbinto;

    QSqlQuery query("SELECT * FROM Idioma ", db);
    if(!(query.size()==0)){
        while(query.next()){
            QString idi=query.value(1).toString();
            ui->listaIdioma->addItem(idi);
        }
    }
}

DialogIdioma::~DialogIdioma()
{
    delete ui;
}

void DialogIdioma::on_pushButton_clicked()
{
    if(ui->pushButton->text().compare("Guardar")==0){
        try {
            QString idioma=ui->newIdioma->text();
            if(idioma.compare("")==0)   throw ValidatorException("Vacio");
            QSqlQuery query;
            query.prepare("UPDATE Idioma SET nombre='"+idioma+"' WHERE nombre='"+temp2+"'");
            if(query.exec()){
                ui->newIdioma->setText("");
                QMessageBox::information(nullptr, tr("Informacion"), tr("Editado"),QMessageBox::Ok);
            }else   throw DatabaseException(query.lastError().text());

            ui->pushButton->setText("Agregar \nIdioma");
            ui->pushButton_2->hide();
            ui->pushButton_3->hide();
            ui->newIdioma->setText("");
            ui->listaIdioma->clear();
            QSqlQuery query2("SELECT * FROM Idioma ", db);
            if(query2.size()==0){
                qDebug()<<"Vacio";
            }else{
                while(query2.next()){
                    QString idi=query2.value(1).toString();
                    ui->listaIdioma->addItem(idi);
                }
            }
        } catch (ValidatorException& v) {
            v.view();
        } catch (DatabaseException& d){
            d.view();
        }


    }else{

        try {
            QString idioma=ui->newIdioma->text();
            if(idioma.compare("")==0)   throw ValidatorException("Vacio");
            QSqlQuery query;
            query.prepare("INSERT INTO Idioma (nombre) VALUES ('"+idioma+"')");
            if(query.exec()){
                qDebug()<<"Insertado";
                ui->listaIdioma->addItem(idioma);
                ui->newIdioma->setText("");

            }else   throw DatabaseException(query.lastError().text());

        } catch (ValidatorException& v) {
            v.view();
        } catch (DatabaseException& d){
            d.view();
        }

    }
}

void DialogIdioma::on_pushButton_2_clicked()
{
    ui->pushButton->setText("Agregar \nIdioma");
    ui->pushButton_2->hide();
    ui->pushButton_3->hide();
    ui->newIdioma->setText("");
}

void DialogIdioma::on_listaIdioma_doubleClicked(const QModelIndex &index)
{
    QString idiEdit=ui->listaIdioma->item(index.row())->text();
    ui->pushButton->setText("Guardar");
    ui->newIdioma->setText(idiEdit);
    temp2=idiEdit;
    ui->pushButton_2->show();
    ui->pushButton_3->show();
}

void DialogIdioma::on_pushButton_3_clicked()
{

    try {
        QSqlQuery query;
        query.prepare("DELETE FROM Idioma where (nombre='"+temp2+"')");
        if(query.exec()){
            ui->newIdioma->setText("");

        }else   throw DatabaseException(query.lastError().text());

        ui->pushButton->setText("Agregar \nIdioma");
        ui->pushButton_2->hide();
        ui->pushButton_3->hide();
        ui->newIdioma->setText("");
        ui->listaIdioma->clear();
        QSqlQuery query2("SELECT * FROM Idioma ", db);
        if(!(query2.size()==0)){
            while(query2.next()){
                QString idi=query2.value(1).toString();
                ui->listaIdioma->addItem(idi);
            }
        }
    } catch (DatabaseException& d){
        d.view();
    }

}
