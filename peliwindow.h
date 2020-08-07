#ifndef PELIWINDOW_H
#define PELIWINDOW_H

#include <QMainWindow>
#include "Cliente.h"
#include <QSqlDatabase>
#include <QPushButton>
#include <movielabel.h>

namespace Ui {
class PeliWindow;
}

class PeliWindow : public QMainWindow
{
    Q_OBJECT

public:
    int ct;
    QString *id;
    MovieLabel *moviearr;
    explicit PeliWindow(QWidget *parent = nullptr, Cliente *cl=nullptr);
    ~PeliWindow();

    Cliente *clie;
    QSqlDatabase db;

signals:
    void movieClick(QPushButton*);

private slots:
    void on_options_clicked();

    void on_userbutton_clicked();

private:
    Ui::PeliWindow *ui;
};

#endif // PELIWINDOW_H
