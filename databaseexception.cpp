#include "databaseexception.h"
#include <QMessageBox>


DatabaseException::DatabaseException(QString e)
{
    exceptionV="NONE";
    exceptionV=e;
}

void DatabaseException::view()
{
    QMessageBox::critical(nullptr, "Alerta", exceptionV,QMessageBox::Ok);
}



