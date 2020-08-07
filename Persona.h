#ifndef PERSONA_H_INCLUDED
#define PERSONA_H_INCLUDED
#include <string>
#include <QString>
using namespace std;
class Persona
{
private:
    QString nombre;
    QString apellido;
    int edad;
    QString usuario;
    QString contrasenia;
    QString tipo;
    int id_user;


public:
    void registrar_nombre(QString);
    void registrar_apellido(QString);
    void registrar_edad(int);
    void registrar_usuario(QString);
    void registrar_contrasenia(QString);
    void registrar_tipo(QString);
    void registrar_id(int);


    QString obtener_nombre();
    QString obtener_apellido();
	int obtener_edad();
    QString obtener_usuario();
    QString obtener_contrasenia();
    QString obtener_tipo();
    int obtener_id();
    Persona(QString, QString, QString, int, QString);
    Persona();
};
#endif // PERSONA_H_INCLUDED
