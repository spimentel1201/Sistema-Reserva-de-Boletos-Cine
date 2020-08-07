#include <string>
#include "Pelicula.h"
#include <iostream>

using namespace std;

void Pelicula::establecer_id(int id){
    id_pelicula=id;
}
void Pelicula::establecer_titulo(QString tit){
    titulo=tit;
}
void Pelicula::establecer_duracion(int dur){
    duracion=dur;
}
void Pelicula::establecer_director(QString dir){
    director=dir;
}
void Pelicula::establecer_sinopsis(QString sin){
    sinopsis=sin;
}
void Pelicula::establecer_estado(QChar est){
    estado=est;
}
void Pelicula::establecer_precio(double prec){
    precio=prec;
}

int Pelicula::obtener_id(){
    return id_pelicula;
}
QString Pelicula::obtener_titulo(){
    return titulo;
}
int Pelicula::obtener_duracion(){
    return duracion;
}
QString Pelicula::obtener_director(){
    return director;
}
QString Pelicula::obtener_sinopsis(){
    return sinopsis;
}
QChar Pelicula::obtener_estado(){
    return estado;
}
double Pelicula::obtener_precio(){
    return precio;
}
