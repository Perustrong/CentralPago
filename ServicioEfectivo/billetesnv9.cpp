#include "ServicioEfectivo/billetesnv9.h"


//#include "c_comandos_nv9.h"



#define STRING_SIZE 200
#define MENSAJEOK 0xf0
#define BILLETEINSERTADO 0xef
#define BILLETEGUARDADO 0xcc
#define BILLETERECHAZADO 0xed
#define CANAL0 0x00
#define BILLETE5 0x01
#define BILLETE10 0x02
#define BILLETE20 0x03

unsigned long crcmask;
unsigned long crchighbit;
unsigned long crcinit_direct;
unsigned long crcinit_nondirect;
unsigned long crctab[256];
const int order = 16;
const unsigned long polynom = 0x8005;
const int direct = 1;
const unsigned long crcinit = 0xffff;
const unsigned long crcxor = 0;

using namespace std;



BilletesNV9::BilletesNV9()
{
    ConectarPuertoCom();
    cout<<"Conectado hComPortNV9"<<hComPort<<endl;
    Sleep(100);

}

unsigned long BilletesNV9::reflect (unsigned long crc, int bitnum) {

    // reflects the lower 'bitnum' bits of 'crc'

    unsigned long i, j=1, crcout=0;

    for (i=(unsigned long)1<<(bitnum-1); i; i>>=1) {
        if (crc & i) crcout|=j;
        j<<= 1;
    }
    return (crcout);
}



void BilletesNV9::generate_crc_table() {

    // make CRC lookup table used by table algorithms

    int i, j;
    unsigned long bit, crc;

    for (i=0; i<256; i++) {

        crc=(unsigned long)i;
        crc<<= order-8;

        for (j=0; j<8; j++) {

            bit = crc & crchighbit;
            crc<<= 1;
            if (bit) crc^= polynom;
        }

        crc&= crcmask;
        crctab[i]= crc;
    }
}



unsigned long BilletesNV9::crcbitbybit(unsigned char* p, unsigned long len){

    // bit by bit algorithm with augmented zero bytes.
    // does not use lookup table, suited for polynom orders between 1...32.
   // cout << "Tamaño len = "<< len<<endl;

    unsigned long i, j, c, bit;
    unsigned long crc = crcinit_nondirect;

    for (i=0; i<len; i++) {

        c = (unsigned long)*p++;

        for (j=0x80; j; j>>=1) {

            bit = crc & crchighbit;
            crc<<= 1;
            if (c & j) crc|= 1;
            if (bit) crc^= polynom;
        }
    }

    for (i=0; i<order; i++) {

        bit = crc & crchighbit;
        crc<<= 1;
        if (bit) crc^= polynom;
    }

    crc^= crcxor;
    crc&= crcmask;



    return(crc);
}



void BilletesNV9::CalculoCRC16(unsigned char Mensaje[], int SizeMensaje)
{


// 'order' [1..32] is the CRC polynom order, counted without the leading '1' bit
// 'polynom' is the CRC polynom without leading '1' bit
// 'direct' [0,1] specifies the kind of algorithm: 1=direct, no augmented zero bits
// 'crcinit' is the initial CRC value belonging to that algorithm
// 'crcxor' is the final XOR value



// Data character string

unsigned char AuxMensaje[SizeMensaje];
//TCHAR CRC16[2];

// internal global values:

for (int i=0;i<SizeMensaje;i++)
    {
      /*  cout<<"Mensaje para CRC";
        printf("0x");
        printf("%X", Mensaje[i] & 0xff);
        cout<<endl;*/
        AuxMensaje[i]=Mensaje[i];
             /*  cout<<"AuxMensaje para CRC";
        printf("0x");
        printf("%X", AuxMensaje[i] & 0xff);*/
    }

// subroutines



    // test program for checking four different CRC computing types that are:
    // crcbit(), crcbitfast(), crctable() and crctablefast(), see above.
    // parameters are at the top of this program.
    // Result will be printed on the console.

    int i;

    unsigned long bit, crc, crcaux;


    // at first, compute constant bit masks for whole CRC and CRC high bit

    crcmask = ((((unsigned long)1<<(order-1))-1)<<1)|1;
    crchighbit = (unsigned long)1<<(order-1);


    // check parameters


    // generate lookup table

    generate_crc_table();



    if (direct) {

        crcinit_direct = crcinit;
        crc = crcinit;
        for (i=0; i<order; i++) {

            bit = crc & 1;
            if (bit) crc^= polynom;
            crc >>= 1;
            if (bit) crc|= crchighbit;
        }
        crcinit_nondirect = crc;
    }

    crcaux = crcbitbybit((unsigned char*)AuxMensaje, SizeMensaje);
 //   printf(" crc bit by bit      :  0x%x\n", crcaux);
     //   cout << "Tamaño de crcaux = "<<sizeof(crcaux)<<endl;

    stringstream sstream;
    sstream<<hex<<crcaux;
        //sstream<<crcaux;
    string result = sstream.str();
        //unsigned char Byte2= (unsigned char)strtol(&result,NULL,16);



     //   cout << a <<","<<b<<endl;

        char auxresult1[2];
        char auxresult2[2];

        for (int i =0 ; i<4;i++)
        {
            if(i<2) auxresult1[i]=result[i];
            else auxresult2[i-2]=result[i];
        }
     /*   for(int i =0; i<=3; i++)
        {
            cout << "Resultado" <<result[i]<<endl;
            printf("result string  %x\n",result[i]);

        }*/




        if (result[3]==0)
    {
                auxresult2[1] =auxresult2[0];
        auxresult2[0] =auxresult1[1];
        auxresult1[1] =auxresult1[0];
        auxresult1[0] = {0x30};

    }
        unsigned char resultbyte1; //= ( ( auxresult2[0] - '0' ) << 4 ) | ( auxresult2[1] - '0' );
        unsigned char resultbyte2;// = ( ( auxresult1[0] - '0' ) << 4 ) | ( auxresult1[1] - '0' );

        resultbyte1 = (auxresult2[0] <= '9' ? auxresult2[0] - '0' : toupper(auxresult2[0]) - 'A' + 10) << 4;
        resultbyte1 |= auxresult2[1] <= '9' ? auxresult2[1] - '0' : toupper(auxresult2[1]) - 'A' + 10;

        resultbyte2 = (auxresult1[0] <= '9' ? auxresult1[0] - '0' : toupper(auxresult1[0]) - 'A' + 10) << 4;
        resultbyte2 |= auxresult1[1] <= '9' ? auxresult1[1] - '0' : toupper(auxresult1[1]) - 'A' + 10;

      //  printf("result1 principal  %c\n",(auxresult1[0]));
     //   printf("result2 principal  %c\n",auxresult1[1]);
     //   printf("result3 principal  %c\n",auxresult2[0]);
     //   printf("result0 principal  %c\n",auxresult2[1]);
     //   printf("result3 principalCompuesto1  %x\n",resultbyte1);
      //  printf("result0 principalCompuesto2  %x\n",resultbyte2);



    CRC16[0] = resultbyte1;
    CRC16[1] = resultbyte2;



    // call CRC algorithms using the CRC parameters above and print result to the console


}

void BilletesNV9::ConectarPuertoCom()
{
    dcbCom.BaudRate = CBR_9600;     //  baud rate
    dcbCom.ByteSize = 8;             //  data size, xmit and rcv
    dcbCom.Parity   = NOPARITY;      //  parity bit
    dcbCom.StopBits = TWOSTOPBITS;    //  stop bit

    SetCommState(hComPort, &dcbCom);

    hComPort = CreateFile( pcCommPort,
                      GENERIC_READ | GENERIC_WRITE, // solo pueden ser estos valores
                      0,
                      NULL,
                      OPEN_EXISTING, // solo puede ser OPEN_EXISTING
                      FILE_FLAG_OVERLAPPED,
                      NULL);
    if (hComPort == INVALID_HANDLE_VALUE)
    {    // no se pudo abrir el puerto COM3:
      cout<<"No se pudo abrir el puerto ."<<endl;
      FlagsCom.flag_status_com(false);
    }
    else
    {
        cout<<"En toería conectado";
        FlagsCom.flag_status_com(true);
        cout<<"hComPort conectar "<< hComPort<<endl;
    }

    SetCommState(hComPort, &dcbCom);
}

bool BilletesNV9::SyncBilletes()
{

    if(*FlagsCom.estado_com()==true)
    {

        EscribirPuertoCom(CmdSync,sizeof(CmdSync));
        Sleep(100);
        EscribirPuertoCom(CmdProtocolVersion,sizeof(CmdProtocolVersion));
        Sleep(100);
        EscribirPuertoCom(CmdSetUpRequest,sizeof(CmdSetUpRequest));
        Sleep(100);
        EscribirPuertoCom(CmdSetInhibits,sizeof(CmdSetInhibits));
        Sleep(100);
        EscribirPuertoCom(CmdPoll,sizeof(CmdPoll));
        Sleep(100);
        EscribirPuertoCom((CmdEnable),sizeof(CmdEnable));
        Sleep(100);
        EscribirPuertoCom((CmdDisplayOn),sizeof(CmdDisplayOn));
        Sleep(100);

    }
    else
    {
        ConectarPuertoCom();
        Sleep(100);
        EscribirPuertoCom(CmdSync,sizeof(CmdSync));
        Sleep(100);
        EscribirPuertoCom(CmdProtocolVersion,sizeof(CmdProtocolVersion));
        Sleep(100);
        EscribirPuertoCom(CmdSetUpRequest,sizeof(CmdSetUpRequest));
        Sleep(100);
        EscribirPuertoCom(CmdSetInhibits,sizeof(CmdSetInhibits));
        Sleep(100);
        EscribirPuertoCom(CmdPoll,sizeof(CmdPoll));
        Sleep(100);
        EscribirPuertoCom((CmdEnable),sizeof(CmdEnable));
        Sleep(100);
        EscribirPuertoCom((CmdDisplayOn),sizeof(CmdDisplayOn));
        Sleep(100);
    }
    return true;

}







void BilletesNV9::EscribirPuertoCom(unsigned char Mensaje[], int SizeMensaje)
{

    DWORD BufferSizeCom = SizeMensaje+3;
   // cout<<"Tamaño del mensaje = "<<BufferSizeCom<<endl;
    DWORD BytesEscritos;
    unsigned char AuxMensaje[SizeMensaje];
   // unsigned char* CRCAux[2];// = new unsigned char[2];
    unsigned char CRC[2];
    unsigned char ComandoEnvio[BufferSizeCom];
    int Contador = 0;
    unsigned char ControlSync[]={0x80,0x01,0x11};
    OVERLAPPED ovEscribir={0};
    bool testing = false;
    ovEscribir.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
        TCHAR* hola =TEXT("Hola");
 /* for (int i=0;i<=BufferSizeCom;i++)
  {
        cout<<"Mensaje recibido en Escribirpuerto";
        printf("0x");
        printf("%X", Mensaje[i] & 0xff);
        cout<<endl;
    }*/


    if(Mensaje[0]==ControlSync[0]&&Mensaje[1]==ControlSync[1]&&Mensaje[2]==ControlSync[2])
    {
       // cout << "Entrado en control de Sync";


        //for (int i=0;i<SizeMensaje+1;i++)

        for (int i=0;i<BufferSizeCom-2;i++)
        {
            if(i==0)
            {
                ComandoEnvio[0]={0x7F};
            }
            else
            {
          /*  cout<<"Lleagada Mensaje";
            printf("0x");
            printf("%X", Mensaje[i-1] & 0xff);
            cout<<endl;*/
            AuxMensaje[i-1]=Mensaje[i-1];
            ComandoEnvio[i]=AuxMensaje[i-1];
            }
            FlagsCom.flag_sincronismo_com(0x80);
            Contador++;
        }
    }
    else
    {
        //for (int i=0;i<SizeMensaje+1;i++)
        for (int i=0;i<BufferSizeCom-2;i++)
        {
            if(i==0)
            {
                ComandoEnvio[0]={0x7F};

            }
            else if (i==1)
            {
            ComandoEnvio[1]=FlagsCom.SyncBill_com();
            AuxMensaje[0]=FlagsCom.SyncBill_com();
          /*  cout<<"Lleagada Mensaje";
            printf("0x");
            printf("%X", Mensaje[i] & 0xff);
            cout<<endl;*/
            }
            else
            {
          /*  cout<<"Lleagada Mensaje";
            printf("0x");
            printf("%X", Mensaje[i-1] & 0xff);
            cout<<endl;*/
            AuxMensaje[i-1]=Mensaje[i-1];
            ComandoEnvio[i]=AuxMensaje[i-1];
            }

            Contador++;
        }
    }
    /*    for (int i=0;i<3;i++)
    {
    cout<<"Contenido AuxMensaje";
        printf("0x");
        printf("%X", AuxMensaje[i] & 0xff);
        cout<<endl;
    }*/
    CalculoCRC16(AuxMensaje,SizeMensaje);

    ComandoEnvio[Contador]=CRC16[0];
    ComandoEnvio[Contador+1]=CRC16[1];

  /*  cout<<"Valor contador = "<<Contador<<endl;
    printf("CRC161  %x\n",CRC16[1]);
    printf("CRC160 %x\n",CRC16[0]);*/

//	strcat(ComandoEnvio,CRC);
//	strncat(ComandoEnvio,*CRC[1],2);

  /*  for (int i=0;i<BufferSizeCom;i++)
    {
        cout <<"Comando Env�o"<<endl;
        printf("0x");
        printf("%X", ComandoEnvio[i] & 0xff);
        cout<<endl;
    }*/


  //  cout<<"hComPort escribir despu�s"<< hComPort<<endl;

    if (ovEscribir.hEvent == NULL)
    {
        cout<<"No creado"<<endl;

    }
   // Issue write.
    if (!WriteFile(hComPort, &ComandoEnvio, BufferSizeCom, &BytesEscritos, &ovEscribir))
    {
        if (GetLastError() != ERROR_IO_PENDING)
        {
         // WriteFile failed, but it isn't delayed. Report error and abort.
         //   cout<<"Pendiente env�o";
        }
        else
        {
         // Write is pending.
            if (GetOverlappedResult(hComPort, &ovEscribir, &BytesEscritos, TRUE))
            {
              //  cout<<"Enviado. Bytes Escritos = " << BytesEscritos;

                if((FlagsCom.SyncBill_com())==0x00)
                {
                    FlagsCom.flag_sincronismo_com(0x80);
                   // cout<<"Flag 80"<<(FlagsCom.SyncBill_com())<<endl;
                }
                else
                {
                  //  cout<<"Flag 00"<<(FlagsCom.SyncBill_com())<<endl;
                    FlagsCom.flag_sincronismo_com(0x00);
                }
            }
        }
    }
   else
   {
        // WriteFile completed immediately.

     //   cout << "Enviado Directo"<<endl;
        CloseHandle(ovEscribir.hEvent);
        if(FlagsCom.SyncBill_com()==0x00)
        {
            FlagsCom.flag_sincronismo_com(0x80);
        }
        else if(FlagsCom.SyncBill_com()==0x80)
        {
            FlagsCom.flag_sincronismo_com(0x00);
        }
    }

}

c_flags_NV9 BilletesNV9::EstadoFlags()
{
    return FlagsCom;
}

HANDLE BilletesNV9::GetComPort()
{
    return hComPort;
}



