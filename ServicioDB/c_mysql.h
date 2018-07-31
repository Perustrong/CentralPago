#ifndef C_MYSQL_H
#define C_MYSQL_H

#include <iostream>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlError>
#include <QSqlQuery>
#include <QMessageBox>

using namespace std;

class c_MySQL
{
public:
    c_MySQL();


    bool ConectarServidor();
    bool NuevoCliente(QString nombre, QString apellidos, QString saldo, QString CardID);
    float SaldoCliente(QString NumeroTarjeta, QString ID);
    bool RecargaTarjeta(QString ID,float cantidad);
    QString IDNuevoCliente();
    bool NuevoSaldo(QString ID, float saldo);




private:

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");



};

#endif // C_MYSQL_H
