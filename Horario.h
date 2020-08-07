#ifndef HORARIO_H_INCLUDED
#define HORARIO_H_INCLUDED
#include <ctime>
#include "Pelicula.h"
class Horario
{
private:
    int id_hora;
    time_t fecha;
public:
	void agregar_pelicula();
	void establecer_fecha();
	Pelicula* obtener_peliculas();
	time_t obtenerFecha();
	void mostrarDatos();
};
#endif // HORARIO_H_INCLUDED
