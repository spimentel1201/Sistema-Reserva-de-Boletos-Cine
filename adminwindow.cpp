#include "adminwindow.h"
#include "ui_adminwindow.h"
#include "genero.h"
#include "idiomawindow.h"
#include "dialogaddmovie.h"
#include "QSqlDatabase"
#include "QSqlQuery"
#include "QDebug"
#include "login.h"
#include "QSqlTableModel"
#include "dialoggenero.h"
#include "dialogidioma.h"
#include "conexionmysql.h"
#include "QMessageBox"
#include "Pelicula.h"
#include "string"
#include "dialogeditmovie.h"
#include <dialogadminsala.h>
#include <dialogaddsala.h>
#include <databaseexception.h>


AdminWindow::AdminWindow(QWidget *parent, Administrador *per) :
    QMainWindow(parent),
    ui(new Ui::AdminWindow)
{
    ui->setupUi(this);
    admi=per;
    ui->userbutton->setText(per->obtener_usuario());
    listai=new QVBoxLayout();

    try {
        //nos conectamos a la base de datos
        ConexionMySQL s;
        db = QSqlDatabase::addDatabase(s.dbt);
        db.setHostName(s.hostdb);
        db.setDatabaseName(s.dbname);
        db.setUserName(s.usernamedb);
        db.setPassword(s.passdb);
        if (!db.open()) throw DatabaseException(db.lastError().text());

    } catch (DatabaseException& d) {
        d.view();
    }


    //Peliculas

    QSqlQuery query("SELECT * FROM Pelicula ", db);
    if(!(query.size()==0)){
        model=new QSqlQueryModel();
        model->setQuery(query);
        ui->pelitable->setModel(model);
        ui->pelitable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->pelitable->hideColumn(0);
    }

    //Salas

    QSqlQuery query2("SELECT * FROM Sala ", db);
    if(!(query2.size()==0)){
        salaarr=new Sala[query2.size()]();
        int c=0;
        while(query2.next()){
            salaarr[c].espablecer_id(query2.value(0).toInt());
            salaarr[c].establecer_numero_de_sillas(query2.value(1).toInt());
            salaarr[c].establecer_tipo_de_sala(query2.value(2).toString());

            QListWidgetItem *tmmp=new QListWidgetItem;
            tmmp->setSizeHint(QSize(0,60));

            tmmp->setText("SALA "+query2.value(0).toString());
            tmmp->setTextAlignment(Qt::AlignCenter);
            tmmp->setFont(QFont("MS Reference Sans Serif", 18, QFont::Bold));
            if(salaarr[c].obtener_tipo_de_sala().compare("B")==0)    tmmp->setBackground(QColor(252, 255, 254));
            else    tmmp->setBackground(QColor("#efb810"));

            //Agreagmos la sala a la vista
            ui->listSala->addItem(tmmp);
            c++;
        }
    }


    //USUARIOS
    userModel=new QSqlTableModel(this);
    userModel->setTable("persona");
    userModel->select();
    ui->tableUser->setModel(userModel);


    //reservas
    this->queryReserva(lunesModel, ui->tablelunes, 1);
    this->queryReserva(martesModel, ui->tablemartes, 2);
    this->queryReserva(miercolesModel, ui->tablemiercoles, 3);
    this->queryReserva(juevesModel, ui->tablejueves, 4);
    this->queryReserva(viernesModel, ui->tableviernes, 5);
    this->queryReserva(sabadoModel, ui->tablesabado, 6);
    this->queryReserva(domingoModel, ui->tabledomingo, 7);



}

AdminWindow::~AdminWindow()
{
    delete ui;
}

void AdminWindow::actualizarPeliculas()
{
    //Actualizamos peliculas
    QSqlQuery query("SELECT * FROM Pelicula ", db);
    model->setQuery(query);
}

void AdminWindow::actualizarUsuarios()
{
    userModel=new QSqlTableModel(this);
    userModel->setTable("persona");
    userModel->select();
    ui->tableUser->setModel(userModel);
}

void AdminWindow::queryReserva(QSqlQueryModel *qm, QTableView *tabla,int d)
{
    qm=new QSqlQueryModel;
    string consulta = "SELECT * FROM reserva where dia_id=" + std::to_string(d);
    qm->setQuery(consulta.c_str());
    tabla->setModel(qm);
}

void AdminWindow::on_pushButton_3_clicked()
{
    DialogGenero generowindow(db);
    generowindow.setModal(true);
    generowindow.exec();

    this->actualizarPeliculas();
    this->actualizarUsuarios();
}

void AdminWindow::on_pushButton_2_clicked()
{
    DialogIdioma idiomawindow(db);
    idiomawindow.setModal(true);
    idiomawindow.exec();

    this->actualizarPeliculas();
    this->actualizarUsuarios();
}

void AdminWindow::on_pushButton_clicked()
{
    DialogAddMovie peliwindow(db);
    peliwindow.setModal(true);
    peliwindow.exec();

    this->actualizarPeliculas();
    this->actualizarUsuarios();
}

void AdminWindow::on_options_clicked()
{
    Login *l=new Login();
    l->show();
    this->close();
}


void AdminWindow::on_pelitable_doubleClicked(const QModelIndex &index)
{
    int fila=index.row();
    Pelicula* temp=new Pelicula();
    QSqlQuery query("SELECT * FROM Pelicula where id_pelicula="+index.model()->index(fila,0).data().toString(), db);
    query.next();
    temp->establecer_id(query.value(0).toInt());
    temp->establecer_titulo(query.value(1).toString());
    temp->establecer_duracion(query.value(2).toInt());
    temp->establecer_director(query.value(3).toString());
    temp->establecer_sinopsis(query.value(4).toString());
    temp->establecer_estado(query.value(5).toChar());
    temp->establecer_precio(query.value(6).toDouble());
    DialogEditMovie edit(db, temp);
    edit.setModal(true);
    edit.exec();

    this->actualizarPeliculas();
    this->actualizarUsuarios();
}


void AdminWindow::on_listSala_clicked(const QModelIndex &index)
{
    DialogAdminSala *saladialog=new DialogAdminSala(&db, nullptr, &salaarr[index.row()]);
    saladialog->setModal(true);
    saladialog->exec();

    this->actualizarPeliculas();
    this->actualizarUsuarios();

    //Actualñizar Sala
    QSqlQuery query2("SELECT * FROM Sala ", db);
    if(!(query2.size()==0)){
        ui->listSala->clear();
        salaarr=new Sala[query2.size()]();
        int c=0;
        while(query2.next()){
            salaarr[c].espablecer_id(query2.value(0).toInt());
            salaarr[c].establecer_numero_de_sillas(query2.value(1).toInt());
            salaarr[c].establecer_tipo_de_sala(query2.value(2).toString());

            QListWidgetItem *tmmp=new QListWidgetItem;
            tmmp->setSizeHint(QSize(0,60));

            tmmp->setText("SALA "+query2.value(0).toString());
            tmmp->setTextAlignment(Qt::AlignCenter);
            tmmp->setFont(QFont("MS Reference Sans Serif", 18, QFont::Bold));
            if(salaarr[c].obtener_tipo_de_sala().compare("B")==0)    tmmp->setBackground(QColor(252, 255, 254));
            else    tmmp->setBackground(QColor("#efb810"));

            ui->listSala->addItem(tmmp);
            qDebug()<<salaarr[c].obtener_id();
            c++;
        }
    }
}

void AdminWindow::on_pushButton_4_clicked()
{
    DialogAddSala salaadddialog(db);
    salaadddialog.setModal(true);
    salaadddialog.exec();

    this->actualizarPeliculas();
    this->actualizarUsuarios();

    //Actualizar Sala
    QSqlQuery query2("SELECT * FROM Sala ", db);
    if(!(query2.size()==0)){
        ui->listSala->clear();
        salaarr=new Sala[query2.size()]();
        int c=0;
        while(query2.next()){
            salaarr[c].espablecer_id(query2.value(0).toInt());
            salaarr[c].establecer_numero_de_sillas(query2.value(1).toInt());
            salaarr[c].establecer_tipo_de_sala(query2.value(2).toString());

            QListWidgetItem *tmmp=new QListWidgetItem;
            tmmp->setSizeHint(QSize(0,60));

            tmmp->setText("SALA "+query2.value(0).toString());
            tmmp->setTextAlignment(Qt::AlignCenter);
            tmmp->setFont(QFont("MS Reference Sans Serif", 18, QFont::Bold));
            if(salaarr[c].obtener_tipo_de_sala().compare("B")==0)    tmmp->setBackground(QColor(252, 255, 254));
            else    tmmp->setBackground(QColor("#efb810"));

            ui->listSala->addItem(tmmp);
            qDebug()<<salaarr[c].obtener_id();
            c++;
        }
    }

}

void AdminWindow::on_pushNewUser_clicked()
{
    userModel->insertRow(userModel->rowCount());
}

void AdminWindow::on_pushDelUser_clicked()
{
    userModel->removeRow(ui->tableUser->currentIndex().row());
}

void AdminWindow::on_pushUpdate_clicked()
{
    bool ac=userModel->submitAll();
    qDebug()<<ac<<" "<<userModel->lastError().text();
    userModel->select();
}
