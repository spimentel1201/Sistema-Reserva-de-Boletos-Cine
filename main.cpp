#include "mainwindow.h"
#include "login.h"
#include <iostream>
#include <fstream>
#include "Administrador.h"
#include "Cine.h"
#include "Cliente.h"
#include "Horario.h"
#include "Pago.h"
#include "Pelicula.h"
#include "metodosPersona.cpp"
#include "Reserva.h"
#include "Sala.h"


#include <QApplication>
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login l;
    l.show();
    return a.exec();
}
