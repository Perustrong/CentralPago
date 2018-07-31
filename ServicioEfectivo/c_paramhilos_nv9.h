#ifndef C_PARAMHILOS_NV9_H
#define C_PARAMHILOS_NV9_H

#include <windows.h>
#include "ServicioEfectivo/c_flags_nv9.h"

class c_ParamHilos_NV9
{
public:
    c_ParamHilos_NV9();
    void AddValorHANDLE(HANDLE* InhComPort);
    void AddValorBuffer(TCHAR* InBufferLecturaIn);
    void AddValorFlags(c_flags_NV9* InCom);
    TCHAR* ParamBuffer();
    HANDLE* ParamhComPort();
    c_flags_NV9* ParamCom();
protected:


private:
    HANDLE* hComPort;
    TCHAR BufferLectura;
    c_flags_NV9 Com;
};

#endif // C_PARAMHILOS_NV9_H
