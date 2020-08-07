#include "fileexception.h"

#include <QMessageBox>


FileException::FileException(QString e)
{
    exceptionV="NONE";
    exceptionV=e;
}

void FileException::view()
{
    QMessageBox::critical(nullptr, "Alerta", exceptionV,QMessageBox::Ok);
}


