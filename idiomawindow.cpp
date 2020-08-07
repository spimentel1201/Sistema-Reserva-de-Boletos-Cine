#include "idiomawindow.h"
#include "ui_idiomawindow.h"
#include "QSqlDatabase"
#include "QSqlQuery"
#include "QDebug"

IdiomaWindow::IdiomaWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::IdiomaWindow)
{
    ui->setupUi(this);
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("sql10.freesqldatabase.com");
    db.setDatabaseName("sql10352486");
    db.setUserName("sql10352486");
    db.setPassword("9BPgk6jrLt");
    if (!db.open()) qDebug()<<"Error en base de datos";
    else qDebug()<<"Conectado Idiomas";
    QSqlQuery query("SELECT * FROM Idioma ", db);
    if(query.size()==0){
        qDebug()<<"Vacio";
    }else{
        while(query.next()){
            QString idi=query.value(1).toString();
            ui->listaIdioma->addItem(idi);
        }
    }
}

IdiomaWindow::~IdiomaWindow()
{
    delete ui;
}

void IdiomaWindow::on_pushButton_clicked()
{
    QString idioma=ui->newIdioma->text();
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("sql10.freesqldatabase.com");
    db.setDatabaseName("sql10352486");
    db.setUserName("sql10352486");
    db.setPassword("9BPgk6jrLt");
    if (!db.open()) qDebug()<<"Error en base de datos";
    else qDebug()<<"Conectado Idiomas";
    QSqlQuery query;
    query.prepare("INSERT INTO Idioma (nombre) VALUES ('"+idioma+"')");
    if(query.exec()){
        qDebug()<<"Insertado";
        ui->listaIdioma->addItem(idioma);
        ui->newIdioma->setText("");

    }else
        qDebug()<<"error";

}
