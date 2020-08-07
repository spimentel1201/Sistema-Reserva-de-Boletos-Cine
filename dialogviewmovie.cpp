#include "dialogviewmovie.h"
#include "ui_dialogviewmovie.h"
#include <QDebug>
#include <dialogschedulemovie.h>

DialogViewMovie::DialogViewMovie(QWidget *parent, Pelicula* p, QSqlDatabase* dbinto, Cliente* userinto) :
    QDialog(parent),
    ui(new Ui::DialogViewMovie)
{

    ui->setupUi(this);
    peli=p;
    db=dbinto;
    user=userinto;

    //Mostramos datos
    ui->lblTitulo->setText(peli->obtener_titulo());
    ui->lblSinopsis->setText(peli->obtener_sinopsis());
    ui->lblPrecio->setText(QString::number(peli->obtener_precio()));
    ui->lblDirector->setText(peli->obtener_director());
    ui->lblDuracion->setText(QString::number(peli->obtener_duracion()));

    QString qss = "font: 1pt;"
                   "background-color: #0db2f8;"
                   "image: url(img/"+QString::number(peli->obtener_id())+")";
    ui->lblImagen->setStyleSheet(qss);
}

DialogViewMovie::~DialogViewMovie()
{
    delete ui;
}

void DialogViewMovie::on_pushButton_clicked()
{
    //mostramos horarios
    DialogScheduleMovie hora(nullptr, db,peli, user);
    hora.exec();
}
