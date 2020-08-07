#include "login.h"
#include "ui_login.h"
#include "peliwindow.h"
#include <iostream>
#include <QtSql/QSqlDatabase>
#include <QtSql>
#include <QDebug>
#include <QSqlQuery>
#include <adminwindow.h>
#include "Administrador.h"
#include "Cliente.h"
#include "QMessageBox"
#include "conexionmysql.h"
#include "dialogloading.h"
#include <dialogregisteruser.h>


using namespace  std;
Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    loa=new DialogLoading("Iniciando sesion...");
    loa->show();
    loa->move(1000, 1000);
    connect(this, &Login::actualizarV, loa, &DialogLoading::actualizar);
}

Login::~Login()
{
    delete ui;
}

void Login::on_loginbutton_clicked()
{


    int px=this->x()+(this->width()-loa->width())/2;
    int py=this->y()+this->height()/2;
    loa->move(px, py);

    ConexionMySQL s;
    db = QSqlDatabase::addDatabase(s.dbt);
    db.setHostName(s.hostdb);
    db.setDatabaseName(s.dbname);
    db.setUserName(s.usernamedb);
    db.setPassword(s.passdb);
    emit actualizarV(15);
    if (!db.open()) {
        qDebug()<<"Error en base de datos";
        QMessageBox::warning(nullptr, tr("Error"), tr("No hay conexion a internet\t\t"),QMessageBox::Ok);
        return;
    }    else qDebug()<<"Conectado";
    emit actualizarV(30);
    QString us=ui->user->text();
    QString pass=ui->pass->text();
    QSqlQuery query("SELECT * FROM Persona WHERE username='"+us+"' AND pass='"+pass+"'", db);
    emit actualizarV(50);
    if(query.size()==0){
        qDebug()<<"Usuario no encontrado";
        emit actualizarV(70);
        QMessageBox::warning(nullptr, tr("Error"), tr("Usuario no encontrado\t\t"),QMessageBox::Ok);
    }else{
        query.next();
        if(query.value(3).toString().compare("1")==0){
            Administrador *ad=new Administrador(query.value(1).toString(), query.value(4).toString(), query.value(5).toString(), query.value(2).toInt(), query.value(3).toString());
            AdminWindow *adm=new AdminWindow(nullptr, ad);
            adm->show();
        }else{
            Cliente *cl=new Cliente(query.value(0).toInt(), query.value(1).toString(), query.value(7).toString(), query.value(4).toString(), query.value(5).toString(), query.value(2).toInt(), query.value(3).toString(), query.value(6).toString());
            PeliWindow *ma=new PeliWindow(nullptr, cl);
            ma->show();
        }
        emit actualizarV(100);
        loa->close();
        this->close();
    }

}

void Login::on_pushButtonRegister_clicked()
{
    DialogRegisterUser* reg=new DialogRegisterUser();
    reg->setModal(true);
    reg->exec();
}
