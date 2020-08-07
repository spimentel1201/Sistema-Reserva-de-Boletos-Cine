#include "chairlabel.h"
#include <QDebug>

ChairLabel::ChairLabel(QWidget *parent):
    QLabel(parent)
{
    enable=true;
    cheked=false;
    QString qss = "font: 1pt;"
                 "background-color: #0db2f8;"
                 "image: url(icon/seatOff)";
    this->setStyleSheet(qss);
}

void ChairLabel::mousePressEvent(QMouseEvent *ev){
    emit mouse_Pressed(change());
}

int ChairLabel:: change(){
    int result=0;
    if (!enable)   {
        QString qss = "font: 1pt;"
                     "background-color: #c40229;"
                     "image: url(icon/seatDisabled)";
        this->setStyleSheet(qss);
        return result;
    }
    QString qss="";
    if(cheked){
         qss = "font: 1pt;"
                      "background-color: #0db2f8;"
                      "image: url(icon/seatOff)";
         cheked=false;
         result=-1;
    }else{
         qss = "font: 1pt;"
                      "background-color: #e0990b;"
                      "image: url(icon/seatOn)";
        cheked=true;
        result=1;
    }

    this->setStyleSheet(qss);
    return result;
}
