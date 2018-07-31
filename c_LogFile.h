#ifndef C_LOGFILE_H
#define C_LOGFILE_H

#include <QFile>
#include <QTextStream>
#include <QDateTime>

class c_LogFile
{
public:
    c_LogFile();

    void InsertarLineaLog(QString Linea);
    QString LeerLog();

private:


};

#endif // C_LOGFILE_H
