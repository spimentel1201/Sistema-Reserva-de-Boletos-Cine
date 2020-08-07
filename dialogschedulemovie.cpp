#include "dialogschedulemovie.h"
#include "ui_dialogschedulemovie.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>
#include <QDebug>
#include <dialogchairavailable.h>
#include <peliculaprogramada.h>
#include <databaseexception.h>



DialogScheduleMovie::DialogScheduleMovie(QWidget *parent, QSqlDatabase* dbinto, Pelicula* p, Cliente* userinto) :
    QDialog(parent),
    ui(new Ui::DialogScheduleMovie)
{
    ui->setupUi(this);
    db=dbinto;
    peli=p;
    user=userinto;

    //llenamos la vista
    idlunes=this->llenar("lunesprog", ui->listLunes);
    idmartes=this->llenar("martesprog", ui->listMartes);
    idmiercoles=this->llenar("miercolesprog", ui->listMiercoles);
    idjueves=this->llenar("juevesprog", ui->listJueves);
    idviernes=this->llenar("viernesprog", ui->listViernes);
    idsabado=this->llenar("sabadoprog", ui->listSabado);
    iddomingo=this->llenar("domingoprog", ui->listDomingo);

}

DialogScheduleMovie::~DialogScheduleMovie()
{
    delete ui;
}

void DialogScheduleMovie::on_listLunes_doubleClicked(const QModelIndex &index)
{
    this->reservar(index.row(), "lunes", "lunesprog", idlunes);
}

void DialogScheduleMovie::on_listMartes_doubleClicked(const QModelIndex &index)
{
    this->reservar(index.row(), "martes", "martesprog", idmartes);
}

void DialogScheduleMovie::on_listMiercoles_doubleClicked(const QModelIndex &index)
{
    this->reservar(index.row(), "miercoles", "miercolesprog", idmiercoles);
}


void DialogScheduleMovie::on_listJueves_doubleClicked(const QModelIndex &index)
{
    this->reservar(index.row(), "jueves", "juevesprog", idjueves);
}



void DialogScheduleMovie::on_listViernes_doubleClicked(const QModelIndex &index)
{
    this->reservar(index.row(), "viernes", "viernesprog", idviernes);
}


void DialogScheduleMovie::on_listSabado_doubleClicked(const QModelIndex &index)
{
    this->reservar(index.row(), "sabado", "sabadoprog", idsabado);
}


void DialogScheduleMovie::on_listDomingo_doubleClicked(const QModelIndex &index)
{

    this->reservar(index.row(), "domingo", "domingoprog", iddomingo);
}

QString* DialogScheduleMovie::llenar(QString diaview, QListWidget *l)
{

    QString *idday=nullptr;
    //Seleccionamos las programaciones de la pelicula en la semana en diferentes salAs
    try {
        QSqlQuery diaq;
        diaq.prepare("select * from "+diaview+" where pelicula_id="+QString::number(peli->obtener_id()));
        if(diaq.exec()){
            int cant=0;

            //guardamos los id de cada programacion para el dia
            idday=new QString[diaq.size()];

            //LLENAMOS EL LISTVIEW
            while(diaq.next()){
                QListWidgetItem *tmmp=new QListWidgetItem;
                tmmp->setSizeHint(QSize(0,60));

                tmmp->setText("SALA "+diaq.value(1).toString()+": "+diaq.value(3).toString());

                tmmp->setTextAlignment(Qt::AlignCenter);
                tmmp->setFont(QFont("MS Reference Sans Serif", 18, QFont::Bold));

                //Direfenciamos por tipo de sala
                if(diaq.value(5).toString().compare("B")==0)    tmmp->setBackground(QColor(252, 255, 254));
                else    tmmp->setBackground(QColor("#efb810"));
                *(idday+cant)=diaq.value(0).toString();
                cant++;
                l->addItem(tmmp);
            }

        }else   throw DatabaseException(diaq.lastError().text());


    } catch (DatabaseException& d) {
        d.view();
    }
    return idday;

}

void DialogScheduleMovie::reservar(int index, QString dia, QString diaview, QString *idday)
{

    QSqlQuery prog;
    prog.prepare("select * from "+diaview+" where id="+idday[index]);
    if(prog.exec()){
        prog.next();
        Sala* sala=new Sala;
        sala->espablecer_id(prog.value(1).toInt());
        sala->establecer_tipo_de_sala(prog.value(5).toString());
        sala->establecer_numero_de_sillas(prog.value(6).toInt());

        Hora* hora=new Hora;
        hora->obtener_id();
        hora->establecer_descripcion(prog.value(3).toString());

        PeliculaProgramada* peliprog=new PeliculaProgramada(peli,sala, hora, dia, idday[index].toInt());
        DialogChairAvailable* sillaDis=new DialogChairAvailable(nullptr, peliprog, db, user);

        sillaDis->exec();
    }
}
