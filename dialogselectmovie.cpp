#include "dialogselectmovie.h"
#include "ui_dialogselectmovie.h"
#include "conexionmysql.h"
#include <QDebug>
#include <QSqlQuery>
#include <QMessageBox>
#include <databaseexception.h>

DialogSelectMovie::DialogSelectMovie(QWidget *parent, Sala* salainto, QString dia, int hora) :
    QDialog(parent),
    ui(new Ui::DialogSelectMovie)
{
    ui->setupUi(this);
    sala=salainto;
    nom_dia=dia;
    id_hora=hora;

    ConexionMySQL s;
    db = QSqlDatabase::addDatabase(s.dbt);
    db.setHostName(s.hostdb);
    db.setDatabaseName(s.dbname);
    db.setUserName(s.usernamedb);
    db.setPassword(s.passdb);
    if (!db.open()) qDebug()<<"Error en base de datos";
    else qDebug()<<"Conectado Pelis";
    QSqlQuery query("SELECT * FROM pelicula ", db);
    if(query.size()==0){
        qDebug()<<"Vacio";
    }else{
        peliarr=new Pelicula[query.size()]();
        int pc=0;
        while(query.next()){
            QString pel=query.value(1).toString();
            peliarr[pc].establecer_id(query.value(0).toInt());
            ui->listMovie->addItem(pel);
            pc++;
        }
        QString pel="(Ninguno)";
        peliarr[pc].establecer_id(0);
        ui->listMovie->addItem(pel);
        pc++;
    }
}

DialogSelectMovie::~DialogSelectMovie()
{
    delete ui;
}

void DialogSelectMovie::on_listMovie_doubleClicked(const QModelIndex &index)
{

    int diaN=index.row();
    if(peliarr[diaN].obtener_id()==0){
        sala->limpiarPelicula(nom_dia, id_hora);
    }else{
        sala->asignarPelicula(&peliarr[diaN], nom_dia, id_hora);
    }



    this->close();

}
