#ifndef DATABASEEXCEPTION_H
#define DATABASEEXCEPTION_H
#include <QString>

class DatabaseException: public std::exception
{
public:
    DatabaseException(QString e);
    void view();

private:
    QString exceptionV;
};

#endif // DATABASEEXCEPTION_H
