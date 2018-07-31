#ifndef C_FUNCTIONSK720_H
#define C_FUNCTIONSK720_H
#include <ServicioDB/c_mysql.h>

#include <cstdlib>
#include <iostream>
#include "windows.h"
#include "ServicioTarjetas/c_flags_K720.h"
#include "ServicioTarjetas/c_ParamHilos_K720.h"
#include <cstring>
#include <ctime>
#include <QDebug>
#include <QString>
#include <sstream>

#include "ServicioTarjetas/K720_Dll.h"

using namespace std;

class c_FunctionsK720
{
public:
    c_FunctionsK720();
    void setHANDLE(HANDLE hComPort);
    HANDLE getHANDLE();
    void setMacAddr(char MacAddr);
    char getMacAddr();
    void setc_flags_K720(c_flags_K720* flagsCom);
    c_flags_K720* getc_flags_K720();
    QString BYTEStringtoQString(unsigned char *CardID, int size);
    QString CardIDTarjeta();
    void ExpulsarTarjeta();
    void DisableMouth();
    void EnableMouth();
    c_MySQL BaseDatos;
    QString UltimaID = NULL;
    QString UltimoNumCard = NULL;


    c_flags_K720 TestSensor();
    HANDLE ConnectCOM();
    float LeerTarjeta();
    QString CrearTarjeta(QString Nombre, QString Apellidos, QString ID);
private:
    HANDLE hComPortInside;
    char MacAddrInside = 03;
    c_flags_K720* flagsComInside = new c_flags_K720;
    char *PortDispenser = "COM1";


};

#endif // C_FUNCTIONSK720_H
