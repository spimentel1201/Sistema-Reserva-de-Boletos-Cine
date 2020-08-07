#ifndef HORA_H
#define HORA_H
#include <QString>

class Hora
{
private:
    int id_hora;
    QString descripcion;
public:
    Hora();

    void establecer_id(int);
    void establecer_descripcion(QString);
    int obtener_id();
    QString obtener_descripcion();
};

#endif // HORA_H
