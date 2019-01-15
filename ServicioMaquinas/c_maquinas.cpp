#include "ServicioMaquinas/c_Maquinas.h"
#include <QThread>

c_Maquinas::c_Maquinas(QObject *parent) //: QObject()
{


    PreciosEfectivo.Extra1 = 0.50;
    PreciosEfectivo.Extra2 = 0.50;
    PreciosEfectivo.Extra3 = 0.50;
    PreciosEfectivo.MinutoSecado = 0.40;
    PreciosEfectivo.ProgramaLigero = 4.50;
    PreciosEfectivo.ProgramaMedio = 7.50;
    PreciosEfectivo.ProgramaPesado = 9.50;
    PreciosEfectivo.ProgramaSecado = 3;


    PreciosTarjeta.Extra1 = 0.40;
    PreciosTarjeta.Extra2 = 0.40;
    PreciosTarjeta.Extra3 = 0.40;
    PreciosTarjeta.MinutoSecado = 0.30;
    PreciosTarjeta.ProgramaLigero = 3.60;
    PreciosTarjeta.ProgramaMedio = 6.00;
    PreciosTarjeta.ProgramaPesado = 7.00;
    PreciosTarjeta.ProgramaSecado = 2.40;

    c_LogFileMaquinas LogFileMaquinas;
}

//c_Maquinas::~c_Maquinas(){}

void c_Maquinas::run()
{
    while (HiloActivo==true)
    {
        switch(AccionHilo)
        {
        case 1:
        {
            MaqStatus();
            Sleep(1500);
            break;
        }
        case 2:
        {
            InfoStatus(numTipoMaquina);
            Sleep(500);
            break;
        }
        }




    }


}

void c_Maquinas::   set_numExtras(int Extras)
{
    numExtras = Extras;
    switch (numExtras)
    {
    case 0:
    {
        CmdNumProgram = (unsigned char)(numPrograma);
        break;
    }
    case 1:
    {
        CmdNumProgram = (unsigned char)(numPrograma+4);
        break;
    }
    case 2:
    {
        CmdNumProgram = (unsigned char)(numPrograma+8);
        break;
    }
    case 3:
    {
        CmdNumProgram = (unsigned char)(numPrograma+16);
        break;
    }
    case 4:
    {
        CmdNumProgram = (unsigned char)(numPrograma+12);
        break;
    }
    case 5:
    {
        CmdNumProgram = (unsigned char)(numPrograma+20);
        break;
    }
    case 6:
    {
        CmdNumProgram = (unsigned char)(numPrograma+24);
        break;
    }
    case 7:
    {
        CmdNumProgram = (unsigned char)(numPrograma+28);
        break;
    }


    }

}

void c_Maquinas::set_numMaquina(int Maquina)
{
    numMaquina = Maquina;


}

void c_Maquinas::set_numPrograma(int Programa)
{
    numPrograma = Programa;
    CmdNumProgram = (unsigned char) numPrograma;

}

void c_Maquinas::set_numTipoMaquina(int TipoMaquina)
{
    numTipoMaquina = TipoMaquina;

}

void c_Maquinas::set_numTiempoExtra(int newTiempoExtra)
{

    numTiempoExtra = newTiempoExtra;
}

void c_Maquinas::set_PreciosEfectivo(int Parametro, float valor)
{
    switch (Parametro)
    {
    case PROGRAMA_LIGERO:
        PreciosEfectivo.ProgramaLigero = valor;
    break;

    case PROGRAMA_MEDIO:
        PreciosEfectivo.ProgramaMedio = valor;
    break;

    case PROGRAMA_PESADO:
         PreciosEfectivo.ProgramaPesado = valor;
    break;

    case PROGRAMA_SECADO:
        PreciosEfectivo.ProgramaSecado = valor;
    break;

    case MINUTO_SECADO:
        PreciosEfectivo.MinutoSecado = valor;
    break;

    case EXTRA_1:
        PreciosEfectivo.Extra1 = valor;
    break;

    case EXTRA_2:
        PreciosEfectivo.Extra2 = valor;
    break;

    case EXTRA_3:
        PreciosEfectivo.Extra3 = valor;
    break;



    default:
        break;
    }

}

void c_Maquinas::set_PreciosTarjeta(int Parametro, float valor)
{
    switch (Parametro)
    {
    case PROGRAMA_LIGERO:
        PreciosTarjeta.ProgramaLigero = valor;
    break;

    case PROGRAMA_MEDIO:
        PreciosTarjeta.ProgramaMedio = valor;
    break;

    case PROGRAMA_PESADO:
         PreciosTarjeta.ProgramaPesado = valor;
    break;

    case PROGRAMA_SECADO:
        PreciosTarjeta.ProgramaSecado = valor;
    break;

    case MINUTO_SECADO:
        PreciosTarjeta.MinutoSecado = valor;
    break;

    case EXTRA_1:
        PreciosTarjeta.Extra1 = valor;
    break;

    case EXTRA_2:
        PreciosTarjeta.Extra2 = valor;
    break;

    case EXTRA_3:
        PreciosTarjeta.Extra3 = valor;
    break;



    default:
        break;
    }

}







int c_Maquinas::get_numExtras()
{
    return numExtras;

}

int c_Maquinas::get_numMaquina()
{
    return numMaquina;

}

int c_Maquinas::get_numPrograma()
{
    return numPrograma;


}

int c_Maquinas::get_numTipoMaquina()
{
    return numTipoMaquina;

}

int c_Maquinas::get_numTiempoExtra()
{
    return numTiempoExtra;

}

float c_Maquinas::get_PreciosEfectivo(int Parametro)
{
    switch (Parametro)
    {
    case PROGRAMA_LIGERO:
       return PreciosEfectivo.ProgramaLigero;
    break;

    case PROGRAMA_MEDIO:
        return PreciosEfectivo.ProgramaMedio;
    break;

    case PROGRAMA_PESADO:
         return PreciosEfectivo.ProgramaPesado;
    break;

    case PROGRAMA_SECADO:
        return PreciosEfectivo.ProgramaSecado;
    break;

    case MINUTO_SECADO:
        return PreciosEfectivo.MinutoSecado;
    break;

    case EXTRA_1:
        return PreciosEfectivo.Extra1;
    break;

    case EXTRA_2:
        return PreciosEfectivo.Extra2;
    break;

    case EXTRA_3:
        return PreciosEfectivo.Extra3;
    break;



    default:
        break;
    }

}

float c_Maquinas::get_PreciosTarjeta(int Parametro)
{

    switch (Parametro)
    {
    case PROGRAMA_LIGERO:
       return PreciosTarjeta.ProgramaLigero;
    break;

    case PROGRAMA_MEDIO:
        return PreciosTarjeta.ProgramaMedio;
    break;

    case PROGRAMA_PESADO:
         return PreciosTarjeta.ProgramaPesado;
    break;

    case PROGRAMA_SECADO:
        return PreciosTarjeta.ProgramaSecado;
    break;

    case MINUTO_SECADO:
        return PreciosTarjeta.MinutoSecado;
    break;

    case EXTRA_1:
        return PreciosTarjeta.Extra1;
    break;

    case EXTRA_2:
        return PreciosTarjeta.Extra2;
    break;

    case EXTRA_3:
        return PreciosTarjeta.Extra3;
    break;



    default:
        break;
    }
}


    void c_Maquinas::set_CmdNumMaq(unsigned char Cmd)
    {
        CmdNumMaq = Cmd;
        ActualizarEstados();

    }
    void c_Maquinas::set_CmdNumProgram(unsigned char Cmd)
    {
        CmdNumProgram = Cmd;
        ActualizarEstados();
        printf("Numero de programa seleccionado = %x",CmdNumProgram);

    }
    void c_Maquinas::set_CmdNumFase(unsigned char Cmd)
    {
        CmdNumFase = Cmd;
        ActualizarEstados();

    }
    void c_Maquinas::set_CmdTiempoSecado(unsigned char Cmd)
    {
        CmdTiempoSecado = Cmd;
        ActualizarEstados();

    }
    void c_Maquinas::set_CmdCalefaccion(unsigned char Cmd)
    {
        CmdCalefaccion = Cmd;
        ActualizarEstados();

    }
    void c_Maquinas::set_CmdTempSalida(unsigned char Cmd)
    {
        CmdTempSalida = Cmd;
        ActualizarEstados();

    }
    void c_Maquinas::set_CmdTempEntrada(unsigned char Cmd)
    {
        CmdTempEntrada = Cmd;
        ActualizarEstados();

    }
    void c_Maquinas::set_CmdVelRotacion(unsigned char Cmd)
    {
        CmdVelRotacion = Cmd;
        ActualizarEstados();

    }
    void c_Maquinas::set_CmdAccionMecanica(unsigned char Cmd)
    {
        CmdAccionMecanica = Cmd;
        ActualizarEstados();

    }
    void c_Maquinas::set_CmdTiempoEnfriamiento(unsigned char Cmd)
    {
        CmdTiempoEnfriamiento = Cmd;
        ActualizarEstados();

    }
    void c_Maquinas::set_CmdMinExtraSecado(unsigned char Cmd)
    {
        CmdMinExtraSecado = Cmd;
        ActualizarEstados();

    }
    void c_Maquinas::set_CmdTimeNoTeclado(unsigned char Cmd)
    {
        CmdTimeNoTeclado = Cmd;
        ActualizarEstados();

    }
    void c_Maquinas::set_CmdHabilitarFase(unsigned char Cmd)
    {
        CmdHabilitarFase = Cmd;
        ActualizarEstados();

    }
    void c_Maquinas::set_CmdNivelBano(unsigned char Cmd)
    {
        CmdNivelBano = Cmd;
        ActualizarEstados();

    }
    void c_Maquinas::set_CmdTemperatura(unsigned char Cmd)
    {
        CmdTemperatura = Cmd;
        ActualizarEstados();

    }
    void c_Maquinas::set_CmdDosificacion(unsigned char Cmd)
    {
        CmdDosificacion = Cmd;
        ActualizarEstados();

    }
    void c_Maquinas::set_CmdTiempoRotacion(unsigned char Cmd)
    {
        CmdTiempoRotacion = Cmd;
        ActualizarEstados();

    }
    void c_Maquinas::set_CmdDesague(unsigned char Cmd)
    {
        CmdDesague = Cmd;
        ActualizarEstados();

    }
    void c_Maquinas::set_CmdTiempoCentrifugado(unsigned char Cmd)
    {
        CmdTiempoCentrifugado = Cmd;
        ActualizarEstados();


    }
    void c_Maquinas::set_CmdEnfriamiento(unsigned char Cmd)
    {
        CmdEnfriamiento = Cmd;
        ActualizarEstados();


    }
    void c_Maquinas::set_CmdPausa(unsigned char Cmd)
    {
        CmdPausa = Cmd;
        ActualizarEstados();

    }
    void c_Maquinas::set_CmdTiempoDosificacion(unsigned char Cmd)
    {
        CmdTiempoDosificacion = Cmd;
        ActualizarEstados();

    }
    void c_Maquinas::set_CmdModoLavadoExtra(unsigned char Cmd)
    {
        CmdModoLavadoExtra = Cmd;
        ActualizarEstados();

    }
    void c_Maquinas::set_CmdTiempoLavadoExtra(unsigned char Cmd)
    {
        CmdTiempoLavadoExtra = Cmd;
        ActualizarEstados();

    }
    void c_Maquinas::set_CmdModoAclaradoExtra(unsigned char Cmd)
    {
        CmdModoAclaradoExtra = Cmd;
        ActualizarEstados();

    }
    void c_Maquinas::set_CmdModoCentrifugadoExtra(unsigned char Cmd)
    {
        CmdModoCentrifugadoExtra = Cmd;
        ActualizarEstados();
    }
    void c_Maquinas::set_CmdTiempoCentrifugadoExtra(unsigned char Cmd)
    {
        CmdTiempoCentrifugadoExtra = Cmd;
        ActualizarEstados();
    }



bool c_Maquinas::ConfigLav(unsigned char NumMaq, unsigned char NumProg, unsigned char NumFase, unsigned char Habilitar, unsigned char NivelBano,
                           unsigned char Temp, unsigned char Dosificar, unsigned char TiempoDosi, unsigned char AccionMec, unsigned char TiempoRot,
                           unsigned char Desague, unsigned char TiempoCent, unsigned char Enfriamiento, unsigned char Pausa)
{
    bool enviado = false;

    CmdNumMaq = NumMaq;
    CmdNumProgram = NumProg;
    CmdNumFase = NumFase;
    CmdHabilitarFase = Habilitar;
    CmdNivelBano = NivelBano;
    CmdTemperatura = Temp;
    CmdDosificacion = Dosificar;
    CmdTiempoDosificacion = TiempoDosi;
    CmdAccionMecanica = AccionMec;
    CmdTiempoRotacion = TiempoRot;
    CmdDesague = Desague;
    CmdTiempoCentrifugado = TiempoCent;
    CmdEnfriamiento = Enfriamiento;
    CmdPausa = Pausa;

    enviado = SendCmd(CmdEditPhaseLav);
    return enviado;

}

bool c_Maquinas::ConfigSec(unsigned char NumMaq, unsigned char NumProg, unsigned char TiempoSec, unsigned char Calefaccion, unsigned char TempSalida,
                           unsigned char TempEntrada, unsigned char VelRotacion, unsigned char AccionMec, unsigned char TiempoEnfri)
{
    bool enviado = false;

    CmdNumMaq = NumMaq;
    CmdNumProgram = NumProg;
    CmdTiempoSecado = TiempoSec;
    CmdCalefaccion = Calefaccion;
    CmdTempSalida = TempSalida;
    CmdTempEntrada = TempEntrada;
    CmdVelRotacion = VelRotacion;
    CmdAccionMecanica = AccionMec;
    CmdTiempoEnfriamiento = TiempoEnfri;

    enviado = SendCmd(CmdEditProgramSec);
    return enviado;

}

HANDLE c_Maquinas::ConectarLav()
{

    dcbComLav.BaudRate = CBR_38400;     //  baud rate
    dcbComLav.ByteSize = 8;             //  data size, xmit and rcv
    dcbComLav.Parity   = NOPARITY;      //  parity bit
    dcbComLav.StopBits = TWOSTOPBITS;    //  stop bit

    SetCommState(hComPortLav, &dcbComLav);

    hComPortLav = CreateFile( CommPortLav,
                      GENERIC_READ | GENERIC_WRITE, // solo pueden ser estos valores
                      0,
                      NULL,
                      OPEN_EXISTING, // solo puede ser OPEN_EXISTING
                      FILE_FLAG_OVERLAPPED,
                      NULL);
    if (hComPortLav == INVALID_HANDLE_VALUE)
    {    // no se pudo abrir el puerto COM3:
      cout<<"No se pudo abrir el puerto Lavadora."<<endl;
      return NULL;

    }
    else
    {
        cout<<"En toería conectado";

        cout<<"hComPort conectar "<< hComPortLav<<endl;
    }

    SetCommState(hComPortLav, &dcbComLav);
    emit HandleLavadora(hComPortLav);
    return hComPortLav;
}



HANDLE c_Maquinas::ConectarSec()
{

    dcbComSec.BaudRate = CBR_38400;     //  baud rate
    dcbComSec.ByteSize = 8;             //  data size, xmit and rcv
    dcbComSec.Parity   = NOPARITY;      //  parity bit
    dcbComSec.StopBits = TWOSTOPBITS;    //  stop bit

    SetCommState(hComPortSec, &dcbComSec);

    hComPortSec = CreateFile( CommPortSec,
                      GENERIC_READ | GENERIC_WRITE, // solo pueden ser estos valores
                      0,
                      NULL,
                      OPEN_EXISTING, // solo puede ser OPEN_EXISTING
                      FILE_FLAG_OVERLAPPED,
                      NULL);
    if (hComPortSec == INVALID_HANDLE_VALUE)
    {    // no se pudo abrir el puerto COM3:
      cout<<"No se pudo abrir el puerto Secadora."<<endl;
      return NULL;
    }
    else
    {
        cout<<"En toería conectado";
        cout<<"hComPort conectar "<< hComPortSec<<endl;
        emit (HandleSecadora(hComPortSec));

    }

    SetCommState(hComPortSec, &dcbComSec);
    return hComPortSec;

}

unsigned char c_Maquinas::CalculaCRC(unsigned char *Cmd)
{
    int NumberData = (int)Cmd[1];
    int SizeMensaje = NumberData + 5;
    unsigned char Mensaje[SizeMensaje];
    unsigned char CRC = {0x00};
    for (int i=0;i<SizeMensaje;i++)
    {
        Mensaje[i] = Cmd[i];

    }
    for (int i=0;i<SizeMensaje;i++)
    {
        CRC = CRC^Mensaje[i];

    }
    printf("CRC Calculado = %x",CRC);
    return CRC;
}

bool c_Maquinas::SendCmd(unsigned char* Cmd)
{
    //QThread *Thread1 = new QThread;
    //this->moveToThread(Thread1);
    int NumberData = (int)Cmd[1];
    //cout <<"Tamaño datos a enviar= "<<NumberData<<"numero de maquina = ";
    //printf("%x",CmdNumMaq);
    int SizeMensaje = NumberData + 6;
    unsigned char ComandoEnvio[SizeMensaje];
    LPDCB auxdcb = new DCB;
    GetCommState(hComPortLav,auxdcb);
   // ActualizarEstados();
   // cout<<"BaudRate = "<<auxdcb->BaudRate<<"StopByte = "<<auxdcb->StopBits<<endl;
   // printf("BaudRato = %x, StopBits = %x",auxdcb->BaudRate,auxdcb->StopBits);

    for(int i = 0;i<SizeMensaje;i++)
    {
        if(i == 2)
        {
            ComandoEnvio[i]=CmdNumMaq;
            printf("Byte envio a sendcmd = %x",ComandoEnvio[i]);
        }
        else
        {
            ComandoEnvio[i]=Cmd[i];
            printf("Byte envio a sendcmd = %x",Cmd[i]);
        }
    }
    DWORD lpModemStat;

    cout<<"Entrado en envío de comandos maquinas"<<endl;
    cout<<"hComPortLav conectar "<< hComPortLav<<endl;

    HANDLE hComPort = NULL;

  /*  if (hComPortLav == 0 && hComPortSec == 0)
    {
        if(numTipoMaquina==1)
        {
           hComPortLav = ConectarLav();
           hComPort = hComPortLav;
           emit HandleLavadora(hComPort);
        }
        else if(numTipoMaquina == 2)
        {
            hComPortSec = ConectarSec();
            hComPort = hComPortSec;
            emit (HandleLavadora(hComPort));
        }
    }
    else if (hComPortLav == 0)
    {
       hComPort  = hComPortSec;
    }
    else if(hComPortSec == 0)
    {
        hComPort = hComPortLav;
    }*/
    if(numTipoMaquina == 1 && hComPortLav == 0)
    {
        hComPortLav = ConectarLav();
        hComPort = hComPortLav;
        cout<<"ConectandoLavadora"<<endl;
        emit HandleLavadora(hComPort);
    }
    else if(numTipoMaquina == 2 && hComPortSec == 0)
    {
        cout<< "Conectando con secadora"<<endl;
        hComPortSec = ConectarSec();
        hComPort = hComPortSec;
        emit (HandleSecadora(hComPort));
    }
    else
    {
        if(numTipoMaquina == 1)
        {
           hComPort = hComPortLav;
           emit HandleLavadora(hComPort);
        }
        else if(numTipoMaquina == 2)
        {
            hComPort = hComPortSec;
            emit (HandleSecadora(hComPort));
        }

    }

   // cout<<"hComPort conectar "<< hComPort<<endl;
   // ClearCommError(hComPort,&lpModemStat,NULL);
   /* if(GetCommModemStatus(hComPort,&lpModemStat)==0)
    {
        cout <<GetLastError()<<endl;

        if(numTipoMaquina==1)
        {
           hComPortLav = ConectarLav();
           hComPort = hComPortLav;
           emit HandleLavadora(&hComPort);
        }
        else if(numTipoMaquina == 2)
        {
            hComPortSec = ConectarSec();
            hComPort = hComPortSec;
            emit (HandleLavadora(hComPort));
        }

        if(GetCommModemStatus(hComPort,&lpModemStat)==0)
        {
               return false;
        }
    }*/

        ComandoEnvio[SizeMensaje-1] = CalculaCRC(ComandoEnvio);
    //    printf("ComandoenvioSizeMensaje = %x",ComandoEnvio[SizeMensaje]);

        DWORD BufferSizeCom = SizeMensaje;
       // cout<<"Tamaño del mensaje = "<<BufferSizeCom<<endl;
        DWORD BytesEscritos = 0;
       // unsigned char AuxMensaje[SizeMensaje];
       // unsigned char* CRCAux[2];// = new unsigned char[2];

        OVERLAPPED ovEscribir2;
       // bool testing = false;
        ovEscribir2.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);


        if (ovEscribir2.hEvent == NULL)
        {
            cout<<"No creado"<<endl;

        }
      /*  for (int i=0; i<SizeMensaje;i++)
        {
            cout << "Byte envío"<<i<<endl;
            printf("%x", ComandoEnvio[i]);
        }*/
       // cout << " Entrado en envío333"<<endl;
       // Issue write.
        if(numTipoMaquina == 1)
        {
            if (!WriteFile(hComPortLav, ComandoEnvio, BufferSizeCom, &BytesEscritos, &ovEscribir2))
            {


                if (GetLastError() != ERROR_IO_PENDING)
                {
                 // WriteFile failed, but it isn't delayed. Report error and abort.
                    cout<<"Pendiente env�o";
                    return false;

                }
                else
                {

                 // Write is pending.

                    if (GetOverlappedResult(hComPortLav, &ovEscribir2, &BytesEscritos, TRUE))
                    {
                        cout<<"Enviado. Bytes Escritos = " << BytesEscritos;
                        ResetEvent(ovEscribir2.hEvent);
                        return true;


                    }
                }
           }
           else
           {
                // WriteFile completed immediately.
               // return true;
                cout << "Enviado Directo"<<endl;
                CloseHandle(ovEscribir2.hEvent);
                return true;
            }
        }
        else if(numTipoMaquina == 2)
        {
            if (!WriteFile(hComPortSec, ComandoEnvio, BufferSizeCom, &BytesEscritos, &ovEscribir2))
            {


                if (GetLastError() != ERROR_IO_PENDING)
                {
                 // WriteFile failed, but it isn't delayed. Report error and abort.
                    cout<<"Pendiente env�o";
                    return false;

                }
                else
                {

                 // Write is pending.

                    if (GetOverlappedResult(hComPortSec, &ovEscribir2, &BytesEscritos, TRUE))
                    {
                        cout<<"Enviado. Bytes Escritos = " << BytesEscritos;
                        ResetEvent(ovEscribir2.hEvent);
                        return true;


                    }
                }
           }
           else
           {
                // WriteFile completed immediately.
               // return true;
                cout << "Enviado Directo"<<endl;
                CloseHandle(ovEscribir2.hEvent);
                return true;
            }
        }
}







void c_Maquinas::InfoStatus(unsigned char Maquina)
{

    cout << "InfoStatus Numero de Máquina = ";
    printf("%x",CmdNumMaq);
    if(numTipoMaquina==1)
    {
        bool enviado = SendCmd(CmdReadStatusLav);
        if(enviado ==false)cout<<"Comando de lectura info no se ha enviado correctamente"<<endl;


    }
    else if(numTipoMaquina==2)
    {
        bool enviado = SendCmd(CmdReadStatusSec);
        if(enviado ==false)cout<<"Comando de lectura info no se ha enviado correctamente"<<endl;

    }

}

/*void c_Maquinas::SlotHilo()
{
    moveToThread(&Hilo);
    qRegisterMetaType<HANDLE>("HANDLE");
    connect(&Hilo,SIGNAL(started()),this,SLOT(MaqStatus()));

    cout<<"Pasado por SLOT"<<endl;
    if(Hilo.isRunning())Hilo.terminate();
    Hilo.start();


}*/

void c_Maquinas::MaqStatus()
{

    cout << "InfoStatus Numero de Máquina = ";
    printf("%x",CmdNumMaq);
    if(numTipoMaquina==1)
    {
        CmdNumMaq = 0x01;
        bool enviado = SendCmd(CmdReadStatusLav);
        if(enviado ==false)cout<<"Comando de lectura info no se ha enviado correctamente"<<endl;
        else RespuestaLav[1]=false;
        Sleep(500);
        if(RespuestaLav[1]==false)
        {
            emit InhabilitarLavadora(0x01);
        }
        CmdNumMaq = 0x02;
        enviado = SendCmd(CmdReadStatusLav);
        if(enviado ==false)cout<<"Comando de lectura info no se ha enviado correctamente"<<endl;
        else RespuestaLav[2]=false;
        Sleep(500);
        if(RespuestaLav[2]==false)
        {
            emit InhabilitarLavadora(0x02);
        }
        CmdNumMaq = 0x03;
        enviado = SendCmd(CmdReadStatusLav);
        if(enviado ==false)cout<<"Comando de lectura info no se ha enviado correctamente"<<endl;
        else RespuestaLav[3]=false;
        Sleep(500);
        if(RespuestaLav[3]==false)
        {
            emit InhabilitarLavadora(0x03);
        }
        CmdNumMaq = 0x04;
        enviado = SendCmd(CmdReadStatusLav);
        if(enviado ==false)cout<<"Comando de lectura info no se ha enviado correctamente"<<endl;
        else RespuestaLav[4]=false;
        Sleep(500);
        if(RespuestaLav[4]==false)
        {
            emit InhabilitarLavadora(0x04);
        }
        CmdNumMaq = 0x05;
        enviado = SendCmd(CmdReadStatusLav);
        if(enviado ==false)cout<<"Comando de lectura info no se ha enviado correctamente"<<endl;
        else RespuestaLav[5]=false;
        Sleep(500);
        if(RespuestaLav[5]==false)
        {
            emit InhabilitarLavadora(0x05);
        }
        CmdNumMaq = 0x06;
        enviado = SendCmd(CmdReadStatusLav);
        if(enviado ==false)cout<<"Comando de lectura info no se ha enviado correctamente"<<endl;
        else RespuestaLav[6]=false;
        Sleep(500);
        if(RespuestaLav[6]==false)
        {
            emit InhabilitarLavadora(0x06);
        }


    }
    else if(numTipoMaquina==2)
    {
        cout<<"Envio Hilo Secadora"<<endl;
        CmdNumMaq = 0x01;
        bool enviado = SendCmd(CmdReadStatusSec);
        if(enviado ==false)cout<<"Comando de lectura info no se ha enviado correctamente"<<endl;
        else RespuestaSec[1]=false;
        Sleep(300);
        if(RespuestaSec[1]==false)
        {
            emit InhabilitarSecadora(0x01);
        }
        CmdNumMaq = 0x02;
        enviado = SendCmd(CmdReadStatusSec);
        if(enviado ==false)cout<<"Comando de lectura info no se ha enviado correctamente"<<endl;
        else RespuestaSec[2]=false;
        Sleep(300);
        if(RespuestaSec[2]==false)
        {
            emit InhabilitarSecadora(0x02);
        }
        CmdNumMaq = 0x03;
        enviado = SendCmd(CmdReadStatusSec);
        if(enviado ==false)cout<<"Comando de lectura info no se ha enviado correctamente"<<endl;
        else RespuestaSec[6]=false;
        Sleep(300);
        if(RespuestaSec[6]==false)
        {
            emit InhabilitarSecadora(0x03);
        }
        CmdNumMaq = 0x04;
        enviado = SendCmd(CmdReadStatusSec);
        if(enviado ==false)cout<<"Comando de lectura info no se ha enviado correctamente"<<endl;
        else RespuestaSec[4]=false;
        Sleep(300);
        if(RespuestaSec[4]==false)
        {
            emit InhabilitarSecadora(0x04);
        }
        CmdNumMaq = 0x05;
        enviado = SendCmd(CmdReadStatusSec);
        if(enviado ==false)cout<<"Comando de lectura info no se ha enviado correctamente"<<endl;
        else RespuestaSec[5]=false;
        Sleep(300);
        if(RespuestaSec[5]==false)
        {
            emit InhabilitarSecadora(0x05);
        }
        CmdNumMaq = 0x06;
        enviado = SendCmd(CmdReadStatusSec);
        if(enviado ==false)cout<<"Comando de lectura info no se ha enviado correctamente"<<endl;
        else RespuestaSec[6]=false;
        Sleep(300);
        if(RespuestaSec[6]==false)
        {
            emit InhabilitarSecadora(0x06);
        }

    }



}





void c_Maquinas::ActualizarEstados()
{

    CmdReadStatusSec[2] = CmdNumMaq;
    CmdEditProgramSec[2] = CmdNumMaq;
    CmdEditProgramSec[5] = CmdNumProgram;
    CmdEditProgramSec[8] = CmdTiempoSecado;
    CmdEditProgramSec[9] = CmdCalefaccion;
    CmdEditProgramSec[10] = CmdTempSalida;
    CmdEditProgramSec[11] = CmdTempEntrada;
    CmdEditProgramSec[12] = CmdVelRotacion;
    CmdEditProgramSec[13] = CmdAccionMecanica;
    CmdEditProgramSec[14] = CmdTiempoEnfriamiento;
    CmdReadProgramSec[2] = CmdNumMaq;
    CmdReadProgramSec[2] = CmdNumMaq;
    CmdReadProgramSec[5] = CmdNumProgram;
    CmdProgramStartSec[2] =CmdNumMaq;
    CmdAddMinutesSec[2] = CmdNumMaq;
    CmdAddMinutesSec[5] = CmdMinExtraSecado;
    CmdProgramSelectionSec[2] =CmdNumMaq;
    CmdProgramSelectionSec[5] = CmdNumProgram;
    CmdReadPricesSec[2] =CmdNumMaq;
    CmdReadPricesSec[5] = CmdNumProgram;

    CmdFreezeKeyboardSec[2] =CmdNumMaq;
    CmdFreezeKeyboardSec[5] = CmdTimeNoTeclado;
    CmdReadInfoSec[2] = CmdNumMaq;
    CmdReadProgramCounterSec[2] = CmdNumMaq;
    CmdReadProgramCounterSec[5] = CmdNumProgram;
    CmdReadAlarmCounterSec[2] = CmdNumMaq;


    CmdReadStatusLav[2] = CmdNumMaq;
    CmdReadPhaseLav[2] = CmdNumMaq;
    CmdReadPhaseLav[5] = CmdNumProgram;
    CmdReadPhaseLav[6] = CmdNumFase;
    CmdEditPhaseLav[2] = CmdNumMaq;
    CmdEditPhaseLav[5] = CmdNumProgram;
    CmdEditPhaseLav[6] = CmdNumFase;
    CmdEditPhaseLav[7] = CmdHabilitarFase;
    CmdEditPhaseLav[8] = CmdNivelBano;
    CmdEditPhaseLav[9] = CmdTemperatura;
    CmdEditPhaseLav[10] = CmdDosificacion;
    CmdEditPhaseLav[11] = CmdAccionMecanica;
    CmdEditPhaseLav[12] = CmdTiempoRotacion;
    CmdEditPhaseLav[13] = CmdDesague;
    CmdEditPhaseLav[14] = CmdTiempoCentrifugado;
    CmdEditPhaseLav[15] = CmdEnfriamiento;
    CmdEditPhaseLav[16] = CmdPausa;
    CmdEditPhaseLav[19] = CmdTiempoDosificacion;
    CmdProgramStartLav[2] = CmdNumMaq;
    CmdProgramSelectionLav[2] = CmdNumMaq;
    CmdProgramSelectionLav[5] = CmdNumProgram;
    CmdReadExtraOptionLav[2] = CmdNumMaq;
    CmdEditExtraOptionLav[2] = CmdNumMaq;
    CmdEditExtraOptionLav[5] = CmdModoLavadoExtra;
    CmdEditExtraOptionLav[6] = CmdTiempoLavadoExtra;
    CmdEditExtraOptionLav[9] = CmdModoAclaradoExtra;
    CmdEditExtraOptionLav[10] = CmdTiempoAclaradoExtra;
    CmdEditExtraOptionLav[13] = CmdModoCentrifugadoExtra;
    CmdEditExtraOptionLav[14] = CmdTiempoCentrifugadoExtra;
    CmdReadInfoLav[2] = CmdNumMaq;
    CmdFreezeKeyboardLav[2] = CmdNumMaq;
    CmdFreezeKeyboardLav[5] = CmdTimeNoTeclado;
}


void c_Maquinas::onActualizarConfiguracionLav(string Comando)
{
    cout<<"Entrado en emision"<<endl;
    int numMaq = (int)Comando[0];
    int numProg = (int)Comando[1];
    set_CmdNumMaq((unsigned char)numMaq);
    //printf("Lavadora index = %x\n",(unsigned char)ui->BoxSelMaq->currentIndex());
    set_CmdNumProgram((unsigned char) numProg);
    for(int i=1;i<=6;i++)
    {
        set_CmdNumFase((unsigned char)i);
        printf("Lavadora phase = %x\n",(unsigned char)i);
        //Sleep(100);

        SendCmd(CmdReadPhaseLav);
        Sleep(300);

    }

}

void c_Maquinas::onActualizarConfiguracionSec(string Comando)
{

    cout<<"Entrado en emision"<<endl;
    int numMaq = (int)Comando[0];

    set_CmdNumMaq((unsigned char)numMaq);
    //printf("Lavadora index = %x\n",(unsigned char)ui->BoxSelMaq->currentIndex());

    for(int i=1;i<=3;i++)
    {
        set_CmdNumProgram((unsigned char)i);
        printf("Secadora phase = %x\n",(unsigned char)i);
        //Sleep(100);

        SendCmd(CmdReadProgramSec);
        Sleep(300);
    }

}

/*void c_Maquinas::onEstadoPuerta()
{



        Sleep(100);
        emit PuertaCerrada();



}*/

