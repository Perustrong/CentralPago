#ifndef C_LOGFILEIMPRESION_H
#define C_LOGFILEIMPRESION_H

#include <QFile>
#include <QTextStream>
#include <QDateTime>

class c_LogFileImpresion
{
public:
    c_LogFileImpresion();

    void InsertarLineaLog(QString Linea);
    QString LeerLog();

private:


};

#endif // C_LOGFILE_H
