#include "Sala.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QTableWidgetItem>
#include <QMessageBox>
#include <QSqlError>
#include <dialogloading.h>
#include <databaseexception.h>


void Sala::espablecer_id(int id){
    idSala=id;
}

void Sala::establecer_tipo_de_sala(QString tp){
    tipo_de_sala=tp;
}

void Sala::establecer_numero_de_sillas(int ns){
    numero_de_sillas=ns;
}

void Sala::mostrarDia(QString dia,int column, Hora *arr, int size, QTableWidget *tabla)
{
    try {
        QSqlQuery queryJ;
        queryJ.prepare("SELECT * FROM "+dia+" WHERE sala_id="+QString::number(this->obtener_id()));
        if(!queryJ.exec())  throw DatabaseException(queryJ.lastError().text());
        if(!(queryJ.size()==0)){
            while (queryJ.next()) {
                for (int hi=0;hi<size;hi++) {
                    if(queryJ.value(1).toInt()==arr[hi].obtener_id()){
                        QTableWidgetItem *iTemp;
                        iTemp=new QTableWidgetItem();
                        QSqlQuery queryPeli;
                        queryPeli.prepare("SELECT * FROM pelicula WHERE id_pelicula="+queryJ.value(2).toString());
                        queryPeli.exec();
                        queryPeli.next();
                        iTemp->setText(queryPeli.value(1).toString());
                        tabla->setItem(hi, column, iTemp);
                        break;
                    }
                }

            }
        }

    } catch (DatabaseException& d) {
        d.view();
    }

}

void Sala::eliminarSalaDia(QString dia)
{
    try {
        QSqlQuery queryL;
        queryL.prepare("DELETE FROM "+dia+" WHERE sala_id="+QString::number(this->obtener_id()));
        if(!queryL.exec())  throw DatabaseException(queryL.lastError().text());

    } catch (DatabaseException& d) {
        d.view();
    }


}

void Sala::asignarPelicula(Pelicula *peliinto, QString dia, int hora_id)
{
    qDebug()<<"entro asignar";
    QSqlQuery rev;
    rev.prepare("SELECT * FROM "+dia+" WHERE sala_id="+QString::number(this->obtener_id())+" AND hora_id="+QString::number(hora_id));
    rev.exec();

    QString sillasdefault="";
    for (int z=0;z<this->obtener_numero_de_sillas();++z) {
        sillasdefault=sillasdefault+"L";
    }
    qDebug()<<"sillas correcxtas";
    if(rev.size()==0){
        QSqlQuery query;
        QString consulta="INSERT INTO "+dia+" (sala_id, hora_id, pelicula_id, sillasreg) VALUES ("+QString::number(this->obtener_id())+
                ", "+QString::number(hora_id)+", "+QString::number(peliinto->obtener_id())+", '"+sillasdefault+"')";
        query.prepare(consulta);
        bool as=query.exec();
        QString error=query.lastError().text();
        if(!as){
            qDebug()<<"Error en BD";
            return;
        }else{
            QMessageBox::information(nullptr, "Informacion", "Pelicula asignada",QMessageBox::Ok);
            return;
        }
    }else{
        rev.next();
        QSqlQuery query;
        query.prepare("UPDATE "+dia+" SET pelicula_id="+QString::number(peliinto->obtener_id())+
                      ", sillasreg='"+sillasdefault+"', sillasOcu=0 WHERE id="+rev.value(5).toString());
        if(!query.exec()){
            qDebug()<<"Error en BD";
            return;
        }else{
            QMessageBox::information(nullptr, "Informacion", "Pelicula actualizada",QMessageBox::Ok);
            return;
        }
    }
}

void Sala::limpiarPelicula(QString dia, int hora_id)
{
    try {
        QSqlQuery queryL;
        queryL.prepare("DELETE FROM "+dia+" WHERE sala_id="+QString::number(this->obtener_id())+" AND hora_id="+QString::number(hora_id));
        if(!queryL.exec())  throw DatabaseException(queryL.lastError().text());
        else QMessageBox::information(nullptr, "Informacion", "Hora limpiada",QMessageBox::Ok);

    } catch (DatabaseException& d) {
        d.view();
    }
}


int Sala::obtener_id(){
    return  idSala;
}

QString Sala::obtener_tipo_de_sala(){
    return tipo_de_sala;
}

int Sala::obtener_numero_de_sillas(){
    return numero_de_sillas;
}
