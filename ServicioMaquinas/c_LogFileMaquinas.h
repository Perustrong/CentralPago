#ifndef C_LOGFILEMAQUINAS_H
#define C_LOGFILEMAQUINAS_H

#include <QFile>
#include <QTextStream>
#include <QDateTime>

class c_LogFileMaquinas
{
public:
    c_LogFileMaquinas();

    void InsertarLineaLog(QString Linea);
    QString LeerLog();

private:


};

#endif // C_LOGFILE_H
