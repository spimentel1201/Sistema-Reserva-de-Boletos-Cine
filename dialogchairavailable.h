#ifndef DIALOGCHAIRAVAILABLE_H
#define DIALOGCHAIRAVAILABLE_H

#include <QDialog>
#include <Cliente.h>
#include <QSqlDatabase>
#include <chairlabel.h>
#include <peliculaprogramada.h>

namespace Ui {
class DialogChairAvailable;
}

class DialogChairAvailable : public QDialog
{
    Q_OBJECT

public:
    explicit DialogChairAvailable(QWidget *parent = nullptr, PeliculaProgramada* peliproginto=nullptr, QSqlDatabase* dbinto=nullptr,Cliente* userinto=nullptr);
    ~DialogChairAvailable();

private slots:
    void on_pushCancelar_clicked();

    void on_pushAceptar_clicked();

private:
    ChairLabel **chairarr;
    int ct;
    PeliculaProgramada* peliprog;
    Cliente* user;
    QSqlDatabase* db;
    int chairsReg;
    double precio;
    double totalpago;

    QString* chairs;


    Ui::DialogChairAvailable *ui;
};

#endif // DIALOGCHAIRAVAILABLE_H
