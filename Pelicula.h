#ifndef PELICULA_H_INCLUDED
#define PELICULA_H_INCLUDED
#include <QString>

class Pelicula
{
private:
    int id_pelicula;
    QString titulo;
    int duracion;
    QString director;
    QString sinopsis;
    QChar estado;
    double precio;
public:
    void establecer_id(int);
    void establecer_titulo(QString);
	void establecer_duracion(int);
    void establecer_director(QString);
    void establecer_sinopsis(QString);
    void establecer_estado(QChar);
    void establecer_precio(double);
    int obtener_id();
    QString obtener_titulo();
	int obtener_duracion();
    QString obtener_director();
    QString obtener_sinopsis();
    QChar obtener_estado();
    double obtener_precio();
};
#endif // PELICULA_H_INCLUDED
