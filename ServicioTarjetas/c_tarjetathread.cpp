#include "ServicioTarjetas/c_tarjetathread.h"

c_TarjetaThread::c_TarjetaThread(QObject *parent)
{

}


void c_TarjetaThread::run()
{
    Sleep(1500);

    if(Function==0)  emit LecturaTarjeta(100); //Función lectura normal
    else if (Function==33)
    {
        Function=0;
        emit LecturaTarjeta(33);//33-> Función lectura de tarjeta para recarga desde inicio.

    }
    else if (Function ==39)
    {
        emit LecturaTarjeta(39);// 39-> Funci
    }
    else emit LecturaTarjeta(100);//Funcion lectura normal por defecto
}
