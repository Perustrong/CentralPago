    #ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "ServicioTarjetas/c_functionsk720.h"
#include <QMainWindow>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QPropertyAnimation>
#include <QTimer>
#include <QDebug>
#include <QUrl>
#include <windows.h>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>
#include <QtTest/QTest>
#include <QObject>
#include <QMessageBox>
#include "ServicioMaquinas/c_maquinas.h"
#include "ServicioEfectivo/c_lecturabilletethread.h"
#include "ServicioEfectivo/c_efectivothread.h"
#include "ServicioEfectivo/c_efectivothread2.h"
#include "ServicioDB/c_mysql.h"
#include <ServicioTarjetas/c_tarjetathread.h>
//#include <ServicioImpresion/SSPInclude.h>
#include <ServicioImpresion/c_couponprinter.h>
#include <ServicioImpresion/c_couponprinterthread.h>
#include <ServicioMaquinas/c_lecturamaquinas.h>
#include <crearmaquina.h>
#include <QDateTime>
#include <c_LogFile.h>
#include <ServicioDB/c_LogFileDB.h>
#include <ServicioEfectivo/c_LogFileEfectivo.h>
#include <ServicioImpresion/c_LogFileImpresion.h>
#include <ServicioMaquinas/c_LogFileMaquinas.h>
#include <ServicioTarjetas/c_LogFileTarjetas.h>









namespace Ui {
class MainWindow;
}




class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
     c_EfectivoThread *EfectivoThread;
     c_EfectivoThread2 *EfectivoThread2;
     c_TarjetaThread *TarjetaThread;
     c_CouponPrinterThread *CouponPrinterThread;
     c_lecturamaquinas *LecturaLavadorasThread;
     c_lecturamaquinas *LecturaSecadorasThread;
     c_Maquinas *Lavadora;
     c_Maquinas *Secadora;


signals:

    void PrinterFunction(string function);
    void ActualizacionHandleLecturaLavadoras(HANDLE newhComPort);
    void ActualizacionHandleLecturaSecadoras(HANDLE newhComPort);
    //void RegistroErrores(string errores);
    void TestEstadosLav();
    void ActualizarConfiguracionLav(string);
    void ActualizarConfiguracionSec(string);



private slots:
    void on_Button01_clicked();

    void on_Button02_clicked();

    void on_Button03_clicked();

    void on_B01_Precio_clicked();

    void on_B02_Instrucciones_clicked();

    void on_B03_Tocar_clicked();

    void on_B04_Home_clicked();

    void on_B04_Home_2_clicked();

    void on_B04_Home_3_clicked();

    void on_B04_Home_4_clicked();

    void on_B04_Back_3_clicked();

    void on_B04_Back_4_clicked();

    void on_B09_Lavadora01_toggled(bool checked);

    void on_B09_Lavadora01_clicked(bool checked);

    void on_B11_Lavadora03_toggled(bool checked);

    void on_B09_Lavadora01_clicked();



    void on_B10_Lavadora02_clicked(bool checked);

    void on_B11_Lavadora03_clicked(bool checked);

    void on_B12_Lavadora04_clicked(bool checked);

    void on_B13_Lavadora05_clicked(bool checked);

    void on_B14_Lavadora06_clicked(bool checked);

    void on_B04_Back_2_clicked();

    void on_B04_Back_clicked();

    void on_B05_Lavar_clicked();

    void on_B04_Back_5_clicked();

    void on_B15_Adelante_clicked();

    void on_B15_Adelante_2_clicked();

    void on_B04_Back_6_clicked();

    void on_B15_Adelante_3_clicked();

    void on_B16_MuySucio_clicked();

    void on_B04_Back_7_clicked();

    void on_B15_Adelante_4_clicked();

    void on_B06_Secar_clicked();

    void on_B10_Lavadora02_clicked();

    void on_B11_Lavadora03_clicked();

    void on_B12_Lavadora04_clicked();

    void on_B13_Lavadora05_clicked();

    void on_B14_Lavadora06_clicked();

    void ventana0();

    void ventana4();

    void ventana5();

    void ventana7();

    void ventana9();

    void ventana10();

    void ventana12();

    void on_B17_Sucio_clicked();

    void on_B18_Normal_clicked();

    void on_B19_Delicado_clicked();


    void on_B20_ExtraLavado_clicked(bool checked);

    void on_B21_ExtraAclarado_clicked(bool checked);

    void on_B22_ExtraCentrifugado_clicked(bool checked);



    void on_B08_Tarjeta_clicked();





    void on_Menos_clicked();



    void on_Mas_clicked();

    void on_btnCrearTarjeta_clicked();

    void on_B04_Back_9_clicked();

    void on_B07_Saldo_clicked();

    void on_GuardarFormulario_clicked();

    void on_B04_Back_10_clicked();



    void on_B04_Back_8_clicked();

    void on_B09_Secadora1_clicked();

    void on_B10_Secadora2_clicked();

    void on_B11_Secadora3_clicked();

    void on_B12_Secadora4_clicked();

    void on_B13_Secadora5_clicked();

    void on_B14_Secadora6_clicked();

    void on_B04_Back_13_clicked();

    void on_B15_Adelante_6_clicked();

    void on_B16_Caliente_2_clicked();

    void on_B18_Frio_2_clicked();

    void on_B17_Templado_2_clicked();

    void on_B04_Back_12_clicked();

    void on_B04_Back_11_clicked();

    void on_Mas_2_clicked();

    void on_Menos_2_clicked();

    void on_B15_Adelante_5_clicked();

    void on_B04_Back_14_clicked();

    void on_B04_Back_15_clicked();


    void onLecturaMoneda(float number);

    void onLecturaBillete(float number);

    void on_PagoEfectivo_2_clicked();

    void on_PagoEfectivo_clicked();

    void on_B04_Back_16_clicked();

    void on_PagoTarjeta_2_clicked();

    void on_B04_Back_17_clicked();

    void on_PagoTarjeta_3_clicked();


    void onLecturaTarjeta(float number);




    void on_B04_Back_18_clicked();

    void on_B15_Adelante_7_clicked();

    void on_Menos1_clicked();

    void on_Menos5_clicked();

    void on_Mas1_clicked();

    void on_Mas5_clicked();

    void on_RecargaTarjeta_clicked();

    void on_B04_Back_19_clicked();

    void on_PagoTarjeta_clicked();

    void onEventoImpresora(int evento);

    void onLecturaLavadora(string buffer);
    void onLecturaSecadora(string buffer);
    void onTestEstadosLav();





    void on_pushButton_14_clicked();

    void on_B04_Ajustes_clicked();

    void on_B04_Back_24_clicked();

    void on_B05_Administracion_clicked();

    void on_B06_Clientes_clicked();

    void on_B07_TarifasPromo_clicked();

    void on_IdentificacionTarjeta_clicked();

    void on_GestionTarjetas_clicked();

    void on_TarjetaAdmin_clicked();

    void on_B04_Back_21_clicked();

    void on_B04_Back_20_clicked();

    void on_B04_Back_22_clicked();

    void on_B04_Back_23_clicked();

    void on_B04_Back_25_clicked();



    void on_BtnConfigMaq_clicked();

    void on_B04_Back_27_clicked();

    void on_NuevoCliente_2_clicked();

    void on_B04_Back_28_clicked();

    void on_BtnLavadora_clicked();

    void on_BtnActualizar_clicked();

    void on_BtnAnadirLavadora_clicked();

    void onHandleLavadora(HANDLE);
    void onHandleSecadora(HANDLE);

    void onCrearMaquinaAction(string Action);

    void on_BtnEliminarLavadora_clicked();

    void RegistroErroresLav(string errores);
    void RegistroErroresSec(string errores);

    void on_B04_Back_29_clicked();

    void on_B08_Gestion_clicked();

    void on_B04_Back_26_clicked();


    void onInhabilitaLavadora(unsigned char Lav);
    void onInhabilitaSecadora(unsigned char Sec);

    void ActivarHilosTest();

  //  void on_stackedWidget_currentChanged(int arg1);

  //  void on_stackedWidget_currentChanged(int arg1);

    void on_BtnGuardar_clicked();

    void on_BtnSecadora_clicked();

    void on_B04_Back_30_clicked();

    void on_BtnActualizar_2_clicked();

    void on_BtnGuardar_2_clicked();

    void on_GestionTarjetas_2_clicked();

private:
    Ui::MainWindow *ui;



    int *mump = new int;
    bool extra1 = false;    // extra 1
    bool extra2 = false;    // extra 2
    bool extra3 = false;    // extra 3


    int NumLavadoras = 3;
    int NumSecadoras = 0;
    bool respuesta = false;
    bool PuertaAbierta = true;
    CrearMaquina VentanaCrear;
//    Secadora.set_numTipoMaquina(2);


    c_FunctionsK720 K720_Dispenser;




    QMediaPlayer* player = new QMediaPlayer;
    QVideoWidget* vw = new QVideoWidget;



    c_MySQL BaseDatos;


    int intNuevaTarjeta = 20;
    int intTiempoSecadoExtra = 0;

    float TotalPagoEfectivo = 0;
    float TotalPagoTarjeta = 0;
    float TotalPago = 0;
    int UltimaPagina = 0;

    float SaldoTarjeta = 0;
    float RecargaTarjeta = 0;

    c_LogFileDB LogDB;
    c_LogFileEfectivo LogEfectivo;
    c_LogFileImpresion LogImpresion;
    c_LogFileMaquinas LogMaquinas;
    c_LogFileTarjetas LogTarjetas;



    void set_extra1 (bool e1);
    bool get_extra1 ();

    void set_extra2 (bool o);
    bool get_extra2 ();

    void set_extra3 (bool o);
    bool get_extra3 ();

    void ConectarLavadora();
    void ConectarSecadora();




};





#endif // MAINWINDOW_H
