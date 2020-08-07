#include "dialogeditmovie.h"
#include "ui_dialogeditmovie.h"
#include "QSqlQuery"
#include "QCheckBox"
#include "QDebug"
#include "QMessageBox"
#include "conexionmysql.h"
#include "Pelicula.h"
#include "QFileDialog"
#include <QSqlError>
#include <databaseexception.h>
#include <validatorexception.h>
#include <fileexception.h>

DialogEditMovie::DialogEditMovie(QSqlDatabase dbinto, Pelicula* p,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogEditMovie)
{
    ui->setupUi(this);
    pe=p;

    db=dbinto;

    ui->lineTitle->setText(pe->obtener_titulo());
    ui->lineDuration->setText(QString::number(pe->obtener_duracion()));
    ui->lineDirector->setText(pe->obtener_director());
    ui->lineCost->setText( QString::number(pe->obtener_precio()));
    ui->plainSynopsis->setPlainText(pe->obtener_sinopsis());

    if(QFile::exists("img/"+QString::number(pe->obtener_id())))    ui->lineImage->setPlaceholderText("(Guardado)");
    else    ui->lineImage->setPlaceholderText("(Vacio)");
    ui->lineImage->setEnabled(false);

    QChar statec=pe->obtener_estado();
    if(statec=='A') ui->comboState->setCurrentIndex(0);
    else if(statec=='I')    ui->comboState->setCurrentIndex(1);
    else if(statec=='P')    ui->comboState->setCurrentIndex(2);
    else    ui->comboState->setCurrentIndex(0);


    ui->lineDuration->setValidator(new QIntValidator(0, 1000));
    ui->lineDuration->setMaxLength(4);
    ui->lineCost->setValidator(new QDoubleValidator(0, 200, 2));
    ui->lineCost->setMaxLength(6);

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
                QSqlQuery peli_gen("SELECT * FROM pelicula_genero WHERE pelicula_id="+QString::number(pe->obtener_id())+" AND genero_id="+id_gen, db);
                if(peli_gen.size()!=0){
                    gearr[k]->setCheckState(Qt::Checked);
                }
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
                QSqlQuery peli_idi("SELECT * FROM pelicula_idioma WHERE pelicula_id="+QString::number(pe->obtener_id())+" AND idioma_id="+id_idi, db);
                if(peli_idi.size()!=0){
                    idarr[k]->setCheckState(Qt::Checked);
                }
                k++;
            }
            QVBoxLayout *listai=new QVBoxLayout();
            for(int i=0;i<ci;i++){
                listai->addWidget(idarr[i]);
            }
            ui->idiomas->setLayout(listai);
        }else   DatabaseException(query2.lastError().text());

    } catch (DatabaseException& d) {
        d.view();
        this->close();
    }

}

DialogEditMovie::~DialogEditMovie()
{
    delete ui;
}

void DialogEditMovie::on_pushImage_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "/home",
                                                    tr("Images (*.png *.xpm *.jpg)"));
    ui->lineImage->setText(fileName);

}

void DialogEditMovie::on_aceptar_clicked()
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

        /*else if(imagen.isEmpty()){
            //qDebug()<<"Precio vacio";
            QMessageBox::warning(nullptr, tr("Alerta"), tr("Imagen vacia\t\t"),QMessageBox::Ok);
            return;
        }*/

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
        query.prepare("UPDATE Pelicula SET titulo='"+title+"', duracion="+duration
                      +", director='"+director+"', sinopsis='"+sinopsis+"', estado='"+estadof
                      +"', precio="+precio+" WHERE(id_pelicula="+QString::number(pe->obtener_id())+")");
        if(!query.exec()) throw DatabaseException(query.lastError().text());
        else{

            //limpiamos generos e idiomas registrados antes
            query.prepare("DELETE from pelicula_genero where pelicula_id="+QString::number(pe->obtener_id()));
            if(!query.exec())   throw DatabaseException(query.lastError().text());

            query.prepare("DELETE from pelicula_idioma where pelicula_id="+QString::number(pe->obtener_id()));
            if(!query.exec())   throw DatabaseException(query.lastError().text());



            query.prepare("SELECT * FROM Pelicula WHERE id_pelicula="+QString::number(pe->obtener_id()));
            if(!query.exec())   throw DatabaseException(query.lastError().text());
            query.next();
            QString idpeli=query.value(0).toString();

            //Insertando generos
            QSqlQuery query2;
            for(int i=0;i<cg;i++){
                if(gearr[i]->isChecked()){
                       query2.prepare("INSERT INTO Pelicula_Genero (pelicula_id, genero_id) VALUES("+idpeli+", "+idg[i]+")");
                       if(!query2.exec())   throw DatabaseException(query2.lastError().text());
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
            if(!imagen.isEmpty()){
                QFile::remove("img/"+idpeli);
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
            }



            QMessageBox::information(nullptr, tr("Informacion"), tr("Pelicula\t\nActualizada\t"),QMessageBox::Ok);

            this->close();

        }
    } catch (DatabaseException& d) {
        d.view();
        this->close();
    } catch (FileException& fe) {
        fe.view();
    }

}


void DialogEditMovie::on_cancelar_clicked()
{
    this->close();
}
