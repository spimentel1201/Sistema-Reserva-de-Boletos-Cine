#ifndef DIALOGPAGO_H
#define DIALOGPAGO_H

#include <QDialog>
#include <peliculaprogramada.h>
#include <Cliente.h>


namespace Ui {
class dialogPago;
}

class dialogPago : public QDialog
{
    Q_OBJECT

public:

    Cliente* user;
    bool* exitof;

    explicit dialogPago(Cliente* cliinto, bool* exito,QWidget *parent = nullptr);
    ~dialogPago();


private slots:

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::dialogPago *ui;
};

#endif // DIALOGPAGO_H
