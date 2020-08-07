#include "dialogchairavailable.h"
#include "ui_dialogchairavailable.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include <dialogpago.h>
#include <validatorexception.h>
#include <databaseexception.h>
#include <QSqlError>


DialogChairAvailable::DialogChairAvailable(QWidget *parent, PeliculaProgramada* peliproginto, QSqlDatabase* dbinto, Cliente* userinto) :
    QDialog(parent),
    ui(new Ui::DialogChairAvailable)
{
    ui->setupUi(this);

    //Guardamos datos
    db=dbinto;
    user=userinto;
    peliprog=peliproginto;
    chairsReg=0;
    totalpago=0;


    //mostramos datos
    precio=peliprog->peli->obtener_precio();
    if(peliprog->sala->obtener_tipo_de_sala().compare("A")==0)  {
        ui->lbltiposala->setText("    Precio Clase A: S/ 5");
        precio+=5;
    }

    ui->linechair->setText(QString::number(chairsReg));
    ui->lblsalahora->setText("Sala "+QString::number(peliprog->sala->obtener_id())+": "+peliprog->hora->obtener_descripcion());
    ui->lblunit->setText("S/ "+QString::number(peliprog->peli->obtener_precio()));

    ui->movie->setText(peliprog->peli->obtener_titulo());
    ui->linetotal->setText("0");
    ui->linechair->setReadOnly(true);
    ui->linetotal->setReadOnly(true);


    QSqlQuery query("Select * from "+peliprog->dia+" where id="+QString::number(peliprog->id), *db);
    if(query.size()>0){
        query.next();

        //grid de las sillas
        QGridLayout *ele=new QGridLayout(this);
        int i=0;
        int cm=0;
        ct=peliprog->sala->obtener_numero_de_sillas();

        //obtenemos el registro de sillas
        chairs=new QString(query.value(4).toString());

        //array de sillas
        chairarr=new ChairLabel*[ct]();

        //llenamos el grid
        for(int j=0;j<10&&cm<ct;j++){
            chairarr[cm]=new ChairLabel;

            //si la silla esta ocupada cambiamos la imagen
            if(chairs->at(cm).toUpper()=='O'){
                chairarr[cm]->enable=false;
                chairarr[cm]->change();
            }

            //Conectamos la señal de click sobre una silla para cambiar su estado
            connect(chairarr[cm], &ChairLabel::mouse_Pressed, [&](int result){

                //Actualizamos los label
                chairsReg=chairsReg+result;
                ui->linechair->setText(QString::number(chairsReg));
                totalpago=chairsReg*precio;
                ui->linetotal->setText("S/ "+QString::number(totalpago));
            });

            //añadimos la silla
            ele->addWidget(chairarr[cm], i, j);
            cm++;
            if(j==9) {
                i++;
                j=-1;
            }
        }

        //guardamos el grid de sillas en la vista
        ui->frameChairs->setLayout(ele);



    }else{
        QMessageBox::warning(this, "Error", "Programacion no encontrado", QMessageBox::Ok);
    }


}

DialogChairAvailable::~DialogChairAvailable()
{
    delete ui;
}

void DialogChairAvailable::on_pushCancelar_clicked()
{
    this->close();
}

void DialogChairAvailable::on_pushAceptar_clicked()
{

    //Verificamos si se selecciono alguna silla
    bool existe=false;
    QString sillas="";
    QString sillasreg="";
    int sillasOcu=0;
    for (int i=0;i<ct;++i) {
        if(chairarr[i]->enable==false)   {
            sillasreg=sillasreg+"O";
            sillasOcu++;
            continue;
        }
        if(chairarr[i]->cheked==true)   {
            sillas=sillas+QString::number(i)+"  ";
            existe=true;
            sillasreg=sillasreg+"O";
            sillasOcu++;
        }else   sillasreg=sillasreg+"L";
    }

    bool exitoreserva=false;
    bool exitotarjeta=false;

    try {
        if(!existe) throw ValidatorException("Seleccione alguna silla");
        //Si no tiene tarjeta asociada se pide que ingrese una
        if(user->obtener_tarjeta_id().toInt()==0){
            dialogPago* a=new dialogPago(user, &exitotarjeta);
            a->exec();
        }else   exitotarjeta=true;
        //una vez verificada la tarjeta se añade la reserva
        if(exitotarjeta)    exitoreserva=user->agregar_reserva(peliprog->sala,peliprog->hora, peliprog->peli, peliprog->dia, sillas, totalpago);

    } catch (ValidatorException& v){
        v.view();
    }

    //Actualizamos las sillas si la reserva se añadio correctamente
    if(exitoreserva){
        try {
            QSqlQuery sillasUpdate;
            sillasUpdate.prepare("Update "+peliprog->dia+" set sillasreg='"+sillasreg
                                 +"', sillasOcu="+QString::number(sillasOcu)+" where id="
                                 +QString::number(peliprog->id));
            if(!sillasUpdate.exec()) throw DatabaseException(sillasUpdate.lastError().text());
            else this->close();

        } catch (DatabaseException& d) {
            d.view();
        }

    }

}
