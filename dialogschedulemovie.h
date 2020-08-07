#ifndef DIALOGSCHEDULEMOVIE_H
#define DIALOGSCHEDULEMOVIE_H

#include <QDialog>
#include <QSqlDatabase>
#include <Pelicula.h>
#include <Cliente.h>
#include <QListWidget>


namespace Ui {
class DialogScheduleMovie;
}

class DialogScheduleMovie : public QDialog
{
    Q_OBJECT

public:

    Cliente* user;
    QString* llenar(QString diaview,QListWidget* l);
    void reservar(int index, QString dia, QString diaview, QString* idday);
    explicit DialogScheduleMovie(QWidget *parent = nullptr, QSqlDatabase *dbinto=nullptr, Pelicula* p=nullptr, Cliente* userinto=nullptr);
    ~DialogScheduleMovie();

private slots:
    void on_listLunes_doubleClicked(const QModelIndex &index);

    void on_listMartes_doubleClicked(const QModelIndex &index);

    void on_listMiercoles_doubleClicked(const QModelIndex &index);

    void on_listJueves_doubleClicked(const QModelIndex &index);

    void on_listViernes_doubleClicked(const QModelIndex &index);

    void on_listSabado_doubleClicked(const QModelIndex &index);

    void on_listDomingo_doubleClicked(const QModelIndex &index);

private:
    QSqlDatabase *db;
    Pelicula* peli;
    QString *idlunes;
    QString *idmartes;
    QString *idmiercoles;
    QString *idjueves;
    QString *idviernes;
    QString *idsabado;
    QString *iddomingo;

    Ui::DialogScheduleMovie *ui;
};

#endif // DIALOGSCHEDULEMOVIE_H
