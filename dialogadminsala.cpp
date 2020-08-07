#include "dialogadminsala.h"
#include "ui_dialogadminsala.h"
#include <conexionmysql.h>
#include <QDebug>
#include <QSqlQuery>
#include <dialogselectmovie.h>
#include <QMessageBox>
#include <QSqlError>
#include <dialogloading.h>

DialogAdminSala::DialogAdminSala(QSqlDatabase *dbinto, QWidget *parent, Sala *salainto) :
    QDialog(parent),
    ui(new Ui::DialogAdminSala)
{
    ui->setupUi(this);

    //Barra para eliminaciones
    loa=new DialogLoading("Eliminando...", this);
    loa->show();
    loa->move(1000, 1000);
    connect(this, &DialogAdminSala::actualizarV, loa, &DialogLoading::actualizar);


    sala=salainto;
    this->setWindowTitle("Sala "+QString::number(sala->obtener_id()));
    db=*dbinto;

    //Peliculas

    QSqlQuery query("SELECT * FROM hora ", db);
    if(query.size()==0){
        qDebug()<<"Vacio";
    }else{
        ui->tableHora->setColumnCount(7);
        ui->tableHora->setRowCount(query.size());
        QStringList colLabels = {"Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado", "Domingo" };
        ui->tableHora->setHorizontalHeaderLabels(colLabels);
        QStringList rowLabels;

        int hc=0;
        horaarr=new Hora[query.size()]();
        while (query.next()) {
            rowLabels.append(query.value(1).toString());
            horaarr[hc].establecer_id(query.value(0).toInt());
            horaarr[hc].establecer_descripcion(query.value(1).toString());
            hc++;
        }
        ui->tableHora->setVerticalHeaderLabels(rowLabels);
        ui->tableHora->setEditTriggers(QAbstractItemView::NoEditTriggers);

        sala->mostrarDia("Lunes",0, horaarr, query.size(), ui->tableHora);
        sala->mostrarDia("Martes",1 , horaarr, query.size(), ui->tableHora);
        sala->mostrarDia("Miercoles",2 , horaarr, query.size(), ui->tableHora);
        sala->mostrarDia("Jueves", 3, horaarr, query.size(), ui->tableHora);
        sala->mostrarDia("Viernes", 4, horaarr, query.size(), ui->tableHora);
        sala->mostrarDia("Sabado", 5, horaarr, query.size(), ui->tableHora);
        sala->mostrarDia("Domingo", 6, horaarr, query.size(), ui->tableHora);

    }
}

DialogAdminSala::~DialogAdminSala()
{
    delete ui;
}

void DialogAdminSala::on_tableHora_doubleClicked(const QModelIndex &index)
{
    int diaN=index.column();
    QString dia;
    switch (diaN) {
    case 0:
        dia="lunes";
        break;
    case 1:
        dia="martes";
        break;
    case 2:
        dia="miercoles";
        break;
    case 3:
        dia="jueves";
        break;
    case 4:
        dia="viernes";
        break;
    case 5:
        dia="sabado";
        break;
    case 6:
        dia="domingo";
        break;
    default:
        break;
    }

    int hora=index.row();
    hora=horaarr[hora].obtener_id();
    DialogSelectMovie *smovie=new DialogSelectMovie(nullptr, sala, dia, hora);
    smovie->setModal(true);
    smovie->exec();

    QSqlQuery rev("SELECT * FROM "+dia+" WHERE sala_id="+QString::number(sala->obtener_id())+" AND hora_id="+QString::number(hora), db);
    if(rev.size()==0){
        qDebug()<<"No hay regitro\n";
        ui->tableHora->item(index.row(), diaN)->setText("");
    }else{
        rev.next();
        QTableWidgetItem *iTempa;
        iTempa=new QTableWidgetItem();
        QSqlQuery queryPelirev("SELECT * FROM pelicula WHERE id_pelicula="+rev.value(2).toString(), db);
        queryPelirev.next();
        iTempa->setText(queryPelirev.value(1).toString());
        ui->tableHora->setItem(index.row(), diaN, iTempa);
    }
}

void DialogAdminSala::on_pushButton_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("Esto tambien elminara los registros de las programaciones.\n¿Desea Continuar?");
    QPushButton *connectButton = msgBox.addButton(tr("Si"), QMessageBox::ActionRole);
    QPushButton *abortButton = msgBox.addButton(tr("No"), QMessageBox::ActionRole);
    msgBox.exec();

    if (msgBox.clickedButton() == abortButton) {
        return;
    } else if (msgBox.clickedButton() == connectButton) {}

    //eliminar hijos
    int px=this->x()+(this->width()-loa->width())/2;
    int py=this->y()+this->height()/2;
    loa->move(px, py);

    emit actualizarV(0);

    sala->eliminarSalaDia("lunes");
    emit actualizarV(10);

    sala->eliminarSalaDia("martes");
    emit actualizarV(20);

    sala->eliminarSalaDia("miercoles");
    emit actualizarV(30);

    sala->eliminarSalaDia("jueves");
    emit actualizarV(40);

    sala->eliminarSalaDia("viernes");
    emit actualizarV(50);

    sala->eliminarSalaDia("sabado");
    emit actualizarV(55);

    sala->eliminarSalaDia("domingo");
    emit actualizarV(60);

    //eliminar sala
    QSqlQuery query;
    query.prepare("DELETE FROM sala WHERE id_sala="+QString::number(sala->obtener_id()));
    emit actualizarV(69);
    if(query.exec()){
        loa->close();
        emit actualizarV(100);
        QMessageBox::information(nullptr, tr("Informacion"), tr("Sala\t\nEliminada\t"),QMessageBox::Ok);
    }else{
        emit actualizarV(70);
        QString error=query.lastError().text();
        QMessageBox::critical(nullptr, tr("Error"), tr(error.toStdString().c_str()),QMessageBox::Ok);
    }
    this->close();
}
