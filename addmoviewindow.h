#ifndef ADDMOVIEWINDOW_H
#define ADDMOVIEWINDOW_H

#include <QMainWindow>
#include <QCheckBox>

namespace Ui {
class AddMovieWindow;
}

class AddMovieWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AddMovieWindow(QWidget *parent = nullptr);
    ~AddMovieWindow();
    QCheckBox **gearr;
    QString **idg;
    QCheckBox **idarr;
    QString **idi;
    int ci, cg;

private slots:
    void on_aceptar_clicked();

private:
    Ui::AddMovieWindow *ui;
};

#endif // ADDMOVIEWINDOW_H
