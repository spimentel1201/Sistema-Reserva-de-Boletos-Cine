#ifndef DIALOGEDITMOVIE_H
#define DIALOGEDITMOVIE_H

#include <QDialog>
#include <QCheckBox>
#include <Pelicula.h>
#include "QSqlDatabase"

namespace Ui {
class DialogEditMovie;
}

class DialogEditMovie : public QDialog
{
    Q_OBJECT

public:
    explicit DialogEditMovie(QSqlDatabase dbinto, Pelicula* p=nullptr, QWidget *parent = nullptr);
    ~DialogEditMovie();
    Pelicula* pe;
    QCheckBox **gearr;
    QString **idg;
    QCheckBox **idarr;
    QString **idi;
    int ci, cg;
    QSqlDatabase db;

private slots:
    void on_pushImage_clicked();

    void on_aceptar_clicked();

    void on_cancelar_clicked();

private:
    Ui::DialogEditMovie *ui;
};

#endif // DIALOGEDITMOVIE_H
