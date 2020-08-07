#ifndef GENERO_H
#define GENERO_H

#include <QMainWindow>

namespace Ui {
class Genero;
}

class Genero : public QMainWindow
{
    Q_OBJECT

public:
    explicit Genero(QWidget *parent = nullptr);
    ~Genero();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Genero *ui;
};

#endif // GENERO_H
