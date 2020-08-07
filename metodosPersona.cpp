#include <string>
#include "Persona.h"

using namespace std;


Persona::Persona(QString nom, QString user, QString pass, int ed, QString rol){
    nombre=nom;
    edad=ed;
    usuario=user;
    contrasenia=pass;
    tipo=rol;
}
Persona::Persona(){}

void Persona::registrar_nombre(QString nom){
    nombre=nom;
}

void Persona::registrar_apellido(QString ape)
{
    apellido=ape;
}
void Persona::registrar_edad(int eda){
    edad=eda;
}
void Persona::registrar_usuario(QString use){
    usuario=use;
}
void Persona::registrar_contrasenia(QString cont){
    contrasenia=cont;
}
void Persona::registrar_tipo(QString tip){
    tipo=tip;
}

void Persona::registrar_id(int id)
{
    id_user=id;
}
QString Persona::obtener_nombre(){
    return nombre;
}

QString Persona::obtener_apellido()
{
    return apellido;
}
int Persona::obtener_edad(){
    return edad;
}
QString Persona::obtener_usuario(){
    return usuario;
}
QString Persona::obtener_contrasenia(){
    return contrasenia;
}
QString Persona::obtener_tipo(){
    return tipo;
}

int Persona::obtener_id()
{
    return id_user;
}
