#ifndef DIALOGADDSALA_H
#define DIALOGADDSALA_H

#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class DialogAddSala;
}

class DialogAddSala : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAddSala(QSqlDatabase dbinto, QWidget *parent = nullptr);
    ~DialogAddSala();
    QSqlDatabase db;


private slots:
    void on_pushButtonGuardar_clicked();

private:
    Ui::DialogAddSala *ui;
};

#endif // DIALOGADDSALA_H
