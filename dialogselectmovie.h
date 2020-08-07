#ifndef DIALOGSELECTMOVIE_H
#define DIALOGSELECTMOVIE_H

#include <QDialog>
#include <QSqlDatabase>
#include <Pelicula.h>
#include <Sala.h>

namespace Ui {
class DialogSelectMovie;
}

class DialogSelectMovie : public QDialog
{
    Q_OBJECT

public:
    Pelicula *peliarr;
    int id_sala;
    QString nom_dia;
    int id_hora;
    QSqlDatabase db;
    Sala* sala;
    explicit DialogSelectMovie(QWidget *parent = nullptr, Sala* salainto=nullptr, QString dia=nullptr, int hora=0);
    ~DialogSelectMovie();

private slots:
    void on_listMovie_doubleClicked(const QModelIndex &index);

private:
    Ui::DialogSelectMovie *ui;
};

#endif // DIALOGSELECTMOVIE_H
