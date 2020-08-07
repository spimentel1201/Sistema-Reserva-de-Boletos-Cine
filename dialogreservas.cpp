#include "dialogreservas.h"
#include "ui_dialogreservas.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include <dialogreservas.h>
#include "QSqlTableModel"
#include <validatorexception.h>
#include <databaseexception.h>
#include <QSqlError>
#include <string>

DialogReservas::DialogReservas(QWidget *parent, QSqlDatabase* dbinto, Cliente* userinto) :
    QDialog(parent),
    ui(new Ui::DialogReservas)
{
    ui->setupUi(this);
    this->queryReserva(lunesModel, ui->tableView, userinto->obtener_id());
}

DialogReservas::~DialogReservas()
{
    delete ui;
}

void DialogReservas::queryReserva(QSqlQueryModel *qm, QTableView *tabla,int d)
{
    qm=new QSqlQueryModel;
    string consulta = "SELECT * FROM reserva where persona_id=" + std::to_string(d);
    qm->setQuery(consulta.c_str());
    tabla->setModel(qm);
}
