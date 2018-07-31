#include "ServicioEfectivo/paylink.h"




PayLink::PayLink()
{

}

void PayLink::DevolucionMonedas(float fnumber)
{
    int number = int(fnumber);

  //  if(OpenStatus != 0)
  //  {
    OpenStatus = OpenMHE();
    if(OpenStatus!=0)
    {
        c_LogFileEfectivo LogEfectivo;
        QString Log = "Fallo de conexión con PayLink. Error ";
        Log.append(QString::number(OpenStatus));
        Log.append("/r/n");
        LogEfectivo.InsertarLineaLog(Log);

    }
    else
    {

 //   }

         EnableInterface();

         PayOut(number);
    }


}

void PayLink::Stop()
{

    DisableInterface();
}

void PayLink::Enable()
{
    EnableInterface();
}

float PayLink::PagoMoneda()
{
    NuevaCantidad = CurrentValue();


    while (GetActivoPago())
    {
        Sleep(100);

      /*  if(OpenStatus!=0)
        {
            OpenStatus = OpenMHE();
            cout <<" Paylink No Conectado";
            NuevaCantidad = CurrentValue();
            return 0;

        }*/

        OpenStatus = OpenMHE();
        cout<<"OpenStatus = "<<OpenStatus<<endl;
        if(OpenStatus!=0)
        {
            c_LogFileEfectivo LogEfectivo;
            QString Log = "Fallo de conexión con PayLink. Error ";
            Log.append(QString::number(OpenStatus));
            Log.append("/r/n");
            LogEfectivo.InsertarLineaLog(Log);

        }
        else
        {
            Sleep(50);

            UltimaCantidad = CurrentValue();

            EnableInterface();
            cout <<"Pasado por Enable Interface";

          /*  ValorPago = GetValorPago();
            ValorPago = ValorPago*100;
            intSpinP = int(ValorPago);*/

            while(NuevaCantidad == UltimaCantidad && GetActivoPago() == true)
            {
               NuevaCantidad = CurrentValue();
               if(GetActivoPago() == false)
               {
                   return 0;
                   break;
               }
               else if(NuevaCantidad!=UltimaCantidad)
               {
                   c_LogFileEfectivo LogEfectivo;
                   float Moneda = (NuevaCantidad-UltimaCantidad);
                   Moneda = Moneda/100;
                   QString Log = "Lectura Moneda en PayLink.cpp de valor =";
                   Log.append(QString::number(Moneda));
                   LogEfectivo.InsertarLineaLog(Log);

                   cout<<"El usuario ha introducido solo Euros "<< (NuevaCantidad - UltimaCantidad)<<endl;
                   cout << "El nuevo valor es: "<<NuevaCantidad<<endl;
                   cout <<"El antiguo valor es_ " <<UltimaCantidad<<endl;

                 //  QMessageBox::information(this,tr("Introducción de monedas"),tr("El usuario ha introducido %1 €").arg((NewCurrencyValue - LastCurrencyValue)/100));
                 //  Pagado = Pagado + NewCurrencyValue - LastCurrencyValue;
                   return (NuevaCantidad - UltimaCantidad);
               }
               //cout<<"Nueva Cantidad =" <<NuevaCantidad<<endl;
               //cout <<"Ultimo Valor =" <<UltimaCantidad<<endl;
               Sleep(10);

            }

           // UltimaCantidad=CurrentValue();






         }




    }

}

void PayLink::SetActivoPago(bool Activo)
{

    ActivoPago=Activo;
}

bool PayLink::GetActivoPago()
{
    return ActivoPago;
}

/*void PayLink::SetValorPago(float Valor)
{

    ValorPago = Valor;
}

float PayLink::GetValorPago()
{
    return ValorPago;

}*/
