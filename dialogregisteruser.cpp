#include "dialogregisteruser.h"
#include "ui_dialogregisteruser.h"
#include <validatorexception.h>
#include <Cliente.h>
#include <QMessageBox>
#include <QDebug>
#include <conexionmysql.h>
#include <QSqlDatabase>
#include <dialogpago.h>

DialogRegisterUser::DialogRegisterUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogRegisterUser)
{
    ui->setupUi(this);

    ConexionMySQL s;
    db = QSqlDatabase::addDatabase(s.dbt);
    db.setHostName(s.hostdb);
    db.setDatabaseName(s.dbname);
    db.setUserName(s.usernamedb);
    db.setPassword(s.passdb);

    if (!db.open()) {
        qDebug()<<"Error en base de datos";
        QMessageBox::warning(nullptr, tr("Error"), tr("No hay conexion a internet\t\t"),QMessageBox::Ok);
        return;
    }    else qDebug()<<"Conectado";

    ui->lineUser->setMaxLength(60);
    ui->lineApellido->setMaxLength(60);
    ui->lineEdad->setInputMask("09");
    ui->lineContra->setMaxLength(50);

}

DialogRegisterUser::~DialogRegisterUser()
{
    delete ui;
}

void DialogRegisterUser::on_pushButtonRegister_clicked()
{
    QString user=ui->lineUser->text();
    QString nom=ui->lineNombre->text();
    QString ape=ui->lineApellido->text();
    QString pass=ui->lineContra->text();
    QString edad=ui->lineEdad->text();

    //validamoa los campos

    try {
        if(user.isEmpty())  throw ValidatorException("Nombre de usuario vacio");
        else if(nom.isEmpty())   throw ValidatorException("Nombre vacio");
        else if(ape.isEmpty())   throw ValidatorException("Apellido, vacio");
        else if(pass.length()<4)    throw ValidatorException("Contraseña demaciada corta");
        else if(edad.isEmpty()) throw ValidatorException("Edad vacia");

        //guardaos el usuario

        Cliente* cli=new Cliente(0, nom, ape, user, pass, edad.toInt(), "2", "");
        int id=cli->guardar(&db);
        if(id==0)   this->close();
        cli->registrar_id(id);
        qDebug()<<id;


        QMessageBox msgBox;
        msgBox.setText("No tiene una tarjeta para el sistema.\n¿Desea guardar una?");
        QPushButton *connectButton = msgBox.addButton(tr("Si"), QMessageBox::ActionRole);
        QPushButton *abortButton = msgBox.addButton(tr("No"), QMessageBox::ActionRole);
        msgBox.exec();

        if (msgBox.clickedButton() == abortButton) {
            this->close();
        } else if (msgBox.clickedButton() == connectButton) {
            bool res=false;
            dialogPago* pag=new dialogPago(cli, &res);
            pag->exec();
            this->close();
        }


    } catch (ValidatorException& v) {
        v.view();
    }

}

void DialogRegisterUser::on_pushButtonCancelar_clicked()
{
    this->close();
}
