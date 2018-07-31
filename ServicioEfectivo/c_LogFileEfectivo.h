#ifndef C_LOGFILEEFECTIVO_H
#define C_LOGFILEEFECTIVO_H

#include <QFile>
#include <QTextStream>
#include <QDateTime>

class c_LogFileEfectivo
{
public:
    c_LogFileEfectivo();

    void InsertarLineaLog(QString Linea);
    QString LeerLog();

private:


};

#endif // C_LOGFILE_H
