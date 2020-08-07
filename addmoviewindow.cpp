#include "addmoviewindow.h"
#include "ui_addmoviewindow.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QCheckBox>
AddMovieWindow::AddMovieWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AddMovieWindow)
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

AddMovieWindow::~AddMovieWindow()
{
    delete ui;
}

void AddMovieWindow::on_aceptar_clicked()
{
    QString title=ui->lineTitle->text();
    QString duration=ui->lineDuration->text();
    QString director=ui->lineDirector->text();
    QString sinopsis=ui->plainSynopsis->toPlainText();
    QString precio=ui->lineCost->text();
    QString estado=ui->comboState->currentText();
    try {
        if(title.isEmpty()){
            qDebug()<<"Titulo vacio";
            return;
        }
        else if(duration.isEmpty()){
            qDebug()<<"Duracion vacia";
            return;
        }
        else if(director.isEmpty()){
            qDebug()<<"Director vacio";
            return;
        }
        else if(sinopsis.isEmpty()){
            qDebug()<<"sinopsis vacio";
            return;
        }
        else if(precio.isEmpty()){
            qDebug()<<"Precio vacio";
            return;
        }
        bool gencheck=false;
        for(int i=0;i<cg;i++){
            if(gearr[i]->isChecked()){
                gencheck=true;
                break;
             }
        }
        bool idicheck=false;
        for(int i=0;i<ci;i++){
            if(idarr[i]->isChecked()){
                idicheck=true;
                break;
             }
        }
        if(!gencheck){
            qDebug()<<"Seleccione al menos un genero";
        }else if(!idicheck){
            qDebug()<<"Seleccione al menos un idioma";
        }


    } catch (...) {

    }
    //Evaluando estado
    QString estadof;
    if(estado.compare("Activo")==0){
        qDebug()<<"A";
        estadof="A";
    }else if(estado.compare("Inactivo")==0){
        qDebug()<<"I";
        estadof="I";
    }else{
        qDebug()<<"P";
        estadof="P";
    }


    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("sql10.freesqldatabase.com");
    db.setDatabaseName("sql10352486");
    db.setUserName("sql10352486");
    db.setPassword("9BPgk6jrLt");
    if (!db.open()) qDebug()<<"Error en base de datos";
    else qDebug()<<"Conectado";
    QSqlQuery query;
    query.prepare("INSERT INTO Pelicula (titulo, duracion, director, sinopsis, estado, precio) VALUES ('"+title+"', "+duration+", '"+director+"', '"+sinopsis+"','"+estadof+"', "+precio+")");
    if(!query.exec()){
        qDebug()<<"Error en BD";
        this->close();
        return;
    }else{
        query.prepare("SELECT * FROM Pelicula WHERE titulo='"+title+"' AND duracion="+duration);
        query.exec();
        query.next();
        QString idpeli=query.value(0).toString();
        qDebug()<<idpeli;
        //Insertando generos
        QSqlQuery query2;
        for(int i=0;i<cg;i++){
            if(gearr[i]->isChecked()){
                   query2.prepare("INSERT INTO Pelicula_Genero (pelicula_id, genero_id) VALUES("+idpeli+", "+idg[i]+")");
                   query2.exec();
             }
        }
        QSqlQuery query3;
        //Insertando idiomas
        for(int i=0;i<ci;i++){
            if(idarr[i]->isChecked()){
                   query3.prepare("INSERT INTO Pelicula_Idioma (pelicula_id, idioma_id) VALUES("+idpeli+", "+idi[i]+")");
                   query3.exec();
             }
        }


    }
}

