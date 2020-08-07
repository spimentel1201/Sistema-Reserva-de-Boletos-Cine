#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QMainWindow>
#include <Administrador.h>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <Sala.h>

namespace Ui {
class AdminWindow;
}

class QSqlTableModel;
class AdminWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminWindow(QWidget *parent = nullptr, Administrador *ad=nullptr);
    ~AdminWindow();
    Administrador *admi;

    QVBoxLayout *listai;

    QPushButton **peliarr;

    Sala *salaarr;

    QSqlTableModel *userModel;
    QSqlQueryModel *lunesModel;
    QSqlQueryModel *martesModel;
    QSqlQueryModel *miercolesModel;
    QSqlQueryModel *juevesModel;
    QSqlQueryModel *viernesModel;
    QSqlQueryModel *sabadoModel;
    QSqlQueryModel *domingoModel;

    int cp;



    void abrirSala();

    void actualizarPeliculas();
    void actualizarUsuarios();
    void queryReserva(QSqlQueryModel*, QTableView*, int);

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_options_clicked();

    void on_pelitable_doubleClicked(const QModelIndex &index); 

    void on_listSala_clicked(const QModelIndex &index);

    void on_pushButton_4_clicked();

    void on_pushNewUser_clicked();

    void on_pushDelUser_clicked();

    void on_pushUpdate_clicked();

private:
    Ui::AdminWindow *ui;
    QSqlQueryModel *model;
    QSqlDatabase db;

};

#endif // ADMINWINDOW_H
