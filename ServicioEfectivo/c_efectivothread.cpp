#include "ServicioEfectivo/c_efectivothread.h"
#include "01_home.h"


c_EfectivoThread::c_EfectivoThread(QObject *parent)
{

    //connect(MainWindow,SIGNAL(DevolucionMonedas(float)), this, SLOT(onDevolucionMonedas(float)));

}

void c_EfectivoThread::Stop()
{
    SistemaMonedas.Stop();
}

void c_EfectivoThread::Enable()
{
    SistemaMonedas.Enable();
}


void c_EfectivoThread::run()
{
        float Pagado;

  /*  for (int i =0; i<1000; i++)
    {
        QMutex Mutex;
        Mutex.lock();
        if(this->Stop) break;
        Mutex.unlock();

        emit NumberChanged(i);
    }*/

    cout << "entrado en el hilo";
    while (true)
    {
        Pagado = SistemaMonedas.PagoMoneda();

        emit LecturaMoneda(Pagado);
        Sleep(10);
    }


}
