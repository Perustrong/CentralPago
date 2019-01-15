#ifndef C_LECTURAMAQUINAS_H
#define C_LECTURAMAQUINAS_H

#define STRING_SIZE 200

#include <QtCore>
#include <QDebug>
#include <windows.h>
#include <iostream>
#include <string>
#include <QString>
#include <ServicioMaquinas/c_LogFileMaquinas.h>
using namespace std;

class c_lecturamaquinas:public QThread
{
    Q_OBJECT
public:
    c_lecturamaquinas(QObject *parent = 0);
    float LeerPuertoCom();
    void InterpretaMensaje(string MensajeAux);
    void run();
    bool Stop;
    HANDLE hComPort=0;
    bool EstadoPuerta = false;

    string BufferAuxiliar;
signals:

    void LecturaMaquina(string);
   // void PuertaCerrada();



private:


    int BytesRecibidos = 0;
    int SizeMensajeAux = 0;

private slots:

    void onActualizacionHandle(HANDLE NewhComPort);


};

#endif // C_LECTURAMAQUINAS_H





