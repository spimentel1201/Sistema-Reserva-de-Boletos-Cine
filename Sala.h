#ifndef SALA_H_INCLUDED
#define SALA_H_INCLUDED
#include "hora.h"
#include <string>
#include <QTableWidget>
#include <Pelicula.h>

using namespace std;
class Sala
{
private:
    int idSala;
    QString tipo_de_sala;
    int numero_de_sillas;

public:
    void espablecer_id(int);
    void establecer_tipo_de_sala(QString);
    void establecer_numero_de_sillas(int);
    void mostrarDia(QString dia,int column, Hora* arr, int size, QTableWidget* tabla);
    void eliminarSalaDia(QString dia);
    void asignarPelicula(Pelicula* peliinto, QString dia, int hora_id);
    void limpiarPelicula(QString dia, int hora_id);

    QString obtener_tipo_de_sala();
	int obtener_numero_de_sillas();
    int obtener_id();

};
#endif // SALA_H_INCLUDED
