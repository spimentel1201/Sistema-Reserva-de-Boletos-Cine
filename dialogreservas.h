#ifndef DIALOGRESERVAS_H
#define DIALOGRESERVAS_H

#include <QDialog>
#include <Cliente.h>
#include <QSqlDatabase>
#include <chairlabel.h>
#include <QSqlQueryModel>
#include <peliculaprogramada.h>
#include <string>

namespace Ui {
class DialogReservas;
}

class DialogReservas : public QDialog
{
    Q_OBJECT

public:
    explicit DialogReservas(QWidget *parent = nullptr, QSqlDatabase* dbinto=nullptr,Cliente* userinto=nullptr);
    ~DialogReservas();

    QSqlQueryModel *lunesModel;
    QSqlQueryModel *martesModel;
    QSqlQueryModel *miercolesModel;
    QSqlQueryModel *juevesModel;
    QSqlQueryModel *viernesModel;
    QSqlQueryModel *sabadoModel;
    QSqlQueryModel *domingoModel;

    void queryReserva(QSqlQueryModel*, QTableView*, int);

private slots:

private:

    Ui::DialogReservas *ui;
};

#endif // DIALOGRESERVAS_H
