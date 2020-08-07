#ifndef DIALOGLOADING_H
#define DIALOGLOADING_H

#include <QDialog>

namespace Ui {
class DialogLoading;
}

class DialogLoading : public QDialog
{
    Q_OBJECT

public:
    explicit DialogLoading(QString title="", QWidget *parent = nullptr);
    ~DialogLoading();

private:
    Ui::DialogLoading *ui;
public slots:
    void actualizar(int);
};

#endif // DIALOGLOADING_H
