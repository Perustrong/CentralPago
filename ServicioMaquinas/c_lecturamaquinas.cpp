 #include "ServicioMaquinas/c_lecturamaquinas.h"


#define STRING_SIZE 200
#define MENSAJEOK 0xf0
#define BILLETEINSERTADO 0xef
#define BILLETEGUARDADO 0xcc
#define BILLETERECHAZADO 0xed
#define CANAL0 0x00
#define BILLETE5 0x01
#define BILLETE10 0x02
#define BILLETE20 0x03

c_lecturamaquinas::c_lecturamaquinas(QObject *parent)
{
    qRegisterMetaType<string>("string");


}


void c_lecturamaquinas::run()
{

    float ComandoLeido = 0;
    string strComandoLeido;
    cout<<"Hilo arrancado a tope"<<endl;

    while (true)
    {

        if (hComPort == 0)
        {
            cout<<"hComPort Hilo Lectura"<< hComPort<<endl;
         //   Sleep(100);

        }
        else
        {
             cout<<"hComPort Hilo Lectura"<< hComPort<<endl;
             ComandoLeido = LeerPuertoCom();


            if(ComandoLeido==500||ComandoLeido==1000||ComandoLeido==2000)
            {
               // cout<<"ComandoLeido = "<< ComandoLeido<<" Vamooooooooooooooooooooooooooooosss"<<endl;

               // emit LecturaMaquina(ComandoLeido);

            }
        //    Sleep(1000);

        }

    }



}


void c_lecturamaquinas::InterpretaMensaje(string MensajeAux)
{


    if (MensajeAux[1] == 0x0a)
    {
       if(MensajeAux[7]==0x00)
       {
           EstadoPuerta=false;
           //emit PuertaCerrada();
       }
       else if(MensajeAux[7]==0x01)
       {
           EstadoPuerta=true;

        }
    }




}

float c_lecturamaquinas::LeerPuertoCom()
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

                cout<<"Leido Capullo"<<endl;
                CharRecibido = szBuffer2[0];

                for (int i=0;i<BytesTranscritos;i++)
                    {

                        cout<<endl<<"Byte"<< i<<"="<<endl;
                        printf("%x", CharRecibido);
                        cout<<endl<<"Byte"<< i<<"="<<endl;
                    }

                cout<<"Mensaje"<<BytesTranscritos<<endl;
                printf("%x", szBuffer2[0]);
                if(CharRecibido==0x02 && BytesRecibidos == 0)
                {
                    cout << "Cabecera leida locoooo!"<<endl;

                    //Cabecera = true;
                   // MensajeCompleto = false;
                   // BufferAuxiliar[0]=CharRecibido;
                    BytesRecibidos = 1;
                    SizeMensajeAux = 0;

                }
                else if(BytesRecibidos == 1)
                {
                  //  BufferAuxiliar[0]=CharRecibido;
                    BytesRecibidos++;
                    SizeMensajeAux = ((int)CharRecibido);
                    cout<<"Tamaño Mensaje recibido = "<<SizeMensajeAux<<endl;
                   // cout << "Entrado Byte 2a "<< endl;
                   // printf("%x",CharRecibido);

                }


                else if(BytesRecibidos == 2)
                {

                    BufferAuxiliar[0]=(char)CharRecibido;
                    BytesRecibidos++;
                   // SizeMensajeAux = (int)BufferAuxiliar[2];
                //    cout << "Entrado Byte 3a "<< endl;
                //    printf("%x",CharRecibido);
                 //   cout<< "Tamaño Mensaje = "<<SizeMensajeAux<<endl;

                }
                else if(BytesRecibidos == 3)
                {

                    BufferAuxiliar[1]=CharRecibido;
                    BytesRecibidos++;
                   // SizeMensajeAux = (int)BufferAuxiliar[2];
                //    cout << "Entrado Byte 3a "<< endl;
                //    printf("%x",CharRecibido);
                 //   cout<< "Tamaño Mensaje = "<<SizeMensajeAux<<endl;

                }

                else if(BytesRecibidos == 4)
                {
                    BytesRecibidos++;
                }


                else if(BytesRecibidos>4)
                {

                    BufferAuxiliar[BytesRecibidos-3] = CharRecibido;

                    BytesRecibidos++;

                    cout<< "BytesRecibidos Total = "<<BytesRecibidos<<endl;

                  //  cout << "Entrado Byte "<<BytesRecibidos<< endl << "SizeMensajeAux = "<<SizeMensajeAux<<endl;
                  //  printf("%x",CharRecibido);

                    if(BytesRecibidos>=(SizeMensajeAux+6))
                    {
                        string ResizeBuffer;
                        ResizeBuffer.resize(BytesRecibidos);
                        for(int i = 0; i<BytesRecibidos;i++)
                        {
                            ResizeBuffer[i] = BufferAuxiliar[i];
                        }

                        BufferAuxiliar.resize(BytesRecibidos);
                        for(int i = 0; i<BytesRecibidos;i++)
                        {
                            BufferAuxiliar[i] = ResizeBuffer[i];
                        }
                        SizeMensajeAux = 0;

                        for (int i=0;i<BytesRecibidos;i++)
                            {
                                cout<<"Mensaje Completo!!!2"<<BytesRecibidos<<endl;
                                printf("%x", BufferAuxiliar[i]);
                            }

                        BytesRecibidos = 0;
                    cout<<"Longitud buffer auxiliar dentro del hilo secundario = "<<BufferAuxiliar.length()<<endl;
                    InterpretaMensaje(BufferAuxiliar);
                    //Sleep(2000);
                        emit LecturaMaquina(BufferAuxiliar);

                        cout<<"Emision Realizada"<<endl;
                        //BufferAuxiliar = NULL;
                        //MensajeCompleto = true;
                   /*     if((InterpretaMensaje(BufferAuxiliar))!=0)
                        {
                            float aux;
                            aux = InterpretaMensaje(BufferAuxiliar);
                            memset(BufferAuxiliar,0,STRING_SIZE);
                            if(aux!=0)return aux;
                        }*/

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


    }
    else
    {

        cout<<"LEIDO PAPADELTAAAAAAAAAA!!!";
        cout<<"BytesLeídos"<<ReadBytes<<endl;
        CharRecibido = szBuffer2[0];

        for (int i=0;i<ReadBytes;i++)
            {

                cout<<endl<<"Byte2"<< i<<"="<<endl;
                printf("%x", CharRecibido);
                cout<<endl<<"Byte"<< i<<"="<<endl;
            }

      /*  cout<<"Mensaje"<<BytesTranscritos<<endl<<"Byte 1 = ";
        printf("%x", szBuffer2[0]);*/
      /*  if(CharRecibido==0x7F)
        {
         //   cout << "Cabecera leida locoooo!"<<endl;

         //   Cabecera = true;
           // MensajeCompleto = false;
            BufferAuxiliar[0]=CharRecibido;
            BytesRecibidos = 1;
            SizeMensajeAux = 0;

        }*/
       /* else if(BytesRecibidos == 0)
        {


        }*/
  //  do
   // {
        if(BytesRecibidos == 1)
        {
          //  BufferAuxiliar[0]=CharRecibido;
            BytesRecibidos++;
            SizeMensajeAux = ((int)CharRecibido);
            cout<<"Tamaño Mensaje recibido = "<<SizeMensajeAux<<endl;
           // cout << "Entrado Byte 2a "<< endl;
           // printf("%x",CharRecibido);

        }


        else if(BytesRecibidos == 2)
        {

            BufferAuxiliar[0]=CharRecibido;
            BytesRecibidos++;
           // SizeMensajeAux = (int)BufferAuxiliar[2];
        //    cout << "Entrado Byte 3a "<< endl;
        //    printf("%x",CharRecibido);
         //   cout<< "Tamaño Mensaje = "<<SizeMensajeAux<<endl;

        }
        else if(BytesRecibidos == 3)
        {

            BufferAuxiliar[1]=CharRecibido;
            BytesRecibidos++;
           // SizeMensajeAux = (int)BufferAuxiliar[2];
        //    cout << "Entrado Byte 3a "<< endl;
        //    printf("%x",CharRecibido);
         //   cout<< "Tamaño Mensaje = "<<SizeMensajeAux<<endl;

        }
        else if(BytesRecibidos == 4)
        {
            BytesRecibidos++;
        }


        else if(BytesRecibidos>4)
        {

            BufferAuxiliar[BytesRecibidos-3] = CharRecibido;

            BytesRecibidos++;
            cout<< "BytesRecibidos Total = "<<BytesRecibidos<<endl;
          //  cout << "Entrado Byte "<<BytesRecibidos<< endl << "SizeMensajeAux = "<<SizeMensajeAux<<endl;
          //  printf("%x",CharRecibido);

            if(BytesRecibidos>=(SizeMensajeAux+6))
            {
                string ResizeBuffer;
                ResizeBuffer.resize(BytesRecibidos);
                for(int i = 0; i<BytesRecibidos;i++)
                {
                    ResizeBuffer[i] = BufferAuxiliar[i];
                }

                BufferAuxiliar.resize(BytesRecibidos);
                for(int i = 0; i<BytesRecibidos;i++)
                {
                    BufferAuxiliar[i] = ResizeBuffer[i];
                }
                SizeMensajeAux = 0;
                for (int i=0;i<BytesRecibidos;i++)
                    {
                        cout<<"Mensaje Completo!!!2"<<BytesRecibidos<<endl;
                        printf("%x", BufferAuxiliar[i]);
                    }

                BytesRecibidos = 0;

                cout<<"Longitud buffer auxiliar dentro del hilo secundario = "<<BufferAuxiliar.length()<<endl;
                InterpretaMensaje(BufferAuxiliar);
                //Sleep(2000);
                emit LecturaMaquina(BufferAuxiliar);

                cout<<"Emision Realizada"<<endl;
                //BufferAuxiliar = NULL;
                //MensajeCompleto = true;
           /*     if((InterpretaMensaje(BufferAuxiliar))!=0)
                {
                    float aux;
                    aux = InterpretaMensaje(BufferAuxiliar);
                    memset(BufferAuxiliar,0,STRING_SIZE);
                    if(aux!=0)return aux;
                }*/

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

void c_lecturamaquinas::onActualizacionHandle(HANDLE NewhComPort)
{
    hComPort = NewhComPort;
    cout<<"Nuevo hcomport lectura = "<<hComPort<<endl;

}


