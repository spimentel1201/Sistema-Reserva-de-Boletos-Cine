#include "dialoggenero.h"
#include "ui_dialoggenero.h"
#include "QSqlDatabase"
#include "QDebug"
#include "QSqlQuery"
#include "conexionmysql.h"
#include <QMessageBox>
#include <validatorexception.h>
#include <databaseexception.h>
#include <QSqlError>

QString temp;

DialogGenero::DialogGenero(QSqlDatabase dbinto, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogGenero)
{
    ui->setupUi(this);
    ui->pushButton_2->hide();
    ui->pushButton_3->hide();
    db=dbinto;

    //Obtenemos los generos y añadimos a la vista
    QSqlQuery query("SELECT * FROM Genero ", db);
    if(!(query.size()==0)){
        while(query.next()){
            QString gen=query.value(1).toString();
            ui->listagenero->addItem(gen);
        }
    }
}

DialogGenero::~DialogGenero()
{
    delete ui;
}

void DialogGenero::on_pushButton_clicked()
{
    if(ui->pushButton->text().compare("Guardar")==0){
        try {
            QString genero=ui->newGenero->text();
            if(genero.compare("")==0)   throw ValidatorException("Vacio");
            //Se actualiza el registro
            QSqlQuery query;
            query.prepare("UPDATE Genero SET nombre='"+genero+"' WHERE nombre='"+temp+"'");

            if(query.exec()){
                ui->newGenero->setText("");
                QMessageBox::information(nullptr, tr("Informacion"), tr("Editado"),QMessageBox::Ok);
            }else throw DatabaseException(query.lastError().text());
            ui->pushButton->setText("Agregar \nGenero");
            ui->pushButton_2->hide();
            ui->pushButton_3->hide();
            ui->newGenero->setText("");
            ui->listagenero->clear();
            //actualizamos la vista
            QSqlQuery query2("SELECT * FROM Genero ", db);
            if(!(query2.size()==0)){
                while(query2.next()){
                    QString gen=query2.value(1).toString();
                    ui->listagenero->addItem(gen);
                }
            }
        } catch (ValidatorException& v) {
            v.view();
        } catch (DatabaseException& d){
            d.view();
        }


    }else{
        try {
            //validamos
            QString genero=ui->newGenero->text();
            if(genero.compare("")==0)   throw ValidatorException("Vacio");
            //se inserta
            QSqlQuery query;
            query.prepare("INSERT INTO Genero (nombre) VALUES ('"+genero+"')");
            if(query.exec()){
                //se actualiza la vista
                ui->listagenero->addItem(genero);
                ui->newGenero->setText("");
            }else throw DatabaseException(query.lastError().text());
        } catch (ValidatorException& v) {
            v.view();
        } catch(DatabaseException& d){
            d.view();
        }

    }
}

void DialogGenero::on_listagenero_doubleClicked(const QModelIndex &index)
{
    QString genEdit=ui->listagenero->item(index.row())->text();
    ui->pushButton->setText("Guardar");
    ui->newGenero->setText(genEdit);
    temp=genEdit;
    ui->pushButton_2->show();
    ui->pushButton_3->show();
}

void DialogGenero::on_pushButton_2_clicked()
{
    ui->pushButton->setText("Agregar \nGenero");
    ui->pushButton_2->hide();
    ui->pushButton_3->hide();
    ui->newGenero->setText("");
}

void DialogGenero::on_pushButton_3_clicked()
{
    QSqlQuery query;
    query.prepare("DELETE FROM Genero where (nombre='"+temp+"')");
    if(query.exec()){
        qDebug()<<"Eliminado";
        ui->newGenero->setText("");

    }else
        qDebug()<<"error";
    ui->pushButton->setText("Agregar \nGenero");
    ui->pushButton_2->hide();
    ui->pushButton_3->hide();
    ui->newGenero->setText("");
    ui->listagenero->clear();
    QSqlQuery query2("SELECT * FROM Genero ", db);
    if(!(query2.size()==0)){
        while(query2.next()){
            QString gen=query2.value(1).toString();
            ui->listagenero->addItem(gen);
        }
    }
}
