#ifndef HORARIODISP_H
#define HORARIODISP_H

#include <QWidget>

namespace Ui {
class horariodisp;
}

class horariodisp : public QWidget
{
    Q_OBJECT

public:
    explicit horariodisp(QWidget *parent = nullptr);
    ~horariodisp();

private slots:
    void on_aceptar_clicked();

private:
    Ui::horariodisp *ui;
};

#endif // HORARIODISP_H
