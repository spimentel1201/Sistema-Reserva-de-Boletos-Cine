#include "peliwindow.h"
#include "ui_peliwindow.h"
#include "QGridLayout"
#include "QPushButton"
#include "QSqlDatabase"
#include "QSqlQuery"
#include "QDebug"
#include "login.h"
#include "dialogreservas.h"
#include "conexionmysql.h"
#include <dialogviewmovie.h>
#include <databaseexception.h>

PeliWindow::PeliWindow(QWidget *parent, Cliente *cl) :
    QMainWindow(parent),
    ui(new Ui::PeliWindow)
{
    ui->setupUi(this);
    clie=cl;
    ui->userbutton->setText(clie->obtener_usuario());

    clie=cl;

    //Nos conectamos a la base de datos
    try {
        ConexionMySQL s;
        db = QSqlDatabase::addDatabase(s.dbt);
        db.setHostName(s.hostdb);
        db.setDatabaseName(s.dbname);
        db.setUserName(s.usernamedb);
        db.setPassword(s.passdb);
        if (!db.open()) throw DatabaseException(db.lastError().text());


        QSqlQuery query("SELECT * FROM Pelicula where estado='A'", db);
        if(!(query.size()==0)){
            QGridLayout *ele=new QGridLayout(this);
            int i=0;
            int cm=0;
            ct=query.size();
            moviearr=new MovieLabel[query.size()]();
            id=new QString[query.size()]();
            for(int j=0;j<5&&query.next();j++){
                id[cm]=query.value(0).toString();
                QString nom=query.value(1).toString();

                //creamos un objeto pelicula
                Pelicula* tmp=new Pelicula;
                tmp->establecer_id(query.value(0).toInt());
                tmp->establecer_titulo(query.value(1).toString());
                tmp->establecer_duracion(query.value(2).toInt());
                tmp->establecer_director(query.value(3).toString());
                tmp->establecer_sinopsis(query.value(4).toString());
                tmp->establecer_estado(query.value(5).toChar());
                tmp->establecer_precio(query.value(6).toDouble());
                moviearr[cm].setContent(tmp);
                moviearr[cm].setText(id[cm]);
                moviearr[cm].setMinimumSize(20, 200);

                QString qss = "font: 1pt;"
                              "background-color: #0db2f8;"
                              "image: url(img/"+query.value(0).toString()+")";
                moviearr[cm].setStyleSheet(qss);

                //conectamos los label con la accion de mostrar
                connect(&moviearr[cm], &MovieLabel::mouse_Pressed, [&](Pelicula* p){
                    qDebug()<<p->obtener_id();
                    DialogViewMovie dataMovie(this, p, &db, clie);
                    dataMovie.exec();
                });


                //añadimos el label de la pelicula
                ele->addWidget(&moviearr[cm], i, j);
                cm++;
                if(j==4) {
                    i++;
                    j=-1;
                }
            }
            //guardamos en la vista
            ui->peli_lista->setLayout(ele);
        }

    } catch (DatabaseException& d) {
        d.view();
    }


}

PeliWindow::~PeliWindow()
{
    delete ui;
}

void PeliWindow::on_options_clicked()
{
    Login *l=new Login();
    l->show();
    this->close();
}


void PeliWindow::on_userbutton_clicked()
{
    DialogReservas dataReservas(this, &db, clie);
    dataReservas.setModal(true);
    dataReservas.exec();
}
