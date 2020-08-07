#ifndef MOVIELABEL_H
#define MOVIELABEL_H
#include <QLabel>
#include <QMouseEvent>
#include <Pelicula.h>

class MovieLabel : public QLabel
{
    Q_OBJECT
public:

    Pelicula* content;

    explicit MovieLabel(QWidget *parent=0);

    void mousePressEvent(QMouseEvent *ev) override;

    void setContent(Pelicula* p=nullptr);

signals:
    void mouse_Pressed(Pelicula* s);

};

#endif // MOVIELABEL_H
