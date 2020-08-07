#include "dialogaddmovie.h"
#include "ui_dialogaddmovie.h"
#include "QSqlDatabase"
#include "QSqlQuery"
#include "QCheckBox"
#include "QDebug"
#include "QMessageBox"
#include "conexionmysql.h"
#include "QFileDialog"
#include "validatorexception.h"
#include <databaseexception.h>
#include <QSqlError>
#include <fileexception.h>

DialogAddMovie::DialogAddMovie(QSqlDatabase dbinto, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddMovie)
{
    ui->setupUi(this);
    ui->lineDuration->setValidator(new QIntValidator(0, 1000));
    ui->lineDuration->setMaxLength(4);
    ui->lineCost->setValidator(new QDoubleValidator(0, 200, 2));
    ui->lineCost->setMaxLength(6);

    db=dbinto;

    try {
        QSqlQuery query("SELECT * FROM Genero ", db);
        if(!(query.size()==0)){
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
        }else   throw DatabaseException(query.lastError().text());


        QSqlQuery query2("SELECT * FROM Idioma ", db);
        if(!(query2.size()==0)){
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
        }else   throw DatabaseException(query2.lastError().text());

    } catch (DatabaseException& d) {
        d.view();
        this->close();
    }

}

DialogAddMovie::~DialogAddMovie()
{
    delete ui;
}

void DialogAddMovie::on_aceptar_clicked()
{
    QString title=ui->lineTitle->text();
    QString duration=ui->lineDuration->text();
    QString director=ui->lineDirector->text();
    QString sinopsis=ui->plainSynopsis->toPlainText();
    QString precio=ui->lineCost->text();
    QString estado=ui->comboState->currentText();
    QString imagen=ui->lineImage->text();
    try {
        if(title.isEmpty()) throw ValidatorException("Titulo Vacio\t\t");

        else if(duration.isEmpty()) throw ValidatorException("Duracion vacia\t\t");

        else if(director.isEmpty()) throw ValidatorException("Director vacio\t\t");

        else if(sinopsis.isEmpty()) throw ValidatorException("Sinopsis vacio\t\t");

        else if(precio.isEmpty()) throw ValidatorException("Precio vacio\t\t");

        else if(imagen.isEmpty())   throw ValidatorException("Imagen vacio\t\t");

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

        if(!gencheck)   throw ValidatorException("Seleccione al menos un genero\t\t");

        else if(!idicheck)   throw ValidatorException("Seleccione al menos un idioma\t\t");


    } catch (ValidatorException& v) {
        v.view();
        return;
    }

    //Evaluando estado
    QString estadof;
    if(estado.compare("Activo")==0) estadof="A";
    else if(estado.compare("Inactivo")==0)  estadof="I";
    else    estadof="P";


    try {
        QSqlQuery query;
        query.prepare("INSERT INTO Pelicula (titulo, duracion, director, sinopsis, estado, precio) VALUES ('"+title+"', "+duration+", '"+director+"', '"+sinopsis+"','"+estadof+"', "+precio+")");
        if(!query.exec())   throw DatabaseException(query.lastError().text());
        else{
            query.prepare("SELECT * FROM Pelicula WHERE titulo='"+title+"' AND duracion="+duration);
            query.exec();
            query.next();
            QString idpeli=query.value(0).toString();

            //Insertando generos
            QSqlQuery query2;
            for(int i=0;i<cg;i++){
                if(gearr[i]->isChecked()){
                       query2.prepare("INSERT INTO Pelicula_Genero (pelicula_id, genero_id) VALUES("+idpeli+", "+idg[i]+")");
                       if(!query2.exec())    throw DatabaseException(query2.lastError().text());
                 }
            }
            QSqlQuery query3;
            //Insertando idiomas
            for(int i=0;i<ci;i++){
                if(idarr[i]->isChecked()){
                       query3.prepare("INSERT INTO Pelicula_Idioma (pelicula_id, idioma_id) VALUES("+idpeli+", "+idi[i]+")");
                       if(!query3.exec())   throw DatabaseException(query3.lastError().text());
                 }
            }


            //Guardamos la imagen
            QString destino("img/"+idpeli);
            QFile f(imagen);
            QFile fs(destino);
            if(!f.open(QIODevice::ReadOnly))    throw FileException("No se puede abrir imagen");
            if(!fs.open(QIODevice::WriteOnly))  throw FileException("No se pudo crear el archivo");
            while( !f.atEnd() )
            {
                QByteArray data = f.read(32);
                fs.write(data,data.size());
            }
            f.close();
            fs.close();


            QMessageBox::information(nullptr, tr("Informacion"), tr("Pelicula\t\nAgregada\t"),QMessageBox::Ok);

            this->close();
        }

    } catch (DatabaseException& d) {
        d.view();
    } catch (FileException& fe){
        fe.view();
    }

}

void DialogAddMovie::on_pushImage_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "/home",
                                                    tr("Images (*.png *.xpm *.jpg)"));
    ui->lineImage->setText(fileName);

}

void DialogAddMovie::on_cancelar_clicked()
{
    this->close();
}
