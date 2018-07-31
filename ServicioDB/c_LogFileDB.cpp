#include "ServicioDB/c_LogFileDB.h"

c_LogFileDB::c_LogFileDB()
{
    QString InicioLog = "Creado LogFile";
    InsertarLineaLog(InicioLog);
}

void c_LogFileDB::InsertarLineaLog(QString Linea)
{
    QString ContenidoAntiguo;
    QString LineaAux;
    QFile LogFile("ServicioDB/LogFileDB.txt");
    LineaAux.append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm:ss"));
    LineaAux.append(" ");
    LineaAux.append(Linea);
    LineaAux.append("\r\n");

    if(LogFile.open(QIODevice::ReadOnly))
    {
        QTextStream LecturaLog(&LogFile);
        ContenidoAntiguo.append(LecturaLog.readAll());
        LogFile.close();

    }

    if(LogFile.open(QIODevice::WriteOnly))
    {
        QTextStream EscrituraLog(&LogFile);
        EscrituraLog<<ContenidoAntiguo;
        EscrituraLog<<LineaAux;
        LogFile.close();
    }

}

QString c_LogFileDB::LeerLog()
{
    QString ContenidoActual;
    QFile LogFile("ServicioDB/LogFileDB.txt");



     if(LogFile.open(QIODevice::ReadOnly))
     {
         QTextStream LecturaLog(&LogFile);
         ContenidoActual.append(LecturaLog.readAll());

         LogFile.close();

     }

     return ContenidoActual;


}
