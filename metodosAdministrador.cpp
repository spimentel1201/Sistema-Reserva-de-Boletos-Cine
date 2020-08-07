#include <string>
#include "Administrador.h"

using namespace std;


Administrador::Administrador(QString nom, QString user, QString pass, int ed, QString rol){
    registrar_nombre(nom);
    registrar_edad(ed);
    registrar_usuario(user);
    registrar_contrasenia(pass);
    registrar_tipo(rol);
}
