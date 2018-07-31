#include "ServicioDB/c_mysql.h"

c_MySQL::c_MySQL()
{

}

bool c_MySQL::ConectarServidor()
{
    db.setHostName("localhost");
    db.setUserName("root");
    db.setPassword("genuix23");
    db.setDatabaseName("base_datos_cp");
    if(db.open()==false)
    {
        cout<<"Conexion a MySQL erronea"<<endl;
        return false;
    }
    else return true;

}

bool c_MySQL::NuevoCliente(QString nombre, QString apellidos, QString saldo, QString CardID)
{
    QSqlQuery query(db);
    if(db.isOpen())
    {
        qDebug() << "La conexion esta establecida";
        QString insertvalues = "INSERT INTO base_datos_cp.clientes (Nombre, Apellidos, Numero_de_tarjeta, Saldo) VALUES (:nombre, :apellidos, :CardID, :saldoString)";

        query.prepare(insertvalues);
        query.bindValue(":nombre",nombre);
        query.bindValue(":apellidos",apellidos);
        query.bindValue(":saldoString",saldo);
        query.bindValue(":CardID",CardID);
        query.exec();
        query.finish();

        if(query.lastError().isValid())
        {
            cout << "No se ha introducido bien el nuevo vliente"<<endl;
            return false;
        }
        else
        {
            return true;
        }
        qDebug() << query.lastError().text();


    }
    else
    {
        bool conectado;

        conectado = ConectarServidor();
        if(conectado==false)
        {
            cout<< "Conexión con MySQL imposible de realizar"<<endl;
        }
        else
        {
            qDebug() << "La conexion esta establecida";
            QString insertvalues = "INSERT INTO base_datos_cp.clientes (Nombre, Apellidos, Numero_de_tarjeta, Saldo) VALUES (:nombre, :apellidos, :CardID, :saldoString)";

            query.prepare(insertvalues);
            query.bindValue(":nombre",nombre);
            query.bindValue(":apellidos",apellidos);
            query.bindValue(":saldoString",saldo);
            query.bindValue(":CardID",CardID);
            query.exec();
            query.finish();

            if(query.lastError().isValid())
            {
                cout << "No se ha introducido bien el nuevo cliente"<<endl;
                return false;
            }
            else
            {
                return true;
            }
            qDebug() << query.lastError().text();

        }
    }

}

QString c_MySQL::IDNuevoCliente()
{
    QSqlQuery query(db);
    QString NuevaID;
    if(db.isOpen())
        {
            qDebug() << "La conexion esta establecida";
            query.exec("SELECT max(id+1) FROM base_datos_cp.clientes");
            query.first();
            NuevaID = query.value(0).toString();

            qDebug() << query.lastError().text();
            if(query.lastError().isValid())
            {
                cout << "No se ha introducido bien el nuevo vliente"<<endl;
                return NULL;
            }
            else
            {
                return NuevaID;
            }

        }
        else
        {
            bool conectado;
            conectado = ConectarServidor();
            if(conectado == false)
            {
                cout << "Imposible realizar la conexión con MySQL"<<endl;
            }
            else
            {
                qDebug() << "La conexion esta establecida";
                query.exec("SELECT max(id+1) FROM base_datos_cp.clientes");
                query.first();
                NuevaID = query.value(0).toString();

                qDebug() << query.lastError().text();
                if(query.lastError().isValid())
                {
                    cout << "No se ha obtenido correctamente la Nueva ID"<<endl;
                    return NULL;
                }
                else
                {
                    return NuevaID;
                }
            }
        }

}

float c_MySQL::SaldoCliente(QString NumeroTarjeta, QString ID)
{
    QSqlQuery query(db);
    float saldo = NULL;

    if(db.isOpen())
    {
        qDebug() << "La conexion esta establecida";

      //  QString insertvalues ="SELECT Saldo FROM base_datos_cp.clientes WHERE Numero_de_tarjeta = (NumeroTarjeta)VALUES(:NumeroTarjeta) AND ID =(ID)VALUES(:ID)";
        QString insertvalues ="SELECT Saldo FROM base_datos_cp.clientes WHERE Numero_de_tarjeta = :NumeroTarjeta AND ID =:ID";
        query.prepare(insertvalues);
        query.bindValue(":NumeroTarjeta",NumeroTarjeta);
        query.bindValue(":ID",ID);
        query.exec();

        query.first();

        qDebug() <<query.lastError().text();

        if(query.lastError().isValid())
        {
            cout << "No se ha obtenido correctamente el saldo del cliente"<< query.lastError().text().toStdString() << query.value(0).toFloat()<<endl;
            saldo = query.value(0).toFloat();
            return saldo;
        }
        else
        {
            saldo = query.value(0).toFloat();

            return saldo;
        }

    }
    else
    {
        bool conectado;
        conectado = ConectarServidor();
        if(conectado == false)
        {
            cout << "Imposible realizar la conexión con MySQL"<<endl;
            return 0;
        }
        else
        {
            qDebug() << "La conexion esta establecida";

          //  QString insertvalues ="SELECT Saldo FROM base_datos_cp.clientes WHERE Numero_de_tarjeta = (NumeroTarjeta)VALUES(:NumeroTarjeta) AND ID =(ID)VALUES(:ID)";
            QString insertvalues ="SELECT Saldo FROM base_datos_cp.clientes WHERE Numero_de_tarjeta = :NumeroTarjeta AND ID =:ID";
            query.prepare(insertvalues);
            query.bindValue(":NumeroTarjeta",NumeroTarjeta);
            query.bindValue(":ID",ID);
            query.exec();

            query.first();

            qDebug() <<query.lastError().text();

            if(query.lastError().isValid())
            {
                cout << "No se ha obtenido correctamente el saldo del cliente"<< query.lastError().text().toStdString() << query.value(0).toFloat()<<endl;
                saldo = query.value(0).toFloat();
                return saldo;
            }
            else
            {
                saldo = query.value(0).toFloat();

                return saldo;
            }
        }

    }
     query.finish();

}



bool c_MySQL::NuevoSaldo(QString ID, float saldo)
{
    QSqlQuery query(db);
    saldo = saldo/100;
    QString strSaldo = QString::number(saldo);

    if(db.isOpen())
    {
        qDebug() << "La conexion esta establecida";

        cout <<"ID dentro base de datos = "<<ID.toStdString()<<endl;
        cout <<"saldo dentro de base de datos =" << saldo <<"  strSaldo dentro de base de datos = "<<strSaldo.toStdString()<<endl;

      //  QString insertvalues ="SELECT Saldo FROM base_datos_cp.clientes WHERE Numero_de_tarjeta = (NumeroTarjeta)VALUES(:NumeroTarjeta) AND ID =(ID)VALUES(:ID)";
        QString insertvalues ="UPDATE base_datos_cp.clientes SET Saldo = :saldo WHERE ID = :ID";
        query.prepare(insertvalues);
        query.bindValue(":saldo",saldo);
        query.bindValue(":ID",ID);
        query.exec();

        query.first();

        qDebug() <<query.lastError().text();

        if(query.lastError().isValid())
        {
            cout << "No se ha obtenido correctamente el saldo del cliente"<< query.lastError().text().toStdString() << query.value(0).toFloat()<<endl;
            return false;
        }
        else
        {


            return true;
        }

    }
    else
    {
        bool conectado;
        conectado = ConectarServidor();
        if(conectado == false)
        {
            cout << "Imposible realizar la conexión con MySQL"<<endl;
            return 0;
        }
        else
        {
            qDebug() << "La conexion esta establecida";

          //  QString insertvalues ="SELECT Saldo FROM base_datos_cp.clientes WHERE Numero_de_tarjeta = (NumeroTarjeta)VALUES(:NumeroTarjeta) AND ID =(ID)VALUES(:ID)";
            QString insertvalues ="UPDATE base_datos_cp.clientes SET Saldo = :saldo WHERE ID = :ID";
            query.prepare(insertvalues);
            query.bindValue(":saldo",saldo);
            query.bindValue(":ID",ID);
            query.exec();

            query.first();

            qDebug() <<query.lastError().text();

            if(query.lastError().isValid())
            {
                cout << "No se ha obtenido correctamente el saldo del cliente"<< query.lastError().text().toStdString() << query.value(0).toFloat()<<endl;
                return false;
            }
            else
            {


                return true;
            }
        }

    }
     query.finish();





}

bool c_MySQL::RecargaTarjeta(QString ID, float cantidad)
{
    QSqlQuery query(db);
    cantidad = cantidad/100;
    QString strCantidad = QString::number(cantidad);

    if(db.isOpen())
    {
        qDebug() << "La conexion esta establecida";

        cout <<"ID dentro base de datos = "<<ID.toStdString()<<endl;
        cout <<"cantidad dentro de base de datos =" << cantidad <<"  strcantidad dentro de base de datos = "<<strCantidad.toStdString()<<endl;


        QString insertvalues ="UPDATE base_datos_cp.clientes SET Saldo = (Saldo+:cantidad) WHERE ID = :ID";
        query.prepare(insertvalues);
        query.bindValue(":cantidad",cantidad);
        query.bindValue(":ID",ID);
        query.exec();

        query.first();

        qDebug() <<query.lastError().text();

        if(query.lastError().isValid())
        {
            cout << "No se ha actualizado correctamente la recarga del cliente"<< query.lastError().text().toStdString() << query.value(0).toFloat()<<endl;
            return false;
        }
        else
        {


            return true;
        }

    }
    else
    {
        bool conectado;
        conectado = ConectarServidor();
        if(conectado == false)
        {
            cout << "Imposible realizar la conexión con MySQL"<<endl;
            return 0;
        }
        else
        {
            qDebug() << "La conexion esta establecida";

            QString insertvalues ="UPDATE base_datos_cp.clientes SET Saldo = (Saldo+:cantidad) WHERE ID = :ID";
            query.prepare(insertvalues);
            query.bindValue(":cantidad",cantidad);
            query.bindValue(":ID",ID);
            query.exec();

            query.first();

            qDebug() <<query.lastError().text();

            if(query.lastError().isValid())
            {
                cout << "No se ha obtenido correctamente el saldo del cliente"<< query.lastError().text().toStdString() << query.value(0).toFloat()<<endl;
                return false;
            }
            else
            {


                return true;
            }
        }

    }
     query.finish();





}
