#ifndef BILLETESNV9_H
#define BILLETESNV9_H


#define STRING_SIZE 100

#include <windows.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <sstream>
#include <ctime>

#include <string>
#include "ServicioEfectivo/c_comandos_nv9.h"
#include "ServicioEfectivo/c_flags_nv9.h"
#include "ServicioEfectivo/c_paramhilos_nv9.h"


using namespace std;

class BilletesNV9
{
public:

     BilletesNV9();
    unsigned long reflect (unsigned long crc, int bitnum);
    void generate_crc_table();
    unsigned long crcbitbybit(unsigned char* p, unsigned long len);
    void CalculoCRC16(unsigned char Mensaje[], int SizeMensaje);
    void ConectarPuertoCom();

    bool SyncBilletes();
    void EscribirPuertoCom(unsigned char Mensaje1[], int SizeMensaje);

    HANDLE GetComPort();
    c_flags_NV9 EstadoFlags();



    unsigned char CmdSync[3] = {0x80,0x01,0x11};
    unsigned char CmdEnable[3]= {FlagsCom.SyncBill_com(),0x01,0x0A};
    unsigned char CmdReset[3]={FlagsCom.SyncBill_com(),0x01,0x01};
    unsigned char CmdSetInhibits[5]={FlagsCom.SyncBill_com(),0x03,0x02,0xFF,0xFF};
    unsigned char CmdSetUpRequest[3]={FlagsCom.SyncBill_com(),0x01,0x05};
    unsigned char CmdDisplayOn[3]={FlagsCom.SyncBill_com(),0x01,0x03};
    unsigned char CmdDisplayOff[3]={FlagsCom.SyncBill_com(),0x01,0x04};
    unsigned char CmdPoll[3]={FlagsCom.SyncBill_com(),0x01,0x07};
    unsigned char CmdProtocolVersion[4]={FlagsCom.SyncBill_com(),0x02,0x06,0x06};

private:


    HANDLE hComPort;
   // HANDLE* AuxhCom1Port;
    //unsigned char* BufferLectura = new unsigned char[50];
    //unsigned char LecturaInterna[25];//Me he quedado creando un buffer para almacenar lo que ha leido.
    //float fLecturaInterna = 0; //Esta variable es para que LeerPuertoCom pueda devolver un valor interpretado por internamente para acceder al buffer de lectura interna y ver que ha ocurrido.
    DWORD dwBufferSize;
    TCHAR szBuffer[STRING_SIZE];
    TCHAR *pcCommPort = TEXT("COM7:");
    bool fSuccess;
    bool Sync = false;
    DCB dcbCom;
    unsigned char CRC16[2];




    c_flags_NV9 FlagsCom;
    c_ParamHilos_NV9 ParamHilo1;







};

#endif // BILLETESNV9_H
