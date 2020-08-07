#ifndef PAGO_H_INCLUDED
#define PAGO_H_INCLUDED
class Pago
{
private:
    bool efectivo;
    bool cheque;
    bool tarjeta_de_credito;
public:
	void establecer_tipo_de_pago();
	void obtener_datos();
};
#endif // PAGO_H_INCLUDED
