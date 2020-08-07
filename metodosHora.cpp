#include "hora.h"

Hora::Hora()
{

}

void Hora::establecer_id(int id){
    id_hora=id;
}

void Hora::establecer_descripcion(QString des){
    descripcion=des;
}

int Hora::obtener_id(){
    return id_hora;
}

QString Hora::obtener_descripcion(){
    return descripcion;
}
