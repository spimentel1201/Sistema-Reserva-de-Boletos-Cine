#ifndef PELICULAPROGRAMADA_H
#define PELICULAPROGRAMADA_H
#include <Pelicula.h>
#include <Sala.h>
#include <hora.h>

class PeliculaProgramada
{
public:
    Pelicula* peli;
    Sala* sala;
    Hora* hora;
    QString dia;
    int id;
    PeliculaProgramada(Pelicula*, Sala*, Hora*, QString, int);
};

#endif // PELICULAPROGRAMADA_H
