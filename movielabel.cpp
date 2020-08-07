#include "movielabel.h"

MovieLabel::MovieLabel(QWidget *parent) :
    QLabel(parent)
{
    content=nullptr;
}

void MovieLabel::mousePressEvent(QMouseEvent *ev){
    emit mouse_Pressed(this->content);
}

void MovieLabel::setContent(Pelicula* p){
    content=p;
}
