#include <string>
#include "Cliente.h"
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QDateTime>
#include <QMessageBox>
#include <databaseexception.h>

using namespace std;


Cliente::Cliente(int id, QString nom, QString ape, QString user, QString pass, int ed, QString rol, QString tarid){
    registrar_nombre(nom);
    registrar_edad(ed);
    registrar_usuario(user);
    registrar_contrasenia(pass);
    registrar_tipo(rol);
    registrar_id(id);
    registrar_apellido(ape);
    tarjid=tarid;
}

int Cliente::guardar(QSqlDatabase* db)
{

    try {
        if(!db->open()) throw DatabaseException("Error de base de datos");
        QSqlQuery search;
        search.prepare("select *  from persona where username='"+this->obtener_usuario()+"'");
        qDebug()<<"select * from persona where username='"+this->obtener_usuario()+"'";
        if(!search.exec())  throw DatabaseException(search.lastError().text());
        if(search.size()>0)     throw DatabaseException("Nombre de usuario existente");


        QSqlQuery save;
        save.prepare("INSERT INTO persona (nombre, edad, rol_id, username, pass, apellido) VALUES('"+
                     this->obtener_nombre()+"', "+QString::number(this->obtener_edad())+", "+this->obtener_tipo()+
                     ", '"+this->obtener_usuario()+"', '"+this->obtener_contrasenia()+"', '"+this->obtener_apellido()+"')");

        if(!save.exec())    throw DatabaseException("Ha ocurrido un error en la insercion"+save.lastError().text());

        else    {
            QMessageBox::information(nullptr, "Exito", "Registrado", QMessageBox::Ok);
            QSqlQuery searchf;
            searchf.prepare("select * from persona where username='"+this->obtener_usuario()+"'");
            if(!searchf.exec())  throw DatabaseException("Ha ocurrido un error");
            searchf.next();
            qDebug()<<searchf.value(0).toInt()<<" -->  user guardado";
            return searchf.value(0).toInt();
        }
    } catch (DatabaseException& d) {
        d.view();
        return 0;
    }





}



bool Cliente::agregar_reserva(Sala* l, Hora* h, Pelicula *p, QString dia, QString sillas, double total)
{

    QString dia_id="";

    //Obtenemos el id del dia;
    try {
        QSqlQuery diaid;
        diaid.prepare("select id_dia from dia where name='"+dia+"'");
        if(diaid.exec()){
            diaid.next();
            dia_id=diaid.value(0).toString();
        }else throw DatabaseException(diaid.lastError().text());

    } catch (DatabaseException& d) {
        d.view();
        return false;
    }

    //obtenemos la fecha actual
    QDate hoydate=QDateTime::currentDateTime().date();
    QString hoy=QString::number(hoydate.year())+"-"+QString::number(hoydate.month())+"-"+QString::number(hoydate.day());

    //Insertamos reserva
    try {
        QSqlQuery res;
        res.prepare("INSERT INTO reserva (persona_id, dia_id, fecha, pelicula_id, sillas, total, sala, hora) VALUES ("+
                    QString::number(this->obtener_id())+", "+dia_id+", '"+hoy+"', "+QString::number(p->obtener_id())+
                    ", '"+sillas+"', "+QString::number(total)+", '"+QString::number(l->obtener_id())+"', '"+
                    h->obtener_descripcion()+"')");


        if(res.exec()){
            QMessageBox::information(nullptr, "Exito", "Reserva agregada", QMessageBox::Ok);
            return true;
        }else throw DatabaseException(res.lastError().text());

    } catch (DatabaseException& d) {
        d.view();
        return false;
    }

}

bool Cliente::guardar_tarjeta(QString numero, QString tipo, QString prop, QString fven, QString cvv, QString ape)
{
    QString idtarjeta="";
    //Validacion
        //Si fuera una tarjeta real
    //fin validacion


    try {
        //consultamos existencia
        QSqlQuery tarver;
        tarver.prepare("select id_tarjeta from tarjeta where numero='"+numero+"'");

        if(tarver.exec()){

            if(tarver.size()==0){
                //En caso no exista la tarjeta en la bd
                    //Insertamos la tarjeta
                QSqlQuery tar;
                tar.prepare("INSERT INTO tarjeta (numero, tipo, propietario, fechaven, cvv, ProApellido) VALUES ('"+
                            numero+"', '"+tipo+"', '"+prop+"', '"+fven+"', '"+cvv+"', '"+ape+"')");

                if(tar.exec()){

                    //obtenemos el id de la tarjeta insertada
                    QSqlQuery tarver2;
                    tarver2.prepare("select id_tarjeta from tarjeta where numero='"+numero+"'");
                    tarver2.exec();
                    tarver2.next();
                    idtarjeta=tarver2.value(0).toString();

                }else throw DatabaseException(tar.lastError().text());


            }else{
                tarver.next();
                idtarjeta=tarver.value(0).toString();
            }


        }else   throw DatabaseException(tarver.lastError().text());

    } catch (DatabaseException& e) {
        e.view();
        return false;
    }

    //asiganamos la tarjeta al ususario
    try {
        QSqlQuery addtar;
        addtar.prepare("UPDATE persona SET tarjeta_id ="+idtarjeta+" WHERE (id_persona = "+QString::number(this->obtener_id())+");");

        if(addtar.exec()){
            this->tarjid=idtarjeta;
            QMessageBox::information(nullptr, "Exito", "Tarjeta Guardada", QMessageBox::Ok);
            return true;
        }else throw DatabaseException(addtar.lastError().text());

    } catch (DatabaseException& e) {
        e.view();
    }
    return false;

}

QString Cliente::obtener_tarjeta_id()
{
    return tarjid;
}

