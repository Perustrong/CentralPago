#include "ServicioTarjetas/c_functionsk720.h"

c_FunctionsK720::c_FunctionsK720()
{

}

HANDLE c_FunctionsK720::ConnectCOM()
{
    HANDLE hComPort;
    hComPort = K720_CommOpen(PortDispenser);
        if(hComPort!=0)
        {

            cout << "Conexión COM OK!"<<endl;
            this->flagsComInside->flag_status_com(true);
            hComPortInside = hComPort;
            cout<<"HANDLE COM en la conexión"<<hComPort<<endl;
            return hComPort;
        }
        else
        {
            this->flagsComInside->flag_status_com(false);
            cout << "Error de Conexión COM"<<endl;
            return 0;

        }

}

c_flags_K720 c_FunctionsK720::TestSensor ()
{
    BYTE MacAddr = getMacAddr();
    BYTE StateInfo[4];
    char RecordInfo[300];
    int Check;

    memset(RecordInfo, 0, sizeof(RecordInfo));
    memset(StateInfo, 0, sizeof(StateInfo));
    //memset(Check,0,sizeof(Check));

    Check = K720_SensorQuery(getHANDLE(), MacAddr, StateInfo, RecordInfo);
    cout<<"Puerto com en el test"<<hComPortInside<<endl;

    cout<<"Check thread"<<Check<<endl;
    cout<<"StateInfo"<<StateInfo[3]<<endl;
    printf("%x", StateInfo[3]);




    if(StateInfo[3]==0x31)
    {
        this->flagsComInside->flag_sensor2_com(false);
        this->flagsComInside->flag_sensor3_com(true);
        this->flagsComInside->flag_sensor1_com(false);
    }
    if(StateInfo[3]==0x32)
    {
        this->flagsComInside->flag_sensor2_com(true);
        this->flagsComInside->flag_sensor3_com(false);
        this->flagsComInside->flag_sensor1_com(false);
    }
    if(StateInfo[3]==0x33)
    {
        this->flagsComInside->flag_sensor2_com(true);
        this->flagsComInside->flag_sensor3_com(true);
        this->flagsComInside->flag_sensor1_com(false);
    }
    if(StateInfo[3]==0x34)
    {
        this->flagsComInside->flag_sensor2_com(false);
        this->flagsComInside->flag_sensor3_com(false);
        this->flagsComInside->flag_sensor1_com(true);
    }
    if(StateInfo[3]==0x35)
    {
        this->flagsComInside->flag_sensor2_com(false);
        this->flagsComInside->flag_sensor3_com(false);
        this->flagsComInside->flag_sensor1_com(true);
    }
    if(StateInfo[3]==0x36)
    {
        this->flagsComInside->flag_sensor2_com(true);
        this->flagsComInside->flag_sensor3_com(false);
        this->flagsComInside->flag_sensor1_com(true);
    }
    if(StateInfo[3]==0x37)
    {
        this->flagsComInside->flag_sensor2_com(true);
        this->flagsComInside->flag_sensor3_com(true);
        this->flagsComInside->flag_sensor1_com(true);
    }

    cout<<"FlagSensors 1 2 3" <<endl
    <<*this->getc_flags_K720()->sensor1_com()<<*this->getc_flags_K720()->sensor2_com()<<*this->getc_flags_K720()->sensor3_com()
    <<endl;
    return *flagsComInside;
   // Sleep(100);
}

QString c_FunctionsK720::CardIDTarjeta()
{


    int Check;
    int sizeID = 5;
    BYTE CardID[5];
    QString numCard = NULL;


    char RecordInfo[300];

    BYTE tempByte;

    time_t EndWait;
    time_t Start = time(0);
    time_t Seconds = 10;
    bool TimeOut = true;
    char MacAddr = this->getMacAddr();

    EndWait = Start + Seconds;

    if(*flagsComInside->estado_com()==false)
    {
        HANDLE hComPortAux;
        hComPortAux = ConnectCOM();
        if(hComPortAux==0)
        {
            cout<<"Imposible realizar conexión con Dispensador"<<endl;

        }
        else
        {
            this->TestSensor();
            cout<<" Sensor2 y Sensor3 = "<< *this->getc_flags_K720()->sensor2_com() << *this->getc_flags_K720()->sensor3_com()<<endl;
           if(*this->getc_flags_K720()->sensor2_com() == true || *this->getc_flags_K720()->sensor3_com() == true)
           {
               Check = K720_SendCmd(this->getHANDLE(),MacAddr, "FC7", 3, RecordInfo);
               Sleep(200);
               Check = K720_SendCmd(this->getHANDLE(),MacAddr, "CP", 2, RecordInfo);
               Sleep(33);
           }
            Sleep(1000);
            while (Start < EndWait)
            {
                if(*this->getc_flags_K720()->sensor2_com() == true && *this->getc_flags_K720()->sensor3_com() == true)
                {
                    TimeOut = false;
                    break;
                }
                this->TestSensor();
                Start = time(0);

            }
            if(TimeOut==true)
            {
                cout<<"TimeOut! Tiempo de espera finalizado";
                Check = K720_CommClose(hComPortInside);
                cout << "Check ComClose" << Check << endl;
                this->flagsComInside->flag_status_com(false);

                return "fail";
            }
            else
            {

                Check = K720_S50DetectCard(this->getHANDLE(), MacAddr,RecordInfo);

                if(Check==0)
                {
                    Check = K720_S50GetCardID(this->getHANDLE(),MacAddr,CardID,RecordInfo);
                    cout<<"Check = "<<Check<<endl<<"Card ID = "<<CardID<<endl;
                    printf("%x", CardID);
                    numCard = BYTEStringtoQString(CardID,sizeID);
                    return numCard;


                }
                else
                {
                    ExpulsarTarjeta();
                    Check = K720_CommClose(hComPortInside);
                    cout << "Check ComClose" << Check << endl;
                    this->flagsComInside->flag_status_com(false);

                    return "fail";
                }
            }
            ExpulsarTarjeta();
            Check = K720_CommClose(hComPortInside);
            cout << "Check ComClose" << Check << endl;
            this->flagsComInside->flag_status_com(false);
        }


    }

    else
    {
        this->TestSensor();
        cout<<" Sensor2 y Sensor3 = "<< *this->getc_flags_K720()->sensor2_com() << *this->getc_flags_K720()->sensor3_com()<<endl;
       if(*this->getc_flags_K720()->sensor2_com() == true || *this->getc_flags_K720()->sensor3_com() == true)
       {
           Check = K720_SendCmd(this->getHANDLE(),MacAddr, "FC7", 3, RecordInfo);
           Sleep(200);
           Check = K720_SendCmd(this->getHANDLE(),MacAddr, "CP", 2, RecordInfo);
           Sleep(33);
       }
        Sleep(1000);
        while (Start < EndWait)
        {
            if(*this->getc_flags_K720()->sensor2_com() == true && *this->getc_flags_K720()->sensor3_com() == true)
            {
                TimeOut = false;
                break;
            }
            this->TestSensor();
            Start = time(0);

        }
        if(TimeOut==true)
        {
            cout<<"TimeOut! Tiempo de espera finalizado";
            Check = K720_CommClose(hComPortInside);
            cout << "Check ComClose" << Check << endl;
            this->flagsComInside->flag_status_com(false);
            return "fail";
        }
        else
        {

            Check = K720_S50DetectCard(this->getHANDLE(), MacAddr,RecordInfo);

            if(Check==0)
            {
                Check = K720_S50GetCardID(this->getHANDLE(),MacAddr,CardID,RecordInfo);
                cout<<"Check = "<<Check<<endl<<"Card ID = "<<CardID<<endl;
                printf("%x", CardID);
                numCard = BYTEStringtoQString(CardID,sizeID);
                return numCard;


            }
            else
            {
                Check = K720_SendCmd(this->getHANDLE(),MacAddr, "FC0", 3, RecordInfo);
                Check = K720_CommClose(hComPortInside);
                cout << "Check ComClose" << Check << endl;
                this->flagsComInside->flag_status_com(false);
                ExpulsarTarjeta();
                return "fail";
            }
        }
        ExpulsarTarjeta();
        Check = K720_CommClose(hComPortInside);
        cout << "Check ComClose" << Check << endl;
        this->flagsComInside->flag_status_com(false);
    }



}

void c_FunctionsK720::EnableMouth()
{
    int Check;
    char MacAddr = this->getMacAddr();
    char RecordInfo[300];

    if(*flagsComInside->estado_com()==false)
    {
        HANDLE hComPortAux;
        hComPortAux = ConnectCOM();
        if(hComPortAux==0)
        {
            cout<<"Imposible realizar conexión con Dispensador"<<endl;
        }
        else
        {

                Check = K720_SendCmd(this->getHANDLE(),MacAddr, "BE", 2, RecordInfo);
                Sleep(200);

              //  Check = K720_CommClose(hComPortInside);
              //  cout << "Check ComClose" << Check << endl;
              //  this->flagsComInside->flag_status_com(false);

        }
    }

    else
    {
        Check = K720_SendCmd(this->getHANDLE(),MacAddr, "BE", 2, RecordInfo);
        Sleep(200);

     //   Check = K720_CommClose(hComPortInside);
     //   cout << "Check ComClose" << Check << endl;
     //   this->flagsComInside->flag_status_com(false);
    }

}

void c_FunctionsK720::DisableMouth()
{
    int Check;
    char MacAddr = this->getMacAddr();
    char RecordInfo[300];

    if(*flagsComInside->estado_com()==false)
    {
        HANDLE hComPortAux;
        hComPortAux = ConnectCOM();
        if(hComPortAux==0)
        {
            cout<<"Imposible realizar conexión con Dispensador"<<endl;
        }
        else
        {

                Check = K720_SendCmd(this->getHANDLE(),MacAddr, "FC8", 3, RecordInfo);
                Sleep(200);

                Check = K720_CommClose(hComPortInside);
                cout << "Check ComClose" << Check << endl;
                this->flagsComInside->flag_status_com(false);

        }
    }

    else
    {
        Check = K720_SendCmd(this->getHANDLE(),MacAddr, "FC8", 3, RecordInfo);
        Sleep(200);

        Check = K720_CommClose(hComPortInside);
        cout << "Check ComClose" << Check << endl;
        this->flagsComInside->flag_status_com(false);
    }


}

void c_FunctionsK720::ExpulsarTarjeta()
{
    int Check;
    char MacAddr = this->getMacAddr();
    char RecordInfo[300];

    if(*flagsComInside->estado_com()==false)
    {
        HANDLE hComPortAux;
        hComPortAux = ConnectCOM();
        if(hComPortAux==0)
        {
            cout<<"Imposible realizar conexión con Dispensador"<<endl;
        }
        else
        {
            this->TestSensor();
            cout<<" Sensor2 y Sensor3 = "<< *this->getc_flags_K720()->sensor2_com() << *this->getc_flags_K720()->sensor3_com()<<endl;
           if(*this->getc_flags_K720()->sensor2_com() == true || *this->getc_flags_K720()->sensor3_com() == true)
           {
                Check = K720_SendCmd(this->getHANDLE(),MacAddr, "FC7", 3, RecordInfo);
                Sleep(200);
                Check = K720_SendCmd(this->getHANDLE(),MacAddr, "FC0", 3, RecordInfo);
                Check = K720_CommClose(hComPortInside);
                cout << "Check ComClose" << Check << endl;
                this->flagsComInside->flag_status_com(false);
           }
        }
    }

    else
    {
        this->TestSensor();
        cout<<" Sensor2 y Sensor3 = "<< *this->getc_flags_K720()->sensor2_com() << *this->getc_flags_K720()->sensor3_com()<<endl;
        if(*this->getc_flags_K720()->sensor2_com() == true || *this->getc_flags_K720()->sensor3_com() == true)
        {
            Check = K720_SendCmd(this->getHANDLE(),MacAddr, "FC0", 3, RecordInfo);
            Check = K720_CommClose(hComPortInside);
            cout << "Check ComClose" << Check << endl;
            this->flagsComInside->flag_status_com(false);
        }
    }

}

float c_FunctionsK720::LeerTarjeta()
{
    int Check;
    int sizeID = 5;
    BYTE CardID[5];
    QString numCard = NULL;
    BYTE SectorAddr,BlockAddr;
    BYTE _BlockRecive[20];
    char RecordInfo[300];
    BYTE KEY[6] ={0xff,0xff,0xff,0xff,0xff,0xff};
    BYTE tempByte;
    memset(_BlockRecive, 0, sizeof(_BlockRecive));
    time_t EndWait;
    time_t Start = time(0);
    time_t Seconds = 10;
    bool TimeOut = true;
    char MacAddr = this->getMacAddr();
    UltimaID = "";
    UltimoNumCard = "";

    EndWait = Start + Seconds;

    if(*flagsComInside->estado_com()==false)
    {
        HANDLE hComPortAux;
        hComPortAux = ConnectCOM();
        if(hComPortAux==0)
        {
            cout<<"Imposible realizar conexión con Dispensador"<<endl;
        }
        else
        {

            TestSensor();
         //   cout<<" Sensor2 y Sensor3 = "<< *getc_flags_K720()->sensor2_com() << *getc_flags_K720()->sensor3_com()<<endl;
           if(*getc_flags_K720()->sensor2_com() == true || *getc_flags_K720()->sensor3_com() == true)
           {
               Check = K720_SendCmd(getHANDLE(),MacAddr, "FC7", 3, RecordInfo);
               Sleep(200);
               Check = K720_SendCmd(getHANDLE(),MacAddr, "CP", 2, RecordInfo);
               //Sleep(33);
           }

            //Sleep(300);
           EnableMouth();

            while (Start < EndWait)
            {
                if(*getc_flags_K720()->sensor2_com() == true && *getc_flags_K720()->sensor3_com() == true)
                {
                    TimeOut = false;
                    break;
                }
                TestSensor();
                Start = time(0);

            }
            if(TimeOut==true)
            {
                cout<<"TimeOut! Tiempo de espera finalizado";
                Check = K720_CommClose(hComPortInside);
                cout << "Check ComClose" << Check << endl;
                flagsComInside->flag_status_com(false);
                return 999;
            }
            else
            {
                Check = K720_SendCmd(getHANDLE(),MacAddr, "FC7", 3, RecordInfo);
                Sleep(1000);

                Check = K720_S50DetectCard(getHANDLE(), MacAddr,RecordInfo);

                if(Check==0)
                {
                    Check = K720_S50GetCardID(getHANDLE(),MacAddr,CardID,RecordInfo);
                    cout<<"Check = "<<Check<<endl<<"Card ID = "<<CardID<<endl;
                    for (int i =0;i<sizeID; i++)
                    {
                        printf("CardID %x", CardID[i]);
                    }
                    numCard = BYTEStringtoQString(CardID,sizeID);

                    cout << "numCard convertido QString = "<<numCard.toStdString()<<endl;

                    if(Check == 0)
                    {
                        SectorAddr = 01;
                        BlockAddr = 00;

                        if(Check==0)
                        {

                             Check = K720_S50LoadSecKey(getHANDLE(),MacAddr,SectorAddr, 0x30,KEY,RecordInfo);
                             cout<<"Check LOADSECURITY = "<<Check<<endl;
                            if(Check == 0)
                            {

                                Check = K720_S50ReadBlock(getHANDLE(), MacAddr, SectorAddr,BlockAddr,_BlockRecive,RecordInfo);

                                cout<<"Check ReadData = "<<endl<<"Record Info Lectura" <<RecordInfo<<endl<<"Tamaño del bloque recibido"<<sizeof(_BlockRecive)<< endl;
                                cout << "BlockRecibe1 = "<<_BlockRecive<<endl;
                                printf("CheckRead1 %x",Check);



                                if(Check ==0)
                                {
                                    if(_BlockRecive[0]=='I')
                                    {

                                        if(_BlockRecive[1]=='D')
                                        {
                                            if(_BlockRecive[2] == '=')
                                            {
                                                int SizeID =(_BlockRecive[3]-'0');
                                                //unsigned char Mensaje[SizeID];
                                                QString ID = NULL;

                                                cout<<"Tamaño recogido en la tarjeta = "<<_BlockRecive[3]<<endl<<SizeID<<endl;
                                                for(int i = 0;i<SizeID;i++)
                                                {
                                                    ID[i]=_BlockRecive[i+4];
                                                }

                                               // ID = BYTEStringtoQString(Mensaje, SizeID);
                                                float saldofloat = BaseDatos.SaldoCliente(numCard,ID);
                                                cout<<"saldofloat = " <<saldofloat<<endl;
                                                saldofloat = saldofloat*100;

                                                UltimaID = ID;
                                                UltimoNumCard = numCard;

                                               return saldofloat;

                                           }
                                       }
                                   }

                                }

                                ExpulsarTarjeta();


                                Check = K720_CommClose(hComPortInside);
                                cout << "Check ComClose" << Check << endl;
                                flagsComInside->flag_status_com(false);
                                return 999;

                            }

                            else
                            {

                                ExpulsarTarjeta();

                                Check = K720_CommClose(hComPortInside);
                                cout << "Check ComClose" << Check << endl;
                                flagsComInside->flag_status_com(false);
                                return 999;
                            }
                        }
                        else
                        {
                            ExpulsarTarjeta();
                            Check = K720_CommClose(hComPortInside);
                            cout << "Check ComClose" << Check << endl;
                            flagsComInside->flag_status_com(false);
                            return 999;
                        }
                    }
                    else
                    {
                        ExpulsarTarjeta();
                        Check = K720_CommClose(hComPortInside);
                        cout << "Check ComClose" << Check << endl;
                        flagsComInside->flag_status_com(false);
                        return 999;
                    }
                }
                else
                {
                    ExpulsarTarjeta();
                    Check = K720_CommClose(hComPortInside);
                    cout << "Check ComClose" << Check << endl;
                    flagsComInside->flag_status_com(false);
                    return 999;
                }
            }
            ExpulsarTarjeta();
            Check = K720_CommClose(hComPortInside);
            cout << "Check ComClose" << Check << endl;
            flagsComInside->flag_status_com(false);
            return 999;
        }


    }

    else
    {
        TestSensor();
        cout<<" Sensor2 y Sensor3 = "<< *getc_flags_K720()->sensor2_com() << *getc_flags_K720()->sensor3_com()<<endl;
        if(*getc_flags_K720()->sensor2_com() == true || *getc_flags_K720()->sensor3_com() == true)
        {
           Check = K720_SendCmd(getHANDLE(),MacAddr, "FC7", 3, RecordInfo);
           Sleep(200);
           Check = K720_SendCmd(getHANDLE(),MacAddr, "CP", 2, RecordInfo);
          // Sleep(33);
        }
        EnableMouth();
       // Sleep(1000);
        while (Start < EndWait)
        {
            if(*getc_flags_K720()->sensor2_com() == true && *getc_flags_K720()->sensor3_com() == true)
            {
                TimeOut = false;
                break;
            }
            TestSensor();
            Start = time(0);

        }
        if(TimeOut==true)
        {
            cout<<"TimeOut! Tiempo de espera finalizado";
            Check = K720_CommClose(hComPortInside);
            cout << "Check ComClose" << Check << endl;
            flagsComInside->flag_status_com(false);
            return 999;
        }
        else
        {
            Check = K720_SendCmd(getHANDLE(),MacAddr, "FC7", 3, RecordInfo);
            Sleep(1000);
            Check = K720_S50DetectCard(getHANDLE(), MacAddr,RecordInfo);

            if(Check==0)
            {
                Check = K720_S50GetCardID(getHANDLE(),MacAddr,CardID,RecordInfo);
                cout<<"Check = "<<Check<<endl<<"Card ID = "<<CardID<<endl;
                for (int i =0;i<sizeID; i++)
                {
                    printf("CardID %x", CardID[i]);
                }
                numCard = BYTEStringtoQString(CardID,sizeID);

                cout << "numCard convertido QString = "<<numCard.toStdString()<<endl;

                if(Check == 0)
                {
                    SectorAddr = 01;
                    BlockAddr = 00;

                    if(Check==0)
                    {

                         Check = K720_S50LoadSecKey(getHANDLE(),MacAddr,SectorAddr, 0x30,KEY,RecordInfo);
                         cout<<"Check LOADSECURITY = "<<Check<<endl;
                        if(Check == 0)
                        {
                            QString BloqueRecibido;
                            Check = K720_S50ReadBlock(getHANDLE(), MacAddr, SectorAddr,BlockAddr,_BlockRecive,RecordInfo);

                            cout<<"Check ReadData = "<<endl<<"Record Info Lectura" <<RecordInfo<<endl<<"Tamaño del bloque recibido"<<sizeof(_BlockRecive)<< endl;
                            cout << "BlockRecibe1 = "<<_BlockRecive<<endl;
                            printf("CheckRead1 %x",Check);



                            if(Check ==0)
                            {
                               if(_BlockRecive[0]=='I')
                               {

                                   if(_BlockRecive[1]=='D')
                                   {
                                       if(_BlockRecive[2] == '=')
                                       {
                                           int SizeID =(_BlockRecive[3]-'0');
                                           //unsigned char Mensaje[SizeID];
                                           QString ID = NULL;

                                           cout<<"Tamaño recogido en la tarjeta = "<<_BlockRecive[3]<<endl<<SizeID<<endl;
                                           for(int i = 0;i<SizeID;i++)
                                           {
                                               ID[i]=_BlockRecive[i+4];
                                           }
                                           UltimaID = ID;
                                           UltimoNumCard = numCard;

                                          // ID = BYTEStringtoQString(Mensaje, SizeID);
                                           float saldofloat = BaseDatos.SaldoCliente(numCard,ID);
                                           cout<<"saldofloat = " <<saldofloat<<endl;
                                           saldofloat = saldofloat*100;


                                           return saldofloat;

                                       }
                                   }
                               }

                            }

                            ExpulsarTarjeta();


                            Check = K720_CommClose(hComPortInside);
                            cout << "Check ComClose" << Check << endl;
                            flagsComInside->flag_status_com(false);
                            return 999;

                        }

                        else
                        {

                            ExpulsarTarjeta();

                            Check = K720_CommClose(hComPortInside);
                            cout << "Check ComClose" << Check << endl;
                            flagsComInside->flag_status_com(false);
                            return 999;
                        }
                    }
                    else
                    {
                        ExpulsarTarjeta();
                        Check = K720_CommClose(hComPortInside);
                        cout << "Check ComClose" << Check << endl;
                        flagsComInside->flag_status_com(false);
                        return 999;
                    }
                }
                else
                {
                    ExpulsarTarjeta();
                    Check = K720_CommClose(hComPortInside);
                    cout << "Check ComClose" << Check << endl;
                    flagsComInside->flag_status_com(false);
                    return 999;
                }
            }
            else
            {
                ExpulsarTarjeta();
                Check = K720_CommClose(hComPortInside);
                cout << "Check ComClose" << Check << endl;
                flagsComInside->flag_status_com(false);
                return 999;
            }
        }
        ExpulsarTarjeta();
        Check = K720_CommClose(hComPortInside);
        cout << "Check ComClose" << Check << endl;
        flagsComInside->flag_status_com(false);
        return 999;
        }
    return 999;
}

QString c_FunctionsK720::BYTEStringtoQString(unsigned char *CardID, int size)
{
   /* unsigned char CardIDAux[5];
    string strCardIDAux;
    QString CardIDOut;
    stringstream ID;

    for (int i=0;i<sizeof(CardIDAux);i++)
    {
        CardIDAux[i]=CardID[i];
        cout << "Byte"<<i<<endl;
        printf("%x",CardIDAux[i]);

    }

     ID << hex<<CardIDAux;
     strCardIDAux = ID.str();

     cout << "ID Tarjeta STRING"<<strCardIDAux<<endl<<"Tamaño de strCardID = "<<sizeof(strCardIDAux)<<endl;
     for (int i=0; i<sizeof(strCardIDAux);i++)
     {
         cout << "Byte interno "<<i<<endl;
         printf("%x",strCardIDAux[i]);


     }



     CardIDOut = QString::fromStdString(CardIDAux);

     return CardIDOut;
*/
    QString s;
        QString result = "";
        int rev = size;

        // Print String in Reverse order....
        for ( int i = 0; i<rev; i++)
            {
               s = QString("%1").arg(CardID[i],0,16);

               if(s == "0"){
                  s="00";
                 }
             result.append(s);

             }
       return result;
    }





QString c_FunctionsK720::CrearTarjeta(QString Nombre, QString Apellidos, QString ID)
{
    int Check;
    int sizeID = 5;
    BYTE CardID[5];
    BYTE SectorAddr,BlockAddr;

    string strNombre = Nombre.toStdString();
    string strApellidos = Apellidos.toStdString();
    unsigned char strID[ID.length()+4];
    //int IDLength = ID.length()+4;
    unsigned char strIDLength = ((unsigned char)(ID.length()))+'0';
    unsigned char strIDAux[ID.length()];
    memcpy(strIDAux,ID.toStdString().c_str(),ID.length());

    cout <<"strID convertido a unsigned char"<< strID <<"Longitud ID = "<<ID.length()<<endl;

    for(int i = 0; i<sizeof(strID);i++)
    {
        if(i==0) strID[i] = 'I';                //Contenido del mensaje = "ID=",nº de cifras,cifra1,cifra2...
        else if(i==1) strID[i] = 'D';
        else if(i==2) strID[i] = '=';
        else if(i==3) strID[i] = strIDLength;
        else
        {
            strID[i] = strIDAux[i-4];
        }
        printf("strID %x",strID[i]);

    }

    cout <<"Mensaje ID completo = "<<strID<<endl;

    QString Auxiliar;

    //Intentar convertir el string en byte incluyendo el 0!!!
    /*BYTE _BlockData[100];
    strncpy((char*)&_BlockData, strNombre.c_str(),sizeof(strNombre.c_str()));
    strncat((char*)&_BlockData,strApellidos.c_str(),sizeof(strApellidos.c_str()));
    //strncat((char*)&_BlockData,strID.c_str(),sizeof(strID.c_str()));*/

  //  cout<<"El bloque de datos a enviar es" << _BlockData<<endl;
   // BYTE _bBlockData[100] = convert:: ToByte(_BlockData);

    BYTE _BlockRecive[]={0x43,0x41,0x52,0x4c,0x4f,0x73,0x5f,0x50,0x45,0x52,0x55,0x4a,0x4f,0x32,0x33};
    char RecordInfo[300];
    char MacAddr = this->getMacAddr();
    BYTE KEY[6] ={0xff,0xff,0xff,0xff,0xff,0xff};
    BYTE tempByte;
    memset(_BlockRecive, 0, sizeof(_BlockRecive));
    memset(CardID, 0, sizeof(CardID));
    cout<<" Sensor2 y Sensor3 = "<< *this->getc_flags_K720()->sensor2_com() << *this->getc_flags_K720()->sensor3_com()<<endl;

    if(*flagsComInside->estado_com()==false)
    {
        HANDLE hComPortAux;
        hComPortAux = ConnectCOM();
        if(hComPortAux==0)
        {
            cout<<"Imposible realizar conexión con Dispensador"<<endl;
        }
        else
        {

           this->TestSensor();
           Sleep(99);
            if (*this->getc_flags_K720()->sensor2_com() == true && *this->getc_flags_K720()->sensor3_com() == true)
            {
                Check = K720_S50DetectCard(this->getHANDLE(), this->getMacAddr(),RecordInfo);

                if(Check==0)
                {
                    Check = K720_S50GetCardID(this->getHANDLE(),MacAddr,CardID,RecordInfo);
                    cout<<"Check = "<<Check<<endl<<"Card ID = "<<CardID<<endl<<"Tamaño CardID = "<<sizeof(CardID)<<endl;;
                     cout<<"Check GetID = "<<Check<<endl<<"RecordInfo = "<<RecordInfo<<endl;
                    for (int i =0; i<10;i++)
                    {
                        printf("La ID hexadecimal es = %x", CardID[i]);
                        printf("La ID Caracter es = %c", CardID[i]);
                        cout << "CardID bucle for" << CardID[i];

                    }



                 //   qDebug() << "cardID Debug", CardID;

                    if(Check == 0)
                    {
                        SectorAddr = 01;
                        BlockAddr = 00;

                        if(Check==0)
                        {

                             Check = K720_S50LoadSecKey(this->getHANDLE(),MacAddr,SectorAddr, 0x30,KEY,RecordInfo);
                             cout<<"Check LOADSECURITY = "<<Check<<endl<<"RecordInfo = "<<RecordInfo<<endl;
                            if(Check == 0)
                            {
                                Check = K720_S50WriteBlock(this->getHANDLE(), MacAddr, SectorAddr,BlockAddr,strID,RecordInfo);
                                cout<<"Check WriteData = "<<Check<<endl<<"RecordInfo = "<<RecordInfo<<endl<<"BlockData = "<< strID<<endl;
                            }

                        Sleep(1000);
                        if(Check == 0)
                        {
                            Check = K720_S50ReadBlock(this->getHANDLE(), MacAddr, SectorAddr,BlockAddr,_BlockRecive,RecordInfo);

                            cout<<"BlockData = "<<strID<<endl<<"BlockRecive = "<<_BlockRecive<<endl<<"Record info READ = "<<endl<<RecordInfo;

                            int Aux=1;
                            for (int i = 0; i< sizeof(strID); i++)
                            {
                                if (strID[i]==_BlockRecive[i]) Aux = 1;
                                else Aux = 0;
                            }
                            if (Aux==1)
                            {
                                Check = K720_SendCmd(this->getHANDLE(),MacAddr, "FC0", 3, RecordInfo);
                                Check = K720_CommClose(hComPortInside);
                                cout << "Check ComClose" << Check << endl;
                                this->flagsComInside->flag_status_com(false);


                               Auxiliar = BYTEStringtoQString(CardID,sizeID);
                                cout <<"Auxiliar fuera de la rutina de cambio a QString"<<Auxiliar.toStdString()<<endl;
                                return Auxiliar;
                            }
                            else
                            {
                                Check = K720_SendCmd(this->getHANDLE(),MacAddr, "CP", 2, RecordInfo);
                                Check = K720_CommClose(hComPortInside);
                                cout << "Check ComClose, comprobacion erronea" << Check << endl;
                                this->flagsComInside->flag_status_com(false);
                                return false;
                            }
                        }
                        }
                    }

                }
            }
            else
            {
                Check = K720_SendCmd(this->getHANDLE(),MacAddr, "FC7", 3, RecordInfo);
                Sleep(2000);
                this->TestSensor();
                  Sleep(99);

                if (*this->getc_flags_K720()->sensor2_com() == true && *this->getc_flags_K720()->sensor3_com() == true)
                {
                    Check = K720_S50DetectCard(this->getHANDLE(), MacAddr,RecordInfo);

                    if(Check==0)
                    {
                        Check = K720_S50GetCardID(this->getHANDLE(),MacAddr,CardID,RecordInfo);
                        cout<<"Check = "<<Check<<endl<<"Card ID = "<<*CardID<<endl;
                        printf("La ID hexadecimal es = %x", CardID);
                        printf("La ID Caracter es = %c", CardID);
                       // qDebug() << "cardID Debug"<< *CardID<<endl;

                        cout<<"Check = "<<Check<<endl<<"Card ID = "<<CardID<<endl<<"Tamaño CardID = "<<sizeof(CardID)<<endl;;
                         cout<<"Check GetID = "<<Check<<endl<<"RecordInfo = "<<RecordInfo<<endl;
                        for (int i =0; i<10;i++)
                        {
                            printf("La ID hexadecimal es = %x", CardID[i]);
                            printf("La ID Caracter es = %c", CardID[i]);
                            cout << "CardID bucle for" << CardID[i];

                        }

                        if(Check == 0)
                        {
                            SectorAddr = 01;
                            BlockAddr = 00;

                            if(Check==0)
                            {

                                Check = K720_S50LoadSecKey(this->getHANDLE(),MacAddr,SectorAddr, 0x30,KEY,RecordInfo);
                                cout<<"Check LOADSECURITY = "<<Check<<endl<<"RecordInfo = "<<RecordInfo<<endl;
                                if(Check == 0)
                                {
                                    Check = K720_S50WriteBlock(this->getHANDLE(), MacAddr, SectorAddr,BlockAddr,strID,RecordInfo);
                                    cout<<"Check WriteData = "<<Check<<endl<<"RecordInfo = "<<RecordInfo<<endl<<"BlockData = "<< strID<<endl;
                                }
                                Sleep(1000);
                                if(Check == 0)
                                {
                                    Check = K720_S50ReadBlock(this->getHANDLE(), MacAddr, SectorAddr,BlockAddr,_BlockRecive,RecordInfo);

                                    cout<<"BlockData = "<<strID<<endl<<"BlockRecive = "<<_BlockRecive<<endl<<"Record info READ = "<<endl<<RecordInfo;

                                    int Aux=1;
                                    for (int i = 0; i< sizeof(strID); i++)
                                    {
                                        if (strID[i]==_BlockRecive[i]) Aux = 1;
                                        else Aux = 0;
                                    }
                                    if (Aux==1)
                                    {
                                        Check = K720_SendCmd(this->getHANDLE(),MacAddr, "FC0", 3, RecordInfo);
                                        Check = K720_CommClose(hComPortInside);
                                        cout << "Check ComClose" << Check << endl;
                                        this->flagsComInside->flag_status_com(false);
                                        Auxiliar = BYTEStringtoQString(CardID,sizeID);
                                        cout <<"Auxiliar fuera de la rutina de cambio a QString"<<Auxiliar.toStdString()<<endl;
                                         return Auxiliar;
                                    }
                                    else
                                    {
                                        Check = K720_SendCmd(this->getHANDLE(),MacAddr, "CP", 2, RecordInfo);
                                        Check = K720_CommClose(hComPortInside);
                                        cout << "Check ComClose, comprobacion erronea" << Check << endl;
                                        this->flagsComInside->flag_status_com(false);
                                        return false;
                                    }
                                }
                            }
                        }
                    }
                }
                else
                {
                    Check = K720_CommClose(hComPortInside);
                    cout << "Check ComClose" << Check << endl;
                    this->flagsComInside->flag_status_com(false);
                    return false;

                }
            }
        }
    }

    else
    {
        this->TestSensor();
        Sleep(99);
         if (*this->getc_flags_K720()->sensor2_com() == true && *this->getc_flags_K720()->sensor3_com() == true)
         {
             Check = K720_S50DetectCard(this->getHANDLE(), this->getMacAddr(),RecordInfo);

             if(Check==0)
             {
                 Check = K720_S50GetCardID(this->getHANDLE(),MacAddr,CardID,RecordInfo);
                 cout<<"Check = "<<Check<<endl<<"Card ID = "<<CardID<<endl<<"Tamaño CardID = "<<sizeof(CardID)<<endl;;
                  cout<<"Check GetID = "<<Check<<endl<<"RecordInfo = "<<RecordInfo<<endl;
                 for (int i =0; i<10;i++)
                 {
                     printf("La ID hexadecimal es = %x", CardID[i]);
                     printf("La ID Caracter es = %c", CardID[i]);
                     cout << "CardID bucle for" << CardID[i];

                 }



              //   qDebug() << "cardID Debug", CardID;

                 if(Check == 0)
                 {
                     SectorAddr = 01;
                     BlockAddr = 00;

                     if(Check==0)
                     {

                          Check = K720_S50LoadSecKey(this->getHANDLE(),MacAddr,SectorAddr, 0x30,KEY,RecordInfo);
                          cout<<"Check LOADSECURITY = "<<Check<<endl<<"RecordInfo = "<<RecordInfo<<endl;
                         if(Check == 0)
                         {
                             Check = K720_S50WriteBlock(this->getHANDLE(), MacAddr, SectorAddr,BlockAddr,strID,RecordInfo);
                             cout<<"Check WriteData = "<<Check<<endl<<"RecordInfo = "<<RecordInfo<<endl<<"BlockData = "<< strID<<endl;
                         }

                     Sleep(1000);
                     if(Check == 0)
                     {
                         Check = K720_S50ReadBlock(this->getHANDLE(), MacAddr, SectorAddr,BlockAddr,_BlockRecive,RecordInfo);

                         cout<<"BlockData = "<<strID<<endl<<"BlockRecive = "<<_BlockRecive<<endl<<"Record info READ = "<<endl<<RecordInfo;

                         int Aux=1;
                         for (int i = 0; i< sizeof(strID); i++)
                         {
                             if (strID[i]==_BlockRecive[i]) Aux = 1;
                             else Aux = 0;
                         }
                         if (Aux==1)
                         {
                             Check = K720_SendCmd(this->getHANDLE(),MacAddr, "FC0", 3, RecordInfo);
                             Check = K720_CommClose(hComPortInside);
                             cout << "Check ComClose" << Check << endl;
                             this->flagsComInside->flag_status_com(false);


                            Auxiliar = BYTEStringtoQString(CardID,sizeID);
                             cout <<"Auxiliar fuera de la rutina de cambio a QString"<<Auxiliar.toStdString()<<endl;
                             return Auxiliar;
                         }
                         else
                         {
                             Check = K720_SendCmd(this->getHANDLE(),MacAddr, "CP", 2, RecordInfo);
                             Check = K720_CommClose(hComPortInside);
                             cout << "Check ComClose, comprobacion erronea" << Check << endl;
                             this->flagsComInside->flag_status_com(false);
                             return false;
                         }
                     }
                     }
                 }

             }
         }
         else
         {
             Check = K720_SendCmd(this->getHANDLE(),MacAddr, "FC7", 3, RecordInfo);
             Sleep(2000);
             this->TestSensor();
               Sleep(99);

             if (*this->getc_flags_K720()->sensor2_com() == true && *this->getc_flags_K720()->sensor3_com() == true)
             {
                 Check = K720_S50DetectCard(this->getHANDLE(), MacAddr,RecordInfo);

                 if(Check==0)
                 {
                     Check = K720_S50GetCardID(this->getHANDLE(),MacAddr,CardID,RecordInfo);
                     cout<<"Check = "<<Check<<endl<<"Card ID = "<<*CardID<<endl;
                     printf("La ID hexadecimal es = %x", CardID);
                     printf("La ID Caracter es = %c", CardID);
                    // qDebug() << "cardID Debug"<< *CardID<<endl;

                     cout<<"Check = "<<Check<<endl<<"Card ID = "<<CardID<<endl<<"Tamaño CardID = "<<sizeof(CardID)<<endl;;
                      cout<<"Check GetID = "<<Check<<endl<<"RecordInfo = "<<RecordInfo<<endl;
                     for (int i =0; i<10;i++)
                     {
                         printf("La ID hexadecimal es = %x", CardID[i]);
                         printf("La ID Caracter es = %c", CardID[i]);
                         cout << "CardID bucle for" << CardID[i];

                     }

                     if(Check == 0)
                     {
                         SectorAddr = 01;
                         BlockAddr = 00;

                         if(Check==0)
                         {

                             Check = K720_S50LoadSecKey(this->getHANDLE(),MacAddr,SectorAddr, 0x30,KEY,RecordInfo);
                             cout<<"Check LOADSECURITY = "<<Check<<endl<<"RecordInfo = "<<RecordInfo<<endl;
                             if(Check == 0)
                             {
                                 Check = K720_S50WriteBlock(this->getHANDLE(), MacAddr, SectorAddr,BlockAddr,strID,RecordInfo);
                                 cout<<"Check WriteData = "<<Check<<endl<<"RecordInfo = "<<RecordInfo<<endl<<"BlockData = "<< strID<<endl;
                             }
                             Sleep(1000);
                             if(Check == 0)
                             {
                                 Check = K720_S50ReadBlock(this->getHANDLE(), MacAddr, SectorAddr,BlockAddr,_BlockRecive,RecordInfo);
                                 cout<<"BlockData = "<<strID<<endl<<"BlockRecive = "<<_BlockRecive<<endl<<"Record info READ = "<<endl<<RecordInfo;

                                 int Aux=1;
                                 for (int i = 0; i< sizeof(strID); i++)
                                 {
                                     if (strID[i]==_BlockRecive[i]) Aux = 1;
                                     else Aux = 0;
                                 }
                                 if (Aux==1)
                                 {
                                     Check = K720_SendCmd(this->getHANDLE(),MacAddr, "FC0", 3, RecordInfo);
                                     Check = K720_CommClose(hComPortInside);
                                     cout << "Check ComClose" << Check << endl;
                                     this->flagsComInside->flag_status_com(false);
                                     Auxiliar = BYTEStringtoQString(CardID,sizeID);
                                     cout <<"Auxiliar fuera de la rutina de cambio a QString"<<Auxiliar.toStdString()<<endl;
                                      return Auxiliar;
                                 }
                                 else
                                 {
                                     Check = K720_SendCmd(this->getHANDLE(),MacAddr, "CP", 2, RecordInfo);
                                     Check = K720_CommClose(hComPortInside);
                                     cout << "Check ComClose, comprobacion erronea" << Check << endl;
                                     this->flagsComInside->flag_status_com(false);
                                     return false;
                                 }
                             }
                         }
                     }
                 }
             }
             else
             {
                 Check = K720_CommClose(hComPortInside);
                 cout << "Check ComClose" << Check << endl;
                 this->flagsComInside->flag_status_com(false);
                 return false;

             }
         }
    }


}


void c_FunctionsK720::setHANDLE(HANDLE hComPort)
{
    hComPortInside = hComPort;
}


HANDLE c_FunctionsK720::getHANDLE()
{
    return hComPortInside;

}


void c_FunctionsK720::setMacAddr(char MacAddr)
{

    MacAddrInside = MacAddr;
}
char c_FunctionsK720::getMacAddr()
{

    return MacAddrInside;
}


void c_FunctionsK720::setc_flags_K720(c_flags_K720* flagsCom)
{
    flagsComInside = flagsCom;

}


c_flags_K720* c_FunctionsK720::getc_flags_K720()
{

    return flagsComInside;
}
