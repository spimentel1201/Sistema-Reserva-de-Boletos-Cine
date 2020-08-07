#ifndef DIALOGADDMOVIE_H
#define DIALOGADDMOVIE_H

#include <QDialog>
#include <QCheckBox>
#include <QSqlDatabase>

namespace Ui {
class DialogAddMovie;
}

class DialogAddMovie : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAddMovie(QSqlDatabase dbinto, QWidget *parent = nullptr);
    ~DialogAddMovie();
    QSqlDatabase db;
    QCheckBox **gearr;
    QString **idg;
    QCheckBox **idarr;
    QString **idi;
    int ci, cg;

private slots:
    void on_aceptar_clicked();

    void on_pushImage_clicked();

    void on_cancelar_clicked();

private:
    Ui::DialogAddMovie *ui;
};

#endif // DIALOGADDMOVIE_H
