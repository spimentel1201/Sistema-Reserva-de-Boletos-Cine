#include "validatorexception.h"
#include <QMessageBox>


ValidatorException::ValidatorException(QString e)
{
    exceptionV="NONE";
    exceptionV=e;
}

void ValidatorException::view()
{
    QMessageBox::warning(nullptr, "Alerta", exceptionV,QMessageBox::Ok);
}


