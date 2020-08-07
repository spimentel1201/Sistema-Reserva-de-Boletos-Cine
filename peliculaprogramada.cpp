#include "peliculaprogramada.h"

PeliculaProgramada::PeliculaProgramada(Pelicula* peliinto, Sala* salainto, Hora* horainto,
                                       QString diainto, int idinto)
{
    peli=peliinto;
    sala=salainto;
    hora=horainto;
    dia=diainto;
    id=idinto;
}
