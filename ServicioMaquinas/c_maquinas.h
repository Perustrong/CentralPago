#ifndef C_MAQUINAS_H
#define C_MAQUINAS_H

#include "windows.h"
#include <iostream>
#include <QString>
#include <QObject>
#include <QtCore>
#include "ServicioMaquinas/c_LogFileMaquinas.h"





using namespace std;

#define PROGRAMA_LIGERO 1
#define PROGRAMA_MEDIO 2
#define PROGRAMA_PESADO 3
#define PROGRAMA_SECADO 4
#define MINUTO_SECADO 5
#define EXTRA_1 6
#define EXTRA_2 7
#define EXTRA_3 8



class c_Maquinas:public QThread
{
    Q_OBJECT

public:
    c_Maquinas(QObject *parent = 0);
  //  virtual ~c_Maquinas(){};


    void run();

    void set_numMaquina(int Maquina);
    void set_numPrograma(int Programa);
    void set_numExtras(int Extras);
    void set_numTipoMaquina(int TipoMaquina);
    void set_numTiempoExtra(int newTiempoExtra);
    void set_PreciosEfectivo(int Parametro, float valor);
    void set_PreciosTarjeta(int Parametro, float valor);

    int get_numMaquina();
    int get_numPrograma();
    int get_numExtras();
    int get_numTipoMaquina();
    int get_numTiempoExtra();
    float get_PreciosEfectivo(int Parametro);
    float get_PreciosTarjeta(int Parametro);

    HANDLE ConectarLav();
    HANDLE ConectarSec();
    bool ConfigLav(unsigned char NumMaq, unsigned char NumProg, unsigned char NumFase, unsigned char Habilitar, unsigned char NivelBano,
                   unsigned char Temp, unsigned char Dosificar, unsigned char TiempoDosi, unsigned char AccionMec, unsigned char TiempoRot,
                   unsigned char Desague, unsigned char TiempoCent, unsigned char Enfriamiento, unsigned char Pausa);
    bool ConfigSec(unsigned char NumMaq, unsigned char NumProg, unsigned char TiempoSec, unsigned char Calefaccion, unsigned char TempSalida,
                   unsigned char TempEntrada, unsigned char VelRotacion, unsigned char AccionMec, unsigned char TiempoEnfri);
    bool SendCmd(unsigned char *Cmd);
    void InfoStatus(unsigned char Maquina);
    unsigned char* ReadCmd();
    unsigned char InterpretaMensaje(unsigned char Cmd);
    unsigned char CalculaCRC(unsigned char* Cmd);
    void ActualizarEstados();


    void set_CmdNumMaq(unsigned char);
    void set_CmdNumProgram(unsigned char);
    void set_CmdNumFase(unsigned char);
    void set_CmdTiempoSecado(unsigned char);
    void set_CmdCalefaccion(unsigned char);
    void set_CmdTempSalida(unsigned char);
    void set_CmdTempEntrada(unsigned char);
    void set_CmdVelRotacion(unsigned char);
    void set_CmdAccionMecanica(unsigned char);
    void set_CmdTiempoEnfriamiento(unsigned char);
    void set_CmdMinExtraSecado(unsigned char);
    void set_CmdTimeNoTeclado(unsigned char);
    void set_CmdHabilitarFase(unsigned char);
    void set_CmdNivelBano(unsigned char);
    void set_CmdTemperatura(unsigned char);
    void set_CmdDosificacion(unsigned char);
    void set_CmdTiempoRotacion(unsigned char);
    void set_CmdDesague(unsigned char);
    void set_CmdTiempoCentrifugado(unsigned char);
    void set_CmdEnfriamiento(unsigned char);
    void set_CmdPausa(unsigned char);
    void set_CmdTiempoDosificacion(unsigned char);
    void set_CmdModoLavadoExtra(unsigned char);
    void set_CmdTiempoLavadoExtra(unsigned char);
    void set_CmdModoAclaradoExtra(unsigned char);
    void set_CmdModoCentrifugadoExtra(unsigned char);
    void set_CmdTiempoCentrifugadoExtra(unsigned char);

    void SlotHilo();

private slots:
    void onActualizarConfiguracionLav(string);
    void onActualizarConfiguracionSec(string);
    void MaqStatus();



signals:

    void HandleLavadora(HANDLE);
    void HandleSecadora(HANDLE);




private:




    HANDLE hComPortLav = 0;
    TCHAR *CommPortLav = TEXT("COM3:");
    DCB dcbComLav;
    HANDLE hComPortSec = 0;
    TCHAR *CommPortSec = TEXT("COM5:");
    DCB dcbComSec;



    struct Precios
    {
        float ProgramaLigero = 0;
        float ProgramaMedio = 0;
        float ProgramaPesado = 0;
        float ProgramaSecado = 0;
        float MinutoSecado = 0;
        float Extra1 = 0;
        float Extra2 = 0;
        float Extra3 = 0;



    }PreciosEfectivo, PreciosTarjeta;

public:

    QThread Hilo;

    int numTipoMaquina = 0; // 1 - Lavadoras // 2 - Secadoras
    int numMaquina = 0;
    int numPrograma = 0;
        /*PROGRAMA LAVADORA     PROGRAMA SECADORA
         * 1 = Muy Sucio        1 = Caliente
         * 2 = Sucio            2 = Templado
         * 3 - Normal           3 = Frio
         * 4 - Delicado
         */
    int numTiempoExtra = 0;
    int numExtras = 0;
        /* LAVADORAS
         * 0 -> No Extra
         * 1 -> Extra 1
         * 2 -> Extra 2
         * 3 -> Extra 3
         * 4 -> Extra 1 + 2
         * 5 -> Extra 1 + 3
         * 6 -> Extra 2 + 3
         * 7 -> Extra 1 + 2 + 3 */


    unsigned char CmdNumMaq = 0x00;
    unsigned char CmdNumProgram = 0x00;
    unsigned char CmdNumFase = 0x00;
    unsigned char CmdTiempoSecado = 0x00;
    unsigned char CmdCalefaccion = 0x00;
    unsigned char CmdTempSalida = 0x00;
    unsigned char CmdTempEntrada = 0x00;
    unsigned char CmdVelRotacion = 0x00;
    unsigned char CmdAccionMecanica = 0x00;
    unsigned char CmdTiempoEnfriamiento = 0x00;
    unsigned char CmdMinExtraSecado = 0x00;
    unsigned char CmdTimeNoTeclado = 0x00;
    unsigned char CmdHabilitarFase = 0x00;
    unsigned char CmdNivelBano = 0x00;
    unsigned char CmdTemperatura = 0x00;
    unsigned char CmdDosificacion = 0x00;
    unsigned char CmdTiempoRotacion = 0x00;
    unsigned char CmdDesague = 0x00;
    unsigned char CmdTiempoCentrifugado = 0x00;
    unsigned char CmdEnfriamiento = 0x00;
    unsigned char CmdPausa = 0x00;
    unsigned char CmdTiempoDosificacion = 0x00;
    unsigned char CmdModoLavadoExtra = 0x00;
    unsigned char CmdTiempoLavadoExtra = 0x00;
    unsigned char CmdModoAclaradoExtra = 0x00;
    unsigned char CmdTiempoAclaradoExtra = 0x00;
    unsigned char CmdModoCentrifugadoExtra = 0x00;
    unsigned char CmdTiempoCentrifugadoExtra = 0x00;




    unsigned char CmdReadStatusSec[5] = {0x02,0x00,CmdNumMaq,0x0a,0x0a};
    unsigned char CmdEditProgramSec[22] = {0x02,0x11,CmdNumMaq,0x51,0x0A,CmdNumProgram,0x00,0x00,CmdTiempoSecado,CmdCalefaccion,CmdTempSalida,CmdTempEntrada,
                                    CmdVelRotacion,CmdAccionMecanica,CmdTiempoEnfriamiento,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
    unsigned char CmdReadProgramSec[6] = {0x02,0x01,CmdNumMaq,0x50,0x0A,CmdNumProgram};
    unsigned char CmdProgramStartSec[6] = {0x02,0x01,CmdNumMaq,0xA7,0x0A,0x55};
    unsigned char CmdAddMinutesSec[6] = {0x02,0x01,CmdNumMaq,0xA8,0x0A,CmdMinExtraSecado};
    unsigned char CmdProgramSelectionSec[11] = {0x02,0x06,CmdNumMaq,0xA6,0x0A,CmdNumProgram,0x00,0x00,0x00,0x00,0x00};
    unsigned char CmdReadPricesSec[6] = {0x02,0x01,CmdNumMaq,0x78,0x0A,CmdNumProgram};
   // unsigned char CmdEditPrices = {0x02,0x0E,CmdNumMaq,0x79,0x0A,CmdNumProgram,};
    unsigned char CmdFreezeKeyboardSec[9] = {0x02,0x04,CmdNumMaq,0x71,0x0A,CmdTimeNoTeclado,0x00,0x00,0x00};
    unsigned char CmdReadInfoSec[5] = {0x02,0x00,CmdNumMaq,0xA4,0x0A};
    unsigned char CmdReadProgramCounterSec[6] = {0x02,0x01,CmdNumMaq, 0x3E,0x0A,CmdNumProgram};
    unsigned char CmdReadAlarmCounterSec[5] = {0x02,0x00,CmdNumMaq,0x3F,0x0A};


    unsigned char CmdReadStatusLav[5] = {0x02,0x00,CmdNumMaq,0x0A,0x00};
    unsigned char CmdReadPhaseLav[7] = {0x02,0x02,CmdNumMaq,0x76,0x00,CmdNumProgram,CmdNumFase};
    unsigned char CmdEditPhaseLav[22] = {0x02,0x11,CmdNumMaq,0x77,0x00,CmdNumProgram,CmdNumFase,CmdHabilitarFase,CmdNivelBano,CmdTemperatura,CmdDosificacion,
                                 CmdAccionMecanica,CmdTiempoRotacion,CmdDesague,CmdTiempoCentrifugado,CmdEnfriamiento,CmdPausa,0x00,0x00,CmdTiempoDosificacion,0x00,0x00};
    unsigned char CmdProgramStartLav[6] = {0x02,0x01,CmdNumMaq,0xA7,0x00,0x55};
    unsigned char CmdProgramSelectionLav[17] = {0x02,0x0C,CmdNumMaq,0xA6,0x00,CmdNumProgram,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
    unsigned char CmdReadExtraOptionLav[5] = {0x02,0x00,CmdNumMaq,0x7A,0x00};
    unsigned char CmdEditExtraOptionLav[17] = {0x02,0x0C,CmdNumMaq,0x7B,0x00,CmdModoLavadoExtra,CmdTiempoLavadoExtra,0x00,0x00,CmdModoAclaradoExtra,CmdTiempoAclaradoExtra,
                                       0x00,0x00,CmdModoCentrifugadoExtra,CmdTiempoCentrifugadoExtra,0x00,0x00};
    unsigned char CmdReadInfoLav[5] = {0x02,0x00,CmdNumMaq,0xA4,0x00};
    unsigned char CmdFreezeKeyboardLav[9] = {0x02,0x04,CmdNumMaq,0x71,0x00,CmdTimeNoTeclado,0x00,0x00,0x00};


    bool EstadoPuerta = false;

};





#endif // C_MAQUINAS_H
