#include "ServicioEfectivo/c_paramhilos_nv9.h"

c_ParamHilos_NV9::c_ParamHilos_NV9()
{

}

void c_ParamHilos_NV9::AddValorHANDLE(HANDLE* InhComPort)
{
    hComPort = InhComPort;
}
void c_ParamHilos_NV9::AddValorBuffer(TCHAR* InBufferLectura)
{
    BufferLectura = *InBufferLectura;
}
void c_ParamHilos_NV9::AddValorFlags(c_flags_NV9* InCom)
{
    Com = *InCom;
}

TCHAR* c_ParamHilos_NV9::ParamBuffer()
{
    return &BufferLectura;
}

HANDLE* c_ParamHilos_NV9::ParamhComPort()
{
    return hComPort;
}

c_flags_NV9* c_ParamHilos_NV9::ParamCom()
{

    return &Com;

}
