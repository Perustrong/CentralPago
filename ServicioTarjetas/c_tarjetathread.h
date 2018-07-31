#ifndef C_TARJETATHREAD_H
#define C_TARJETATHREAD_H

#include <QtCore>
#include <QDebug>
#include <ServicioTarjetas/c_functionsk720.h>

class c_TarjetaThread : public QThread
{
    Q_OBJECT
public:
    explicit c_TarjetaThread(QObject *parent =0);

    void run();
    int Function = 0; //Determina la función que va a realizar el hilo, concretamente el valor a devolver por la señal. De esta forma se controla la señal que llega.

private:

    //ojo hay que ver como implementar el hilo para la impresora.



signals:

    void LecturaTarjeta(float saldo);

};

#endif // C_TARJETATHREAD_H




