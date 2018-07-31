#include "ServicioEfectivo/c_lecturabilletethread.h"
//#include "c_efectivothread2.h"

#define STRING_SIZE 200
#define MENSAJEOK 0xf0
#define BILLETEINSERTADO 0xef
#define BILLETEGUARDADO 0xcc
#define BILLETERECHAZADO 0xed
#define CANAL0 0x00
#define BILLETE5 0x01
#define BILLETE10 0x02
#define BILLETE20 0x03


c_LecturaBilleteThread::c_LecturaBilleteThread(QObject *parent)
{

}

void c_LecturaBilleteThread::run()
{

    float ComandoLeido = 0;
    cout<<"Hilo arrancado a tope"<<endl;

    while (true)
    {

        if (hComPort == 0)
        {
           // cout<<"hComPort Hilo Lectura"<< hComPort<<endl;
          //  Sleep(100);

        }
        else
        {
           //  cout<<"hComPort Hilo Lectura"<< hComPort<<endl;
            ComandoLeido = LeerPuertoCom();


            if(ComandoLeido==500||ComandoLeido==1000||ComandoLeido==2000)
            {
               // cout<<"ComandoLeido = "<< ComandoLeido<<" Vamooooooooooooooooooooooooooooosss"<<endl;

                emit ReadBill(ComandoLeido);

            }
          //  Sleep(10);

        }

    }



}


float c_LecturaBilleteThread::InterpretaMensaje(unsigned char MensajeAux[])
{
    int SizeMensaje = MensajeAux[2];

    if (SizeMensaje == 0x03)
    {
       // cout << "Entrado en interpretar mensaje"<<endl;
       // if(MensajeAux[3]==MENSAJEOK && MensajeAux[4]==BILLETEINSERTADO && MensajeAux[5]==CANAL0 && MensajeAux[6]==BILLETEINSERTADO)
        if(MensajeAux[3]==MENSAJEOK && MensajeAux[4]==BILLETEINSERTADO)
        {
         //   cout << "Entrado en selección de billete"<<endl;
          //  printf("Mensaje Aux 4 = %x",MensajeAux[4]);
          //  printf("Mensaje Aux 5 = %x",MensajeAux[5]);
          //  printf("Mensaje Aux 6 = %x",MensajeAux[6]);
            if(MensajeAux[5]==BILLETE5)
            {
              //  cout<< "Billete seleccionado 5"<<endl;
                float aux = 500;
                return aux;
            }
            if(MensajeAux[5]==BILLETE10)
            {
             //   cout<< "Billete seleccionado 10"<<endl;
                float aux = 1000;
                return aux;
                return aux;
            }
            if(MensajeAux[5]==BILLETE20)
            {
              //  cout<< "Billete seleccionado 20"<<endl;
                float aux = 2000;
                return aux;
                return aux;
            }

        }
    }
    else return 0;



}

float c_LecturaBilleteThread::LeerPuertoCom()
{

    TCHAR szBuffer2[STRING_SIZE];

    DWORD ReadBytes;
    OVERLAPPED ovLectura = {0};
    BOOL fWaitingOnRead = FALSE;

    DWORD BytesTranscritos;





    unsigned char CharRecibido;






    ovLectura.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);


    if (ovLectura.hEvent == NULL)
    {
        cout<<"Error de evento";
    }

    if (!fWaitingOnRead)
    {
       // Issue read operation.

    }



do {

    if(!ReadFile(hComPort, &szBuffer2, 1,&ReadBytes, &ovLectura))//else

    {

        if (GetLastError() != ERROR_IO_PENDING)
            {

                    cout<<"Error"<<GetLastError();
            }
            else
        {

            if (GetOverlappedResult(hComPort, &ovLectura, &BytesTranscritos, TRUE))
            {

             //   cout<<"Leido Capullo"<<endl;
                CharRecibido = szBuffer2[0];

                for (int i=0;i<BytesTranscritos;i++)
                    {

                       // cout<<endl<<"Byte1"<< i<<"="<<endl;
                      //  printf("%x", CharRecibido);
                    //	cout<<endl<<"Byte"<< i<<"="<<endl;
                    }

              //  cout<<"Mensaje"<<BytesTranscritos<<endl;
               // printf("%x", szBuffer2[0]);
                if(CharRecibido==0x7F)
                {
                  //  cout << "Cabecera leida locoooo!"<<endl;

                 //   Cabecera = true;
                   // MensajeCompleto = false;
                    BufferAuxiliar[0]=CharRecibido;
                    BytesRecibidos = 1;
                    SizeMensajeAux = 0;

                }
              /*  else if(BytesRecibidos == 0)
                {


                }*/
                else if(BytesRecibidos == 1)
                {
                    BufferAuxiliar[1]=CharRecibido;
                    BytesRecibidos++;

                 /*   cout << "Entrado Byte 2a "<< endl;
                    printf("%x",CharRecibido);*/

                }


                else if(BytesRecibidos == 2)
                {
                    BufferAuxiliar[2]=CharRecibido;
                    BytesRecibidos++;
                    SizeMensajeAux = (int)BufferAuxiliar[2];
                    
                  //  cout << "Entrado Byte 3a "<< endl;
                  //  printf("%x",CharRecibido);
                  //  cout<< "Tamaño Mensaje = "<<SizeMensajeAux<<endl;

                }

                else if (BytesRecibidos>2)
                {
                    BufferAuxiliar[BytesRecibidos] = CharRecibido;
                    BytesRecibidos++;

                   /* cout << "Entrado Byte "<<BytesRecibidos<< endl;
                    printf("%x",CharRecibido);*/

                    if(BytesRecibidos>=(SizeMensajeAux+5))
                    {
                        SizeMensajeAux = 0;

                      //  for (int i=0;i<BytesRecibidos;i++)
                       //     {
                             //   cout<<"Mensaje Completo1!!!"<<endl;
                            //    printf("%x", BufferAuxiliar[i]);
                       //     }

                        BytesRecibidos = 0;
                        //MensajeCompleto = true;
                        if((InterpretaMensaje(BufferAuxiliar))!=0)
                        {
                            float aux;
                            aux = InterpretaMensaje(BufferAuxiliar);
                            memset(BufferAuxiliar,0,STRING_SIZE);
                            if(aux!=0)return aux;
                        }


                    }
                }
                else
                {
                  //  cout<<"BytesRecibidos = "<<BytesRecibidos<<endl;
                }





                ResetEvent(ovLectura.hEvent);
                BytesTranscritos = 0;

            }
            else
            {
             //   cout<<"Lectura"<<endl;

            }
    }

    }
    else
    {

      //  cout<<"LEIDO PAPADELTAAAAAAAAAA!!!";
     //   cout<<"BytesLeídos"<<ReadBytes<<endl;
        CharRecibido = szBuffer2[0];

     //   for (int i=0;i<ReadBytes;i++)
        //    {

           //     cout<<endl<<"Byte2"<< i<<"="<<endl;
           //     printf("%x", CharRecibido);
            //	cout<<endl<<"Byte"<< i<<"="<<endl;
          //  }

      /*  cout<<"Mensaje"<<BytesTranscritos<<endl<<"Byte 1 = ";
        printf("%x", szBuffer2[0]);*/
        if(CharRecibido==0x7F)
        {
         //   cout << "Cabecera leida locoooo!"<<endl;

         //   Cabecera = true;
           // MensajeCompleto = false;
            BufferAuxiliar[0]=CharRecibido;
            BytesRecibidos = 1;
            SizeMensajeAux = 0;

        }
       /* else if(BytesRecibidos == 0)
        {


        }*/
        else if(BytesRecibidos == 1)
        {
            BufferAuxiliar[1]=CharRecibido;
            BytesRecibidos++;
           // cout << "Entrado Byte 2a "<< endl;
           // printf("%x",CharRecibido);

        }


        else if(BytesRecibidos == 2)
        {

            BufferAuxiliar[2]=CharRecibido;
            BytesRecibidos++;
            SizeMensajeAux = (int)BufferAuxiliar[2];
        //    cout << "Entrado Byte 3a "<< endl;
        //    printf("%x",CharRecibido);
         //   cout<< "Tamaño Mensaje = "<<SizeMensajeAux<<endl;

        }

        else if(BytesRecibidos>2)
        {
            BufferAuxiliar[BytesRecibidos] = CharRecibido;

            BytesRecibidos++;

          //  cout << "Entrado Byte "<<BytesRecibidos<< endl << "SizeMensajeAux = "<<SizeMensajeAux<<endl;
          //  printf("%x",CharRecibido);

            if(BytesRecibidos>=(SizeMensajeAux+5))
            {
                SizeMensajeAux = 0;

             //   for (int i=0;i<BytesRecibidos;i++)
                //    {
                  //      cout<<"Mensaje Completo!!!2"<<BytesRecibidos<<endl;
                   //     printf("%x", BufferAuxiliar[i]);
                  //  }

                BytesRecibidos = 0;
                //MensajeCompleto = true;
                if((InterpretaMensaje(BufferAuxiliar))!=0)
                {
                    float aux;
                    aux = InterpretaMensaje(BufferAuxiliar);
                    memset(BufferAuxiliar,0,STRING_SIZE);
                    if(aux!=0)return aux;
                }

            }
        }
        else
        {
            cout<<"BytesRecibidos = "<<BytesRecibidos<<endl;
        }


            ResetEvent(ovLectura.hEvent);

    }
    }
    while(ReadBytes>0);






}
