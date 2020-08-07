#ifndef FILEEXCEPTION_H
#define FILEEXCEPTION_H
#include <QString>

class FileException: public std::exception
{
public:
    FileException(QString e);
    void view();

private:
    QString exceptionV;
};


#endif // FILEEXCEPTION_H
