#ifndef C_LOGFILETARJETAS_H
#define C_LOGFILETARJETAS_H

#include <QFile>
#include <QTextStream>
#include <QDateTime>

class c_LogFileTarjetas
{
public:
    c_LogFileTarjetas();

    void InsertarLineaLog(QString Linea);
    QString LeerLog();

private:


};

#endif // C_LOGFILE_H
