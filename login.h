#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QtSql/QSqlDatabase>
#include <QtSql>
#include "dialogloading.h"

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    DialogLoading *loa;
    explicit Login(QWidget *parent = nullptr);
    ~Login();

signals:
    void actualizarV(int);

private slots:

    void on_loginbutton_clicked();

    void on_pushButtonRegister_clicked();

private:
    QSqlDatabase db;
    Ui::Login *ui;
};

#endif // LOGIN_H
