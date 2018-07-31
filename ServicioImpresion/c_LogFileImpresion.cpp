#include "ServicioImpresion/c_LogFileImpresion.h"

c_LogFileImpresion::c_LogFileImpresion()
{
    QString InicioLog = "Creado LogFile";
    InsertarLineaLog(InicioLog);
}

void c_LogFileImpresion::InsertarLineaLog(QString Linea)
{
    QString ContenidoAntiguo;
    QString LineaAux;
    QFile LogFile("ServicioImpresion/LogFileImpresion.txt");
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

QString c_LogFileImpresion::LeerLog()
{
    QString ContenidoActual;
    QFile LogFile("ServicioImpresion/LogFileImpresion.txt");



     if(LogFile.open(QIODevice::ReadOnly))
     {
         QTextStream LecturaLog(&LogFile);
         ContenidoActual.append(LecturaLog.readAll());

         LogFile.close();

     }

     return ContenidoActual;


}
