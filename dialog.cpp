#include "dialogadd.h"
#include "ui_dialog.h"
#include "QSqlDatabase"
#include "QSqlQuery"
#include "QCheckBox"
#include "QDebug"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->lineDuration->setValidator(new QIntValidator(0, 1000));
    ui->lineDuration->setMaxLength(4);
    ui->lineCost->setValidator(new QDoubleValidator(0, 200, 2));
    ui->lineCost->setMaxLength(6);

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("sql10.freesqldatabase.com");
    db.setDatabaseName("sql10352486");
    db.setUserName("sql10352486");
    db.setPassword("9BPgk6jrLt");
    if (!db.open()) qDebug()<<"Error en base de datos";
    else qDebug()<<"Conectado Generos";
    QSqlQuery query("SELECT * FROM Genero ", db);
    if(query.size()==0){
        qDebug()<<"Vacio";

        this->close();
    }else{
        cg=query.size();
        gearr=new QCheckBox*[cg];
        idg=new QString*[cg];
        int k=0;
        while(query.next()){
            QString gen=query.value(1).toString();
            QString id_gen=query.value(0).toString();
            gearr[k]=new QCheckBox(gen);
            idg[k]=new QString(id_gen);
            k++;
        }
        QVBoxLayout *lista=new QVBoxLayout();
        for(int i=0;i<cg;i++){
            lista->addWidget(gearr[i]);
        }
        ui->generos->setLayout(lista);
    }
    QSqlQuery query2("SELECT * FROM Idioma ", db);
    if(query2.size()==0){
        qDebug()<<"Vacio2";
        this->close();
    }else{
        ci=query2.size();
        idarr=new QCheckBox*[ci];
        idi=new QString*[ci];
        int k=0;
        while(query2.next()){
            QString idio=query2.value(1).toString();
            QString id_idi=query2.value(0).toString();
            idarr[k]=new QCheckBox(idio);
            idi[k]=new QString(id_idi);
            k++;
        }
        QVBoxLayout *listai=new QVBoxLayout();
        for(int i=0;i<ci;i++){
            listai->addWidget(idarr[i]);
        }
        ui->idiomas->setLayout(listai);
}
}

Dialog::~Dialog()
{
    delete ui;
}
