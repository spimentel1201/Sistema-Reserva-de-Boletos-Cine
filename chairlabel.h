#ifndef CHAIRLABEL_H
#define CHAIRLABEL_H
#include <QLabel>
#include <QMouseEvent>

class ChairLabel : public QLabel
{
    Q_OBJECT
public:
    bool enable;
    bool cheked;

    explicit ChairLabel(QWidget *parent=0);

    void mousePressEvent(QMouseEvent *ev) override;
    int change();

signals:
    void mouse_Pressed(int);

};

#endif // CHAIRLABEL_H
