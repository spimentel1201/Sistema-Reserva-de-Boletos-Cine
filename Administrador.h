#ifndef ADMINISTRADOR_H_INCLUDED
#define ADMINISTRADOR_H_INCLUDED
#include "Persona.h"

class Administrador:public Persona
{
private:

public:
	void agregar_pelicula();
	void eliminar_pelicula();
	void agregar_sala();
	void eliminar_sala();
	void editar_sala();
    Administrador();
    Administrador(QString, QString, QString, int, QString);
};
#endif // ADMINISTRADOR_H_INCLUDED
