QT       += core gui
QT       += core network sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    adminwindow.cpp \
    chairlabel.cpp \
    conexionmysql.cpp \
    databaseexception.cpp \
    dialogaddmovie.cpp \
    dialogaddsala.cpp \
    dialogadminsala.cpp \
    dialogchairavailable.cpp \
    dialogeditmovie.cpp \
    dialoggenero.cpp \
    dialogidioma.cpp \
    dialogloading.cpp \
    dialogpago.cpp \
    dialogregisteruser.cpp \
    dialogreservas.cpp \
    dialogschedulemovie.cpp \
    dialogselectmovie.cpp \
    dialogviewmovie.cpp \
    fileexception.cpp \
    horariodisp.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp\
    metodosAdministrador.cpp \
    metodosCliente.cpp \
    metodosHora.cpp \
    metodosPeli.cpp\
    metodosPersona.cpp \
    metodosSala.cpp \
    movielabel.cpp \
    peliculaprogramada.cpp \
    peliwindow.cpp \
    validatorexception.cpp

HEADERS += \
    adminwindow.h \
    chairlabel.h \
    conexionmysql.h \
    databaseexception.h \
    dialogaddmovie.h \
    dialogaddsala.h \
    dialogadminsala.h \
    dialogchairavailable.h \
    dialogeditmovie.h \
    dialoggenero.h \
    dialogidioma.h \
    dialogloading.h \
    dialogpago.h \
    dialogregisteruser.h \
    dialogreservas.h \
    dialogschedulemovie.h \
    dialogselectmovie.h \
    dialogviewmovie.h \
    fileexception.h \
    hora.h \
    horariodisp.h \
    login.h \
    mainwindow.h\
    Administrador.h\
    Cine.h\
    Cliente.h\
    Pago.h\
    Pelicula.h\
    Persona.h\
    Reserva.h\
    Sala.h \
    movielabel.h \
    peliculaprogramada.h \
    peliwindow.h \
    validatorexception.h


FORMS += \
    adminwindow.ui \
    dialogaddmovie.ui \
    dialogaddsala.ui \
    dialogadduser.ui \
    dialogadminsala.ui \
    dialogchairavailable.ui \
    dialogeditmovie.ui \
    dialoggenero.ui \
    dialogidioma.ui \
    dialogloading.ui \
    dialogpago.ui \
    dialogregisteruser.ui \
    dialogreservas.ui \
    dialogschedulemovie.ui \
    dialogselectmovie.ui \
    dialogviewmovie.ui \
    horariodisp.ui \
    login.ui \
    mainwindow.ui \
    peliwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
QT += sql

RESOURCES += \
    recursos.qrc

DISTFILES += \
    RegisterUser.qml \
    RegisterUserForm.ui.qml
