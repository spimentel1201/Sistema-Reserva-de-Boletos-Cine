#ifndef RESERVA_H_INCLUDED
#define RESERVA_H_INCLUDED
#include "Sala.h"
#include "Pago.h"
#include <ctime>
class Reserva
{
private:
    Sala sala;
    time_t inicio;
    int cantidad_de_sillas;
    Pago medio_de_pago;
public:
	void establecer_sala();
	void establecer_inicio();
	void establecer_cantidad_de_sillas();
	void establecer_medio_de_pago();
	Sala obtener_sala();
	time_t obtener_inicio();
	int obtener_cantidad_de_sillas();
	Pago obtener_medio_de_pago();
	void mostrarDatos();
};


#endif // RESERVA_H_INCLUDED
