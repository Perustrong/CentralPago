#include "c_LogFile.h"

c_LogFile::c_LogFile()
{
    QString InicioLog = "Creado LogFile";
    InsertarLineaLog(InicioLog);
}

void c_LogFile::InsertarLineaLog(QString Linea)
{
    QString ContenidoAntiguo;
    QString LineaAux;
    QFile LogFile("LogFile.txt");
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

QString c_LogFile::LeerLog()
{
    QString ContenidoActual;
    QFile LogFile("LogFile.txt");



     if(LogFile.open(QIODevice::ReadOnly))
     {
         QTextStream LecturaLog(&LogFile);
         ContenidoActual.append(LecturaLog.readAll());

         LogFile.close();

     }

     return ContenidoActual;


}
