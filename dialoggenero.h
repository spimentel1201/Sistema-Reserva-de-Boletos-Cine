#ifndef DIALOGGENERO_H
#define DIALOGGENERO_H

#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class DialogGenero;
}

class DialogGenero : public QDialog
{
    Q_OBJECT

public:
    QSqlDatabase db;
    explicit DialogGenero(QSqlDatabase dbinto, QWidget *parent = nullptr);
    ~DialogGenero();

private slots:
    void on_pushButton_clicked();

    void on_listagenero_doubleClicked(const QModelIndex &index);

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::DialogGenero *ui;
};

#endif // DIALOGGENERO_H
