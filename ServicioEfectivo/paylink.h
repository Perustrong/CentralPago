#ifndef PAYLINK_H
#define PAYLINK_H

#include <iostream>
#include "ServicioEfectivo/Aesimhei.h"
#include <ServicioEfectivo/c_LogFileEfectivo.h>
#include "windows.h"


using namespace std;


class PayLink
{
public:
    PayLink();
    float PagoMoneda();
    void DevolucionMonedas(float fnumber);
    void Stop();
    void Enable();
  //  void SetValorPago(float Valor);
   void SetActivoPago(bool Activo);
  //  float GetValorPago();
    bool GetActivoPago();


private:

    long UltimaCantidad ;
    long NuevaCantidad ;
    int OpenStatus;
   // float ValorPago = 2.30;
   // int intSpinP;
    bool ActivoPago = true;

};

#endif // PAYLINK_H
