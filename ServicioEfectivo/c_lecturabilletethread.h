#ifndef C_LECTURABILLETETHREAD_H
#define C_LECTURABILLETETHREAD_H

#define STRING_SIZE 200

#include <QtCore>
#include <QDebug>
#include <windows.h>
#include <iostream>

using namespace std;
//#include "c_efectivothread2.h"

class c_LecturaBilleteThread:public QThread
{
    Q_OBJECT
public:
    c_LecturaBilleteThread(QObject *parent = 0);
    float LeerPuertoCom();
    float InterpretaMensaje(unsigned char MensajeAux[]);
    void run();
    HANDLE hComPort=0;

signals:

    void ReadBill(float number);

public slots:

    //void onDevolucionMonedas(float number);

private:

    unsigned char BufferAuxiliar[STRING_SIZE];
    int BytesRecibidos = 0;
    int SizeMensajeAux = 0;


};

#endif // C_LECTURABILLETETHREAD_H
