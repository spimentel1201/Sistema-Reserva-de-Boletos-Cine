#ifndef VALIDATOREXCEPTION_H
#define VALIDATOREXCEPTION_H
#include <QString>

class ValidatorException: public std::exception
{
public:
    ValidatorException(QString e);
    void view();

private:
    QString exceptionV;
};

#endif // VALIDATOREXCEPTION_H
