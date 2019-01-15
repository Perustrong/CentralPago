#ifndef C_EFECTIVOTHREAD_H
#define C_EFECTIVOTHREAD_H

#include <QtCore>
#include <QDebug>
#include "ServicioEfectivo/paylink.h"

class c_EfectivoThread : public QThread
{
    Q_OBJECT
public:
    explicit c_EfectivoThread(QObject *parent = 0);
    void Stop();
    void Enable();
    void run();
  //  void DevolucionMonedas(float number);
    PayLink SistemaMonedas;

signals:

    void LecturaMoneda(float number);

public slots:

    //void onDevolucionMonedas(float number);

private:


};

#endif // C_EFECTIVOTHREAD_H
