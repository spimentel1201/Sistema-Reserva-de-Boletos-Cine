#ifndef DIALOGIDIOMA_H
#define DIALOGIDIOMA_H

#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class DialogIdioma;
}

class DialogIdioma : public QDialog
{
    Q_OBJECT

public:
    explicit DialogIdioma(QSqlDatabase dbinto, QWidget *parent = nullptr);
    ~DialogIdioma();
    QSqlDatabase db;
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_listaIdioma_doubleClicked(const QModelIndex &index);

    void on_pushButton_3_clicked();

private:
    Ui::DialogIdioma *ui;
};

#endif // DIALOGIDIOMA_H
