#ifndef IDIOMAWINDOW_H
#define IDIOMAWINDOW_H

#include <QMainWindow>

namespace Ui {
class IdiomaWindow;
}

class IdiomaWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit IdiomaWindow(QWidget *parent = nullptr);
    ~IdiomaWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::IdiomaWindow *ui;
};

#endif // IDIOMAWINDOW_H
