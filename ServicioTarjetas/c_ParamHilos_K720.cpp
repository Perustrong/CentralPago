#include "ServicioTarjetas/c_ParamHilos_K720.h"
#include <windows.h>
#include "ServicioTarjetas/c_flags_K720.h"

c_ParamHilos_K720::c_ParamHilos_K720()
{
}

c_ParamHilos_K720::~c_ParamHilos_K720()
{
}



void c_ParamHilos_K720::AddValorHANDLE(HANDLE* InhComPort)
{
	hComPort = InhComPort;
}
void c_ParamHilos_K720::AddValorBuffer(TCHAR* InBufferLectura)
{
	BufferLectura = *InBufferLectura;
}
void c_ParamHilos_K720::AddValorFlags(c_flags_K720* InCom)
{
	Com = *InCom;
}

TCHAR* c_ParamHilos_K720::ParamBuffer()
{
	return &BufferLectura;
}

HANDLE* c_ParamHilos_K720::ParamhComPort()
{
	return hComPort;
}

c_flags_K720* c_ParamHilos_K720::ParamCom()
{
	
	return &Com;
	
}


