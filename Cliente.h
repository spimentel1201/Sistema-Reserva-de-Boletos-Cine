#ifndef CLIENTE_H_INCLUDED
#define CLIENTE_H_INCLUDED
#include "Reserva.h"
#include <QString>
#include "Persona.h"
#include <Pelicula.h>
#include <QSqlDatabase>

class Cliente:public Persona
{
private:
    Reserva *reservas;
public:
    QString tarjid;
    bool agregar_reserva(Sala* l, Hora* h, Pelicula *p, QString dia, QString sillas, double total);
    bool guardar_tarjeta(QString numero, QString tipo, QString prop, QString fven, QString cvv, QString ape);

    QString obtener_tarjeta_id();
    Cliente(int id, QString nom, QString ape, QString user, QString pass, int ed, QString rol, QString tarid);

    QSqlDatabase* db;
    int guardar(QSqlDatabase* dbinto);

};
#endif // CLIENTE_H_INCLUDED
