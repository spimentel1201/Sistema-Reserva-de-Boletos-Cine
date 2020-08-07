#ifndef CONEXIONMYSQL_H
#define CONEXIONMYSQL_H
#include <QSqlDatabase>

class ConexionMySQL
{
public:
    ConexionMySQL();

    /*
    QString dbt="QMYSQL";
    QString hostdb="us-cdbr-east-02.cleardb.com";
    QString dbname="heroku_ac2026cab24295b";
    QString usernamedb="b279207fe37014";
    QString passdb="ea905765";
    */

    //local
    QString dbt="QMYSQL";
    QString hostdb="localhost";
    QString dbname="heroku_ac2026cab24295b";
    QString usernamedb="root";
    QString passdb="";
};

#endif // CONEXIONMYSQL_H
