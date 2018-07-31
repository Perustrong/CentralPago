#include "ServicioMaquinas/c_LogFileMaquinas.h"

c_LogFileMaquinas::c_LogFileMaquinas()
{
    QString InicioLog = "Creado LogFile";
    InsertarLineaLog(InicioLog);
}

void c_LogFileMaquinas::InsertarLineaLog(QString Linea)
{
    QString ContenidoAntiguo;
    QString LineaAux;
    QFile LogFile("ServicioMaquinas/LogFileMaquinas.txt");
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

QString c_LogFileMaquinas::LeerLog()
{
    QString ContenidoActual;
    QFile LogFile("ServicioMaquinas/LogFileMaquinas.txt");



     if(LogFile.open(QIODevice::ReadOnly))
     {
         QTextStream LecturaLog(&LogFile);
         ContenidoActual.append(LecturaLog.readAll());

         LogFile.close();

     }

     return ContenidoActual;


}
