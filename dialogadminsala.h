#ifndef DIALOGADMINSALA_H
#define DIALOGADMINSALA_H

#include <QDialog>
#include <Sala.h>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <hora.h>
#include <Sala.h>
#include <dialogloading.h>

namespace Ui {
class DialogAdminSala;
}

class DialogAdminSala : public QDialog
{
    Q_OBJECT

public:
    DialogLoading *loa;
    explicit DialogAdminSala(QSqlDatabase *dbinto, QWidget *parent = nullptr, Sala *salainto=nullptr);
    ~DialogAdminSala();

    //void mostrarSala();

private slots:
    void on_tableHora_doubleClicked(const QModelIndex &index);

    void on_pushButton_clicked();
signals:
    void actualizarV(int n);
private:
    Ui::DialogAdminSala *ui;
    QSqlQueryModel *model;
    QSqlDatabase db;
    Hora *horaarr;
    Sala *sala;
};

#endif // DIALOGADMINSALA_H
