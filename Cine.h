#ifndef CINE_H_INCLUDED
#define CINE_H_INCLUDED
#include "Sala.h"
#include "Pelicula.h"

class Cine
{
private:
    Sala *salas;
    Pelicula *cartelera;
public:
	void obtener_pelicula();
	void obtener_sala();
	void mostrarDatos();
};
#endif // CINE_H_INCLUDED
