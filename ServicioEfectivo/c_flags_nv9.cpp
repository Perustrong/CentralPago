#include "ServicioEfectivo/c_flags_nv9.h"

c_flags_NV9::c_flags_NV9()
{
    lectura_com = false;
    escritura_com=false;
    status_com =false;

}

//Lee el estado del flag de lectura del puerto com
bool* c_flags_NV9::leer_com()
{
    //cout << lectura_com;
    return &lectura_com;
}


//Devuelve el estado del flag de conexión del puerto com
bool* c_flags_NV9::estado_com()
{
    //cout << status_com;
    return &status_com;
}

//Devuelve el estado del flag de conexión del puerto com
bool* c_flags_NV9::escribir_com()
{
    //cout << escritura_com;
    return &escritura_com;
}
//Devuelve el estado de sincronismo del validador de billetes
unsigned char c_flags_NV9::SyncBill_com()
{
    return sincronismo_bill_com;
}


///////////////////////////////////////////////////
//Modificación de estados de los estados de los flags para ejecuciones externas
///////////////////////////////////////////////////

//Cambia el estado del flag de lectura del puerto com
void c_flags_NV9::flag_lectura_com(bool flag)
{
    lectura_com = flag;
    //cout << lectura_com;
}
//Cambia el estado del flag de status del puerto com
void c_flags_NV9::flag_status_com(bool flag)
{
    status_com = flag;
    //cout << status_com;
}

//Cambia el estado del flag de escritura del puerto com
void c_flags_NV9::flag_escritura_com(bool flag)
{
    escritura_com = flag;
    //cout << escritura_com;
}

//Cambia el estado del flag de sincronismo del validador de billetes
void c_flags_NV9::flag_sincronismo_com(unsigned char flag)
{
    sincronismo_bill_com = {flag};
}
