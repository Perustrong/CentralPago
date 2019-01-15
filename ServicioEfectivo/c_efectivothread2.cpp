#include "ServicioEfectivo/c_efectivothread2.h"

#include "01_home.h"


c_EfectivoThread2::c_EfectivoThread2(QObject *parent)
{

    BillReadThread = new c_LecturaBilleteThread(this);
    connect(BillReadThread,SIGNAL(ReadBill(float)), this, SLOT(onReadBill(float)));


}

void c_EfectivoThread2::Stop()
{
    Run=false;
    BillReadThread->terminate();
}



void c_EfectivoThread2::run()
{
    float Pagado;
    bool Sincro = false;
    Run = true;
    BillReadThread->start(HighPriority);

    Sleep(10);
    if (*SistemaBilletes.EstadoFlags().estado_com()==false)
    {

        SistemaBilletes.ConectarPuertoCom();
        Sleep(10);
        if (*SistemaBilletes.EstadoFlags().estado_com()==false)
        {
            cout<<"No se pudo conectar el puerto COM del billetero"<<endl;

            if(LogActivo==false)
            {
               LogEfectivo.InsertarLineaLog("No se ha podido conectar con el Billetero.");
               LogActivo = true;
            }

        }
        else
        {

            cout << "Hilo Lectura Arrancado"<<endl;
            Sleep(10);
            BillReadThread->hComPort=SistemaBilletes.GetComPort();

               LogEfectivo.InsertarLineaLog("Billetero Conectado.");
               LogActivo = false;

        }
    }
    else
    {
        //BillReadThread->run();
        cout << "Hilo Lectura Arrancado"<<endl;
        Sleep(10);
        BillReadThread->hComPort=SistemaBilletes.GetComPort();
        Sincro = SistemaBilletes.SyncBilletes();
        if (Sincro == false)
        {
            Sincro = SistemaBilletes.SyncBilletes();

            if (Sincro == false)
            {
                cout <<"Imposible sincronizar con billetero";
                LogEfectivo.InsertarLineaLog("Pérdida de Sincronización con el billetero. Reconectando");
                SistemaBilletes.EstadoFlags().flag_status_com(false);
                SistemaBilletes.ConectarPuertoCom();
                Sleep(10);
                if (*SistemaBilletes.EstadoFlags().estado_com()==false)
                {
                    cout<<"No se pudo conectar el puerto COM del billetero"<<endl;

                    if(LogActivo==false)
                    {
                       LogEfectivo.InsertarLineaLog("No se ha podido conectar con el Billetero.");
                       LogActivo = true;
                    }

                }
                else
                {

                    cout << "Hilo Lectura Arrancado"<<endl;
                    Sleep(10);
                    BillReadThread->hComPort=SistemaBilletes.GetComPort();

                       LogEfectivo.InsertarLineaLog("Billetero Conectado.");
                       LogActivo = false;

                }

                //Meter aquí el destructor//
            }
        }

    }

    Sincro = SistemaBilletes.SyncBilletes();
    if (Sincro == false)
    {
        Sincro = SistemaBilletes.SyncBilletes();
        
        if (Sincro == false)
        {
            cout <<"Imposible sincronizar con billetero";
            LogEfectivo.InsertarLineaLog("Fallo de resincronización.");
            //Meter aquí el destructor//
        }
    }
    Sleep(100);

    cout << "entrado en el hilo";
    while (Run == true)
    {

        float PagoRef = 0;
        Pagado = 0;

            SistemaBilletes.EscribirPuertoCom(SistemaBilletes.CmdPoll,sizeof(SistemaBilletes.CmdPoll));
            cout<<"poll"<<endl;





        Sleep(250);


    }


}

void c_EfectivoThread2::onReadBill(float number)
{
    float Pagado = number;
    QString LogBillete = "Billete Leído. Cantidad = ";
    LogBillete.append(QString::number(Pagado));
    LogEfectivo.InsertarLineaLog(LogBillete);
    cout <<"Entrado en readbill = "<<Pagado<<endl;

    emit LecturaBillete(Pagado);
}

