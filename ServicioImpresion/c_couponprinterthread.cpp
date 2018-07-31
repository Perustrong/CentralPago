#include "ServicioImpresion/c_couponprinterthread.h"

c_CouponPrinterThread::c_CouponPrinterThread(QObject *parent)
{
    cout << "Hilo de impresora encendido. Estado de ActiveThread = "<<ActiveThread<<endl;

  //  connect(,SIGNAL(PrinterFunction(string)),this,SLOT(onPrinterFunction(string)));

    commandStructure.BaudRate = 9600;
    commandStructure.Timeout = 1000;
    commandStructure.RetryLevel = 1;
    commandStructure.IgnoreError = 1;
    commandStructure.PortNumber = 9;
    commandStructure.SSPAddress = 65;
    Impresora.SetOutputStream(&cout);


}



void c_CouponPrinterThread::run()
{
    while(ActiveThread == true)
    {
        //cout<<"Run"<<endl;
        if(ActiveThread == false) cout<<"Hilo Impresora Desactivado";
        Sleep(300);
    }

}

void c_CouponPrinterThread::onPrinterFunction(string Auxfunction)
{
    string function = Auxfunction;
    int ProtocolVersion = 7;
    int Intentos = 5;

    cout <<"Impresora "<<&Impresora<<endl;

    cout<<"Entrado en onPrinterFunction del Hilo"<<endl;
    cout<<"La función es: "<<function<<endl;
    //emit EventoImpresora(3);


    bool printconnect = Impresora.SyncPrinter();

    if(printconnect == false)
    {
        printconnect = Impresora.ConnectToPrinter(commandStructure,ProtocolVersion,Intentos);

        if(printconnect == false) cout<<"Imposible conectar con impresora"<<endl;
        else
        {
            printconnect = Impresora.SyncPrinter();
            if(printconnect == true)
            {
                cout<< "Impresora conectada"<<endl;
            }
            else cout<<"Imposible conectar y sincronizar con impresora"<<endl;
        }
    }



    if(function[0]=='A')
    {
        if(function[1]=='L')
        {
            if(function[2]=='I'&&function[3]=='N'&&function[4]=='I')
            {


            if(printconnect == false)
            {
                printconnect = Impresora.ConnectToPrinter(commandStructure,ProtocolVersion,Intentos);

                if(printconnect == false) cout<<"Imposible conectar con impresora"<<endl;
                else
                {
                    printconnect = Impresora.SyncPrinter();
                    if(printconnect == true)
                    {
                        cout <<"Impresora conectada y sincronizada INI COMANDO1"<<endl;
                        unsigned char PositionX1[2]={0x30,0x01};
                        unsigned char PositionY1[2]={0x36,0x01};
                        unsigned char PositionX2[2]={0x56,0x01};
                        unsigned char PositionY2[2]={0x43,0x01};

                        unsigned char Mensaje1[] ="GENUIX AUDIO S.L.";
                        unsigned char Mensaje2[] ="MODELO EN PRUEBAS";


                        int SizeMensaje1 = sizeof(Mensaje1);
                        int SizeMensaje2 = sizeof(Mensaje2);


                        //Impresora.ClearTemplatePrinter(0xfe);
                        Impresora.AddLinePrinter(PositionX1,PositionY1,Mensaje1,SizeMensaje1);
                        Impresora.AddLinePrinter(PositionX2,PositionY2,Mensaje2,SizeMensaje2);




                    }
                    else cout<<"Impresora no sincronizada"<<endl;

                }

            }
            else
            {
                printconnect = Impresora.SyncPrinter();
                if(printconnect == true)
                {
                    cout <<"Impresora conectada y sincronizada INI COMANDO2"<<endl;
                    unsigned char PositionX1[2]={0x30,0x01};
                    unsigned char PositionY1[2]={0x36,0x01};
                    unsigned char PositionX2[2]={0x56,0x01};
                    unsigned char PositionY2[2]={0x43,0x01};

                    unsigned char Mensaje1[] ="GENUIX AUDIO S.L.";
                    unsigned char Mensaje2[] ="MODELO EN PRUEBAS";

                    int SizeMensaje1 = sizeof(Mensaje1);
                    int SizeMensaje2 = sizeof(Mensaje2);

                    Impresora.AddLinePrinter(PositionX1,PositionY1,Mensaje1,SizeMensaje1);
                    Impresora.AddLinePrinter(PositionX2,PositionY2,Mensaje2,SizeMensaje2);






                }
                else cout<<"Impresora no sincronizada"<<endl;

            }
            }
            else if(function[2]=='L')
            {
                switch (function[3])
                {
                case '1':

                    if(printconnect == false)
                    {
                        printconnect = Impresora.ConnectToPrinter(commandStructure,ProtocolVersion,Intentos);

                        if(printconnect == false) cout<<"Imposible conectar con impresora"<<endl;
                        else
                        {
                            printconnect = Impresora.SyncPrinter();
                            if(printconnect == true)
                            {
                                cout <<"Impresora conectada y sincronizada LAVADORA 1 COMANDO1"<<endl;

                                unsigned char PositionX3[2]={0x88,0x01};
                                unsigned char PositionY3[2]={0x6E,0x01};
                                unsigned char Mensaje3[] ="LAVADORA1";
                                int SizeMensaje3 = sizeof(Mensaje3);
                                Impresora.AddLinePrinter(PositionX3,PositionY3,Mensaje3,SizeMensaje3);


                            }
                            else cout<<"Impresora no sincronizada"<<endl;

                        }

                    }
                    else
                    {
                        printconnect = Impresora.SyncPrinter();
                        if(printconnect == true)
                        {
                            cout <<"Impresora conectada y sincronizada  LAVADORA 1 COMANDO2"<<endl;

                            unsigned char PositionX3[2]={0x88,0x01};
                            unsigned char PositionY3[2]={0x6E,0x01};
                            unsigned char Mensaje3[] ="LAVADORA1";
                            int SizeMensaje3 = sizeof(Mensaje3);
                            Impresora.AddLinePrinter(PositionX3,PositionY3,Mensaje3,SizeMensaje3);


                        }
                        else cout<<"Impresora no sincronizada"<<endl;

                    }


                break;
                case '2':

                    if(printconnect == false)
                    {
                        printconnect = Impresora.ConnectToPrinter(commandStructure,ProtocolVersion,Intentos);

                        if(printconnect == false) cout<<"Imposible conectar con impresora  LAVADORA 2 COMANDO1"<<endl;
                        else
                        {
                            printconnect = Impresora.SyncPrinter();
                            if(printconnect == true)
                            {
                                cout <<"Impresora conectada y sincronizada"<<endl;

                                unsigned char PositionX3[2]={0x88,0x01};
                                unsigned char PositionY3[2]={0x6E,0x01};
                                unsigned char Mensaje3[] ="LAVADORA2";
                                int SizeMensaje3 = sizeof(Mensaje3);
                                Impresora.AddLinePrinter(PositionX3,PositionY3,Mensaje3,SizeMensaje3);


                            }
                            else cout<<"Impresora no sincronizada"<<endl;

                        }

                    }
                    else
                    {
                        printconnect = Impresora.SyncPrinter();
                        if(printconnect == true)
                        {
                            cout <<"Impresora conectada y sincronizada  LAVADORA 2 COMANDO2"<<endl;

                            unsigned char PositionX3[2]={0x88,0x01};
                            unsigned char PositionY3[2]={0x6E,0x01};
                            unsigned char Mensaje3[] ="LAVADORA2";
                            int SizeMensaje3 = sizeof(Mensaje3);
                            Impresora.AddLinePrinter(PositionX3,PositionY3,Mensaje3,SizeMensaje3);


                        }
                        else cout<<"Impresora no sincronizada"<<endl;
                    }



                break;
                case '3':

                    if(printconnect == false)
                    {
                        printconnect = Impresora.ConnectToPrinter(commandStructure,ProtocolVersion,Intentos);

                        if(printconnect == false) cout<<"Imposible conectar con impresora"<<endl;
                        else
                        {
                            printconnect = Impresora.SyncPrinter();
                            if(printconnect == true)
                            {
                                cout <<"Impresora conectada y sincronizada  LAVADORA 3 COMANDO1"<<endl;

                                unsigned char PositionX3[2]={0x88,0x01};
                                unsigned char PositionY3[2]={0x6E,0x01};
                                unsigned char Mensaje3[] ="LAVADORA3";
                                int SizeMensaje3 = sizeof(Mensaje3);
                                Impresora.AddLinePrinter(PositionX3,PositionY3,Mensaje3,SizeMensaje3);


                            }
                            else cout<<"Impresora no sincronizada"<<endl;

                        }

                    }
                    else
                    {
                        printconnect = Impresora.SyncPrinter();
                        if(printconnect == true)
                        {
                            cout <<"Impresora conectada y sincronizada  LAVADORA 3 COMANDO2"<<endl;

                            unsigned char PositionX3[2]={0x88,0x01};
                            unsigned char PositionY3[2]={0x6E,0x01};
                            unsigned char Mensaje3[] ="LAVADORA3";
                            int SizeMensaje3 = sizeof(Mensaje3);
                            Impresora.AddLinePrinter(PositionX3,PositionY3,Mensaje3,SizeMensaje3);


                        }
                        else cout<<"Impresora no sincronizada"<<endl;
                       }



                break;

                case '4':

                    if(printconnect == false)
                    {
                        printconnect = Impresora.ConnectToPrinter(commandStructure,ProtocolVersion,Intentos);

                        if(printconnect == false) cout<<"Imposible conectar con impresora LAVADORA 4 COMANDO1"<<endl;
                        else
                        {
                            printconnect = Impresora.SyncPrinter();
                            if(printconnect == true)
                            {
                                cout <<"Impresora conectada y sincronizada"<<endl;

                                unsigned char PositionX3[2]={0x88,0x01};
                                unsigned char PositionY3[2]={0x6E,0x01};
                                unsigned char Mensaje3[] ="LAVADORA4";
                                int SizeMensaje3 = sizeof(Mensaje3);
                                Impresora.AddLinePrinter(PositionX3,PositionY3,Mensaje3,SizeMensaje3);


                            }
                            else cout<<"Impresora no sincronizada"<<endl;

                        }

                    }
                    else
                    {
                        printconnect = Impresora.SyncPrinter();
                        if(printconnect == true)
                        {
                            cout <<"Impresora conectada y sincronizada  LAVADORA 4 COMANDO2"<<endl;

                            unsigned char PositionX3[2]={0x88,0x01};
                            unsigned char PositionY3[2]={0x6E,0x01};
                            unsigned char Mensaje3[] ="LAVADORA4";
                            int SizeMensaje3 = sizeof(Mensaje3);
                            Impresora.AddLinePrinter(PositionX3,PositionY3,Mensaje3,SizeMensaje3);


                        }
                        else cout<<"Impresora no sincronizada"<<endl;
                    }


                break;
                case '5':

                    if(printconnect == false)
                    {
                        printconnect = Impresora.ConnectToPrinter(commandStructure,ProtocolVersion,Intentos);

                        if(printconnect == false) cout<<"Imposible conectar con impresora"<<endl;
                        else
                        {
                            printconnect = Impresora.SyncPrinter();
                            if(printconnect == true)
                            {
                                cout <<"Impresora conectada y sincronizada  LAVADORA 5 COMANDO1"<<endl;

                                unsigned char PositionX3[2]={0x88,0x01};
                                unsigned char PositionY3[2]={0x6E,0x01};
                                unsigned char Mensaje3[] ="LAVADORA5";
                                int SizeMensaje3 = sizeof(Mensaje3);
                                Impresora.AddLinePrinter(PositionX3,PositionY3,Mensaje3,SizeMensaje3);


                            }
                            else cout<<"Impresora no sincronizada"<<endl;

                        }

                    }
                    else
                    {
                        printconnect = Impresora.SyncPrinter();
                        if(printconnect == true)
                        {
                            cout <<"Impresora conectada y sincronizada  LAVADORA 5 COMANDO2"<<endl;

                            unsigned char PositionX3[2]={0x88,0x01};
                            unsigned char PositionY3[2]={0x6E,0x01};
                            unsigned char Mensaje3[] ="LAVADORA5";
                            int SizeMensaje3 = sizeof(Mensaje3);
                            Impresora.AddLinePrinter(PositionX3,PositionY3,Mensaje3,SizeMensaje3);


                        }
                        else cout<<"Impresora no sincronizada"<<endl;
                        }



                break;

                case '6':

                    if(printconnect == false)
                    {
                        printconnect = Impresora.ConnectToPrinter(commandStructure,ProtocolVersion,Intentos);

                        if(printconnect == false) cout<<"Imposible conectar con impresora"<<endl;
                        else
                        {
                            printconnect = Impresora.SyncPrinter();
                            if(printconnect == true)
                            {
                                cout <<"Impresora conectada y sincronizada  LAVADORA 6 COMANDO1"<<endl;

                                unsigned char PositionX3[2]={0x88,0x01};
                                unsigned char PositionY3[2]={0x6E,0x01};
                                unsigned char Mensaje3[] ="LAVADORA6";
                                int SizeMensaje3 = sizeof(Mensaje3);
                                Impresora.AddLinePrinter(PositionX3,PositionY3,Mensaje3,SizeMensaje3);


                            }
                            else cout<<"Impresora no sincronizada"<<endl;

                        }

                    }
                    else
                    {
                        printconnect = Impresora.SyncPrinter();
                        if(printconnect == true)
                        {
                            cout <<"Impresora conectada y sincronizada  LAVADORA 6 COMANDO2"<<endl;

                            unsigned char PositionX3[2]={0x88,0x01};
                            unsigned char PositionY3[2]={0x6E,0x01};
                            unsigned char Mensaje3[] ="LAVADORA6";
                            int SizeMensaje3 = sizeof(Mensaje3);
                            Impresora.AddLinePrinter(PositionX3,PositionY3,Mensaje3,SizeMensaje3);


                        }
                        else cout<<"Impresora no sincronizada"<<endl;
                    }

                break;

                default:
                break;
                }


            }




            else if(function[2]=='E')
            {


                if(printconnect == false)
                {
                    printconnect = Impresora.ConnectToPrinter(commandStructure,ProtocolVersion,Intentos);

                    if(printconnect == false) cout<<"Imposible conectar con impresora"<<endl;
                    else
                    {
                        printconnect = Impresora.SyncPrinter();
                        if(printconnect == true)
                        {
                            cout <<"Impresora conectada y sincronizada  EXTRA COMANDO1"<<endl;
                            unsigned char PositionX1[2]={0xB8,0x01};
                            unsigned char PositionX2[2]={0xE8,0x01};
                            unsigned char PositionX3[2]={0x18,0x02};
                            unsigned char PositionY[2]={0x6E,0x01};
                            unsigned char Mensaje1[] ="EXTRA 1";
                            unsigned char Mensaje2[] ="EXTRA 2";
                            unsigned char Mensaje3[] ="EXTRA 3";
                            unsigned char Mensaje4[] = "Sin Extras";
                            int SizeMensaje1 = sizeof(Mensaje1);
                            int SizeMensaje2 = sizeof(Mensaje2);
                            int SizeMensaje3 = sizeof(Mensaje3);
                            int SizeMensaje4 = sizeof(Mensaje4);

                            switch (function[3]) {
                            case '0':

                                Impresora.AddLinePrinter(PositionX1,PositionY,Mensaje4,SizeMensaje4);

                                break;
                            case '1':

                                Impresora.AddLinePrinter(PositionX1,PositionY,Mensaje1,SizeMensaje1);
                                break;
                            case '2':

                                Impresora.AddLinePrinter(PositionX1,PositionY,Mensaje2,SizeMensaje2);
                                break;
                            case '3':

                                Impresora.AddLinePrinter(PositionX1,PositionY,Mensaje3,SizeMensaje3);
                                break;
                            case '4':

                                Impresora.AddLinePrinter(PositionX1,PositionY,Mensaje1,SizeMensaje1);
                                Impresora.AddLinePrinter(PositionX2,PositionY,Mensaje2,SizeMensaje2);
                                break;
                            case '5':

                                Impresora.AddLinePrinter(PositionX1,PositionY,Mensaje1,SizeMensaje1);
                                Impresora.AddLinePrinter(PositionX2,PositionY,Mensaje3,SizeMensaje3);
                                break;
                            case '6':

                                Impresora.AddLinePrinter(PositionX1,PositionY,Mensaje2,SizeMensaje2);
                                Impresora.AddLinePrinter(PositionX2,PositionY,Mensaje3,SizeMensaje3);
                                break;
                            case '7':

                                Impresora.AddLinePrinter(PositionX1,PositionY,Mensaje1,SizeMensaje1);
                                Impresora.AddLinePrinter(PositionX2,PositionY,Mensaje2,SizeMensaje2);
                                Impresora.AddLinePrinter(PositionX3,PositionY,Mensaje3,SizeMensaje3);
                                break;
                            default:
                                break;


                            }
                        }
                        else cout<<"Impresora no sincronizada"<<endl;

                    }

                }
                else
                {
                    printconnect = Impresora.SyncPrinter();
                    if(printconnect == true)
                    {
                        cout <<"Impresora conectada y sincronizada EXTRA COMANDO1"<<endl;
                        unsigned char PositionX1[2]={0xB8,0x01};
                        unsigned char PositionX2[2]={0xE8,0x01};
                        unsigned char PositionX3[2]={0x18,0x02};
                        unsigned char PositionY[2]={0x6E,0x01};
                        unsigned char Mensaje1[] ="EXTRA 1";
                        unsigned char Mensaje2[] ="EXTRA 2";
                        unsigned char Mensaje3[] ="EXTRA 3";
                        unsigned char Mensaje4[] = "Sin Extras";
                        int SizeMensaje1 = sizeof(Mensaje1);
                        int SizeMensaje2 = sizeof(Mensaje2);
                        int SizeMensaje3 = sizeof(Mensaje3);
                        int SizeMensaje4 = sizeof(Mensaje4);

                        switch (function[3]) {
                        case '0':

                            Impresora.AddLinePrinter(PositionX1,PositionY,Mensaje4,SizeMensaje4);

                            break;
                        case '1':

                            Impresora.AddLinePrinter(PositionX1,PositionY,Mensaje1,SizeMensaje1);
                            break;
                        case '2':

                            Impresora.AddLinePrinter(PositionX1,PositionY,Mensaje2,SizeMensaje2);
                            break;
                        case '3':

                            Impresora.AddLinePrinter(PositionX1,PositionY,Mensaje3,SizeMensaje3);
                            break;
                        case '4':

                            Impresora.AddLinePrinter(PositionX1,PositionY,Mensaje1,SizeMensaje1);
                            Impresora.AddLinePrinter(PositionX2,PositionY,Mensaje2,SizeMensaje2);
                            break;
                        case '5':

                            Impresora.AddLinePrinter(PositionX1,PositionY,Mensaje1,SizeMensaje1);
                            Impresora.AddLinePrinter(PositionX2,PositionY,Mensaje3,SizeMensaje3);
                            break;
                        case '6':

                            Impresora.AddLinePrinter(PositionX1,PositionY,Mensaje2,SizeMensaje2);
                            Impresora.AddLinePrinter(PositionX2,PositionY,Mensaje3,SizeMensaje3);
                            break;
                        case '7':

                            Impresora.AddLinePrinter(PositionX1,PositionY,Mensaje1,SizeMensaje1);
                            Impresora.AddLinePrinter(PositionX2,PositionY,Mensaje2,SizeMensaje2);
                            Impresora.AddLinePrinter(PositionX3,PositionY,Mensaje3,SizeMensaje3);
                            break;
                        default:
                            break;



                        }
                    }
                    else cout<<"Impresora no sincronizada"<<endl;

                }
            }

            else if(function[2]=='S')
            {
                switch (function[3])
                {
                case '1':

                    if(printconnect == false)
                    {
                        printconnect = Impresora.ConnectToPrinter(commandStructure,ProtocolVersion,Intentos);

                        if(printconnect == false) cout<<"Imposible conectar con impresora"<<endl;
                        else
                        {
                            printconnect = Impresora.SyncPrinter();
                            if(printconnect == true)
                            {
                                cout <<"Impresora conectada y sincronizada SECADORA 1 COMANDO1"<<endl;

                                unsigned char PositionX3[2]={0x88,0x01};
                                unsigned char PositionY3[2]={0x6E,0x01};
                                unsigned char Mensaje3[] ="SECADORA1";
                                int SizeMensaje3 = sizeof(Mensaje3);
                                Impresora.AddLinePrinter(PositionX3,PositionY3,Mensaje3,SizeMensaje3);


                            }
                            else cout<<"Impresora no sincronizada"<<endl;

                        }

                    }
                    else
                    {
                        printconnect = Impresora.SyncPrinter();
                        if(printconnect == true)
                        {
                            cout <<"Impresora conectada y sincronizada SECADORA 1 COMANDO2 "<<endl;

                            unsigned char PositionX3[2]={0x88,0x01};
                            unsigned char PositionY3[2]={0x6E,0x01};
                            unsigned char Mensaje3[] ="SECADORA1";
                            int SizeMensaje3 = sizeof(Mensaje3);
                            Impresora.AddLinePrinter(PositionX3,PositionY3,Mensaje3,SizeMensaje3);


                        }
                        else cout<<"Impresora no sincronizada"<<endl;

                    }


                break;
                case '2':

                    if(printconnect == false)
                    {
                        printconnect = Impresora.ConnectToPrinter(commandStructure,ProtocolVersion,Intentos);

                        if(printconnect == false) cout<<"Imposible conectar con impresora SECADORA 2 COMANDO1"<<endl;
                        else
                        {
                            printconnect = Impresora.SyncPrinter();
                            if(printconnect == true)
                            {
                                cout <<"Impresora conectada y sincronizada"<<endl;

                                unsigned char PositionX3[2]={0x88,0x01};
                                unsigned char PositionY3[2]={0x6E,0x01};
                                unsigned char Mensaje3[] ="SECADORA2";
                                int SizeMensaje3 = sizeof(Mensaje3);
                                Impresora.AddLinePrinter(PositionX3,PositionY3,Mensaje3,SizeMensaje3);


                            }
                            else cout<<"Impresora no sincronizada"<<endl;

                        }

                    }
                    else
                    {
                        printconnect = Impresora.SyncPrinter();
                        if(printconnect == true)
                        {
                            cout <<"Impresora conectada y sincronizada  SECADORA 2 COMANDO2"<<endl;

                            unsigned char PositionX3[2]={0x88,0x01};
                            unsigned char PositionY3[2]={0x6E,0x01};
                            unsigned char Mensaje3[] ="SECADORA2";
                            int SizeMensaje3 = sizeof(Mensaje3);
                            Impresora.AddLinePrinter(PositionX3,PositionY3,Mensaje3,SizeMensaje3);


                        }
                        else cout<<"Impresora no sincronizada"<<endl;
                    }



                break;
                case '3':

                    if(printconnect == false)
                    {
                        printconnect = Impresora.ConnectToPrinter(commandStructure,ProtocolVersion,Intentos);

                        if(printconnect == false) cout<<"Imposible conectar con impresora"<<endl;
                        else
                        {
                            printconnect = Impresora.SyncPrinter();
                            if(printconnect == true)
                            {
                                cout <<"Impresora conectada y sincronizada  SECADORA 3 COMANDO1"<<endl;

                                unsigned char PositionX3[2]={0x88,0x01};
                                unsigned char PositionY3[2]={0x6E,0x01};
                                unsigned char Mensaje3[] ="SECADORA3";
                                int SizeMensaje3 = sizeof(Mensaje3);
                                Impresora.AddLinePrinter(PositionX3,PositionY3,Mensaje3,SizeMensaje3);


                            }
                            else cout<<"Impresora no sincronizada"<<endl;

                        }

                    }
                    else
                    {
                        printconnect = Impresora.SyncPrinter();
                        if(printconnect == true)
                        {
                            cout <<"Impresora conectada y sincronizada  SECADORA 3 COMANDO2"<<endl;

                            unsigned char PositionX3[2]={0x88,0x01};
                            unsigned char PositionY3[2]={0x6E,0x01};
                            unsigned char Mensaje3[] ="SECADORA3";
                            int SizeMensaje3 = sizeof(Mensaje3);
                            Impresora.AddLinePrinter(PositionX3,PositionY3,Mensaje3,SizeMensaje3);


                        }
                        else cout<<"Impresora no sincronizada"<<endl;
                       }



                break;

                case '4':

                    if(printconnect == false)
                    {
                        printconnect = Impresora.ConnectToPrinter(commandStructure,ProtocolVersion,Intentos);

                        if(printconnect == false) cout<<"Imposible conectar con impresora"<<endl;
                        else
                        {
                            printconnect = Impresora.SyncPrinter();
                            if(printconnect == true)
                            {
                                cout <<"Impresora conectada y sincronizadaSECADORA 4 COMANDO1"<<endl;

                                unsigned char PositionX3[2]={0x88,0x01};
                                unsigned char PositionY3[2]={0x6E,0x01};
                                unsigned char Mensaje3[] ="SECADORA4";
                                int SizeMensaje3 = sizeof(Mensaje3);
                                Impresora.AddLinePrinter(PositionX3,PositionY3,Mensaje3,SizeMensaje3);


                            }
                            else cout<<"Impresora no sincronizada"<<endl;

                        }

                    }
                    else
                    {
                        printconnect = Impresora.SyncPrinter();
                        if(printconnect == true)
                        {
                            cout <<"Impresora conectada y sincronizada  SECADORA 4 COMANDO2"<<endl;

                            unsigned char PositionX3[2]={0x88,0x01};
                            unsigned char PositionY3[2]={0x6E,0x01};
                            unsigned char Mensaje3[] ="SECADORA4";
                            int SizeMensaje3 = sizeof(Mensaje3);
                            Impresora.AddLinePrinter(PositionX3,PositionY3,Mensaje3,SizeMensaje3);


                        }
                        else cout<<"Impresora no sincronizada"<<endl;
                    }


                break;
                case '5':

                    if(printconnect == false)
                    {
                        printconnect = Impresora.ConnectToPrinter(commandStructure,ProtocolVersion,Intentos);

                        if(printconnect == false) cout<<"Imposible conectar con impresora"<<endl;
                        else
                        {
                            printconnect = Impresora.SyncPrinter();
                            if(printconnect == true)
                            {
                                cout <<"Impresora conectada y sincronizada  SECADORA 5 COMANDO1"<<endl;

                                unsigned char PositionX3[2]={0x88,0x01};
                                unsigned char PositionY3[2]={0x6E,0x01};
                                unsigned char Mensaje3[] ="SECADORA5";
                                int SizeMensaje3 = sizeof(Mensaje3);
                                Impresora.AddLinePrinter(PositionX3,PositionY3,Mensaje3,SizeMensaje3);


                            }
                            else cout<<"Impresora no sincronizada"<<endl;

                        }

                    }
                    else
                    {
                        printconnect = Impresora.SyncPrinter();
                        if(printconnect == true)
                        {
                            cout <<"Impresora conectada y sincronizada  SECADORA 5 COMANDO2"<<endl;

                            unsigned char PositionX3[2]={0x88,0x01};
                            unsigned char PositionY3[2]={0x6E,0x01};
                            unsigned char Mensaje3[] ="SECADORA5";
                            int SizeMensaje3 = sizeof(Mensaje3);
                            Impresora.AddLinePrinter(PositionX3,PositionY3,Mensaje3,SizeMensaje3);


                        }
                        else cout<<"Impresora no sincronizada"<<endl;



                break;

                case '6':

                    if(printconnect == false)
                    {
                        printconnect = Impresora.ConnectToPrinter(commandStructure,ProtocolVersion,Intentos);

                        if(printconnect == false) cout<<"Imposible conectar con impresora"<<endl;
                        else
                        {
                            printconnect = Impresora.SyncPrinter();
                            if(printconnect == true)
                            {
                                cout <<"Impresora conectada y sincronizada  SECADORA 6 COMANDO1"<<endl;

                                unsigned char PositionX3[2]={0x88,0x01};
                                unsigned char PositionY3[2]={0x6E,0x01};
                                unsigned char Mensaje3[] ="SECADORA6";
                                int SizeMensaje3 = sizeof(Mensaje3);
                                Impresora.AddLinePrinter(PositionX3,PositionY3,Mensaje3,SizeMensaje3);


                            }
                            else cout<<"Impresora no sincronizada"<<endl;

                        }

                    }
                    else
                    {
                        printconnect = Impresora.SyncPrinter();
                        if(printconnect == true)
                        {
                            cout <<"Impresora conectada y sincronizada  SECADORA 6 COMANDO2"<<endl;

                            unsigned char PositionX3[2]={0x88,0x01};
                            unsigned char PositionY3[2]={0x6E,0x01};
                            unsigned char Mensaje3[] ="SECADORA6";
                            int SizeMensaje3 = sizeof(Mensaje3);
                            Impresora.AddLinePrinter(PositionX3,PositionY3,Mensaje3,SizeMensaje3);


                        }
                        else cout<<"Impresora no sincronizada"<<endl;

                break;

                default:
                break;
                }


                }

            }
        }
        }
        else if(function[1]=='I')
        {

            if(printconnect == false)
            {

                printconnect = Impresora.ConnectToPrinter(commandStructure,ProtocolVersion,Intentos);

                if(printconnect == false) cout<<"Imposible conectar con impresora"<<endl;
                else
                {
                    printconnect = Impresora.SyncPrinter();
                    if(printconnect == true)
                    {
                        cout <<"Impresora conectada y sincronizada IMAGEN COMANDO1"<<endl;


                        unsigned char PositionXIm[2]={0x08,0x00};
                        unsigned char PositionYIm[2]={0x04,0x00};



                        Impresora.AddImagePrinter(PositionXIm,PositionYIm,0x01);



                    }
                    else cout<<"Impresora no sincronizada"<<endl;

                }

            }
            else
            {
                printconnect = Impresora.SyncPrinter();
                if(printconnect == true)
                {
                    cout <<"Impresora conectada y sincronizada   IMAGEN COMANDO2"<<endl;


                    unsigned char PositionXIm[2]={0x08,0x00};
                    unsigned char PositionYIm[2]={0x04,0x00};


                    Impresora.AddImagePrinter(PositionXIm,PositionYIm,0x01);

                }
                else cout<<"Impresora no sincronizada"<<endl;

            }

        }



    }
    else if(function[0]=='P'&&function[1]=='R')
    {

        if(printconnect == false)
        {
            printconnect = Impresora.ConnectToPrinter(commandStructure,ProtocolVersion,Intentos);

            if(printconnect == false) cout<<"Imposible conectar con impresora"<<endl;
            else
            {
                printconnect = Impresora.SyncPrinter();
                if(printconnect == true)
                {
                    printconnect = Impresora.SyncPrinter();
                    if(printconnect == true)
                    {
                        cout <<"Impresora conectada y sincronizada   PRINT COMANDO1"<<endl;

                        Impresora.EnablePrinter();
                        Impresora.TicketPrint(0xfe);
                        Impresora.ClearFilePrinter(0xfe);
                    }


                }
                else cout<<"Impresora no sincronizada"<<endl;

            }

        }
        else
        {
            printconnect = Impresora.SyncPrinter();
            if(printconnect == true)
            {
                printconnect = Impresora.SyncPrinter();
                if(printconnect == true)
                {
                    bool Printed = false;

                    cout <<"Impresora conectada y sincronizada   PRINT COMANDO2"<<endl;

                    Impresora.EnablePrinter();
                    Sleep(1000);
                    Printed = Impresora.TicketPrint(0xfe);
                    Sleep(1000);
                   // Impresora.DoPoll();
                    if(Printed == true)
                    {
                        Impresora.ClearFilePrinter(0xfe);
                    }
                }


            }
            else cout<<"Impresora no sincronizada"<<endl;

        }

    }
    else if(function[0]=='C'&&function[1]=='L')
    {

        if(printconnect == false)
        {
            printconnect = Impresora.ConnectToPrinter(commandStructure,ProtocolVersion,Intentos);

            if(printconnect == false) cout<<"Imposible conectar con impresora"<<endl;
            else
            {
                printconnect = Impresora.SyncPrinter();
                if(printconnect == true)
                {
                    printconnect = Impresora.SyncPrinter();
                    if(printconnect == true)
                    {

                        cout <<"Impresora conectada y sincronizada   CLEAR COMANDO1"<<endl;

                        Impresora.ClearFilePrinter(0xfe);
                    }


                }
                else cout<<"Impresora no sincronizada"<<endl;

            }

        }
        else
        {
            printconnect = Impresora.SyncPrinter();
            if(printconnect == true)
            {
                printconnect = Impresora.SyncPrinter();
                if(printconnect == true)
                {

                    cout <<"Impresora conectada y sincronizada   CLEAR COMANDO2"<<endl;

                    Impresora.ClearFilePrinter(0xfe);
                }


            }
            else cout<<"Impresora no sincronizada"<<endl;

        }

    }
    Sleep(100);
     cout <<"Impresora2 "<<&Impresora<<endl;
}

