#ifndef DIALOGVIEWMOVIE_H
#define DIALOGVIEWMOVIE_H

#include <QDialog>
#include <Pelicula.h>
#include <QSqlDatabase>
#include <Cliente.h>

namespace Ui {
class DialogViewMovie;
}

class DialogViewMovie : public QDialog
{
    Q_OBJECT

public:

    Pelicula* peli;
    QSqlDatabase* db;
    Cliente* user;

    explicit DialogViewMovie(QWidget *parent = nullptr, Pelicula *p=nullptr, QSqlDatabase *dbinto=nullptr, Cliente* userinto=nullptr);
    ~DialogViewMovie();

private slots:
    void on_pushButton_clicked();

private:
    Ui::DialogViewMovie *ui;
};

#endif // DIALOGVIEWMOVIE_H
