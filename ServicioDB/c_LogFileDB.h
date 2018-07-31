#ifndef C_LOGFILEDB_H
#define C_LOGFILEDB_H

#include <QFile>
#include <QTextStream>
#include <QDateTime>

class c_LogFileDB
{
public:
    c_LogFileDB();

    void InsertarLineaLog(QString Linea);
    QString LeerLog();

private:


};

#endif // C_LOGFILE_H
