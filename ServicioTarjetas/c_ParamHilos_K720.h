#ifndef c_PARAMHILOS_K720_H
#define c_PARAMHILOS_K720_H

#include <windows.h>
#include "ServicioTarjetas/c_flags_K720.h"

class c_ParamHilos_K720
{
	public:
		c_ParamHilos_K720();
		~c_ParamHilos_K720();
		void AddValorHANDLE(HANDLE* InhComPort);
		void AddValorBuffer(TCHAR* InBufferLecturaIn);
		void AddValorFlags(c_flags_K720* InCom);
		TCHAR* ParamBuffer();
		HANDLE* ParamhComPort();
		c_flags_K720* ParamCom();
	protected:
		
		
	private:
		HANDLE* hComPort;
		TCHAR BufferLectura;
		c_flags_K720 Com;
		
};

#endif
