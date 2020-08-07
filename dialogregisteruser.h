#ifndef DIALOGREGISTERUSER_H
#define DIALOGREGISTERUSER_H

#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class DialogRegisterUser;
}

class DialogRegisterUser : public QDialog
{
    Q_OBJECT

public:
    explicit DialogRegisterUser(QWidget *parent = nullptr);
    ~DialogRegisterUser();

private slots:

    void on_pushButtonRegister_clicked();

    void on_pushButtonCancelar_clicked();

private:
    QSqlDatabase db;
    Ui::DialogRegisterUser *ui;
};

#endif // DIALOGREGISTERUSER_H
