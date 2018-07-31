#include "01_home.h"
#include "ui_01_home.h"




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QMainWindow::showFullScreen();









        EfectivoThread = new c_EfectivoThread(this);
       connect(EfectivoThread,SIGNAL(LecturaMoneda(float)), this, SLOT(onLecturaMoneda(float)));

       EfectivoThread2 = new c_EfectivoThread2(this);
       connect(EfectivoThread2,SIGNAL(LecturaBillete(float)),this,SLOT(onLecturaBillete(float)));

       TarjetaThread = new c_TarjetaThread(this);
       connect(TarjetaThread,SIGNAL(LecturaTarjeta(float)),this,SLOT(onLecturaTarjeta(float)));

       CouponPrinterThread = new c_CouponPrinterThread(this);
       connect(CouponPrinterThread,SIGNAL(EventoImpresora(int)),this,SLOT(onEventoImpresora(int)));
       connect(this,SIGNAL(PrinterFunction(string)),CouponPrinterThread,SLOT(onPrinterFunction(string)));

       qRegisterMetaType<string>("string");

       LecturaLavadorasThread = new c_lecturamaquinas(this);
       connect(LecturaLavadorasThread,SIGNAL(LecturaMaquina(string)),this,SLOT(onLecturaLavadora(string)));
       connect(this,SIGNAL(ActualizacionHandleLecturaLavadoras(HANDLE)),LecturaLavadorasThread,SLOT(onActualizacionHandle(HANDLE)));

       LecturaSecadorasThread = new c_lecturamaquinas(this);
       connect(LecturaSecadorasThread,SIGNAL(LecturaMaquina(string)),this,SLOT(onLecturaSecadora(string)));
       connect(this, SIGNAL(ActualizacionHandleLecturaSecadoras(HANDLE)),LecturaSecadorasThread,SLOT(onActualizacionHandle(HANDLE)));

       connect(this, SIGNAL(TestEstadosLav()),this,SLOT(onTestEstadosLav()));

       Lavadora = new c_Maquinas(this);
       connect(Lavadora,SIGNAL(HandleLavadora(HANDLE)),this,SLOT(onHandleLavadora(HANDLE)));
       connect(this,SIGNAL(ActualizarConfiguracionLav(string)),Lavadora,SLOT(onActualizarConfiguracionLav(string)));


       Secadora = new c_Maquinas(this);
       connect(Secadora,SIGNAL(HandleSecadora(HANDLE)),this,SLOT(onHandleSecadora(HANDLE)));
       connect(this,SIGNAL(ActualizarConfiguracionSec(string)),Secadora,SLOT(onActualizarConfiguracionSec(string)));

       connect(&VentanaCrear,SIGNAL(CrearMaquinaAction(string)),this,SLOT(onCrearMaquinaAction(string)));

       // Lavadora->start();

       K720_Dispenser.DisableMouth();

     //  CouponPrinterThread->ActiveThread=true;
     //  CouponPrinterThread->run();

       Lavadora->set_numTipoMaquina(1);
       Secadora->set_numTipoMaquina(2);


       // LecturaLavadorasThread->start();




   vw = ui->rep;

    player->setVideoOutput(vw);
    player->setMedia(QUrl::fromLocalFile("C:/Users/Central de Pago/Desktop/Charlotte_Cardin_Like_It_Doesnt_Hurt_Feat_Husser.mp4"));
    //vw->setGeometry(100,100,300,400);
    vw->show();
    player->play();

     qDebug () << player -> state();




     /*db.setHostName("localhost");
     db.setUserName("root");
     db.setPassword("genuix23");
     db.setDatabaseName("base_datos_cp");
     if(db.open()==false)
     {
         QMessageBox::critical(this, "Error de conexión",db.lastError().text());
     }

*/



}



MainWindow::~MainWindow()
{
    delete ui;

}






void MainWindow::on_B01_Precio_clicked()
{
    /*V02_precios *v02 = new V02_precios;

    v02->show();*/


    ui->stackedWidget->setCurrentIndex(1);



}

void MainWindow::on_B02_Instrucciones_clicked()
{
        ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_B03_Tocar_clicked()
{
        emit PrinterFunction("CL");
        ui->stackedWidget->setCurrentIndex(3);
        player->stop();
      //  CouponPrinterThread->start();
        emit PrinterFunction("Funcion de impresora");




    /*V02_precios *v02 = new V02_precios;
    v02->show();  */
}

void MainWindow::on_B04_Home_clicked()
{
        ui->stackedWidget->setCurrentIndex(0);
        player->play();
}

void MainWindow::on_B04_Home_2_clicked()
{
        ui->stackedWidget->setCurrentIndex(0);
        player->play();
}

void MainWindow::on_B04_Home_3_clicked()
{

        ui->stackedWidget->setCurrentIndex(0);
        player->play();

}

void MainWindow::on_B04_Home_4_clicked()
{
         ui->stackedWidget->setCurrentIndex(0);
         player->play();
}

void MainWindow::on_B04_Back_3_clicked()
{
         ui->stackedWidget->setCurrentIndex(0);
         player->play();
}

void MainWindow::on_B04_Back_4_clicked()
{
        ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_B09_Lavadora01_toggled(bool checked)
{
   /* if (ui->B09_Lavadora01->isChecked())
       {
        //ui->B10_Lavadora02->setAttribute(Qt::WA_NoSystemBackground, true);

        ui->B10_Lavadora02->setChecked("Off");

       }
       else
       {
        ui->B10_Lavadora02->setChecked("On");

       }*/

}




void MainWindow::on_B11_Lavadora03_toggled(bool checked)
{


}

void MainWindow::on_B09_Lavadora01_clicked(bool checked)
{


}

void MainWindow::on_B09_Lavadora01_clicked()
{
    Lavadora->set_numTipoMaquina(1);
    Lavadora->set_numMaquina(1);

    Lavadora->set_CmdNumMaq(0x01);


    Lavadora->InfoStatus((unsigned char) Lavadora->get_numMaquina());


    ui->intTamaLavSel2->setText(QString("8 KG"));
    ui->intEfectivoSel2 ->setText(QString::number(Lavadora->get_PreciosEfectivo(PROGRAMA_LIGERO)));
    ui->intTarjetaSel2 ->setText(QString::number(Lavadora->get_PreciosTarjeta(PROGRAMA_LIGERO)));
    ui->intTotalSel2->setText(QString::number(Lavadora->get_PreciosEfectivo(PROGRAMA_LIGERO)));
    ui->intTotalTarSel2->setText(QString::number(Lavadora->get_PreciosEfectivo(PROGRAMA_LIGERO)));

    ui->intTamaLavSel2_2->setText(QString("8 KG"));
    ui->intEfectivoSel2_2 ->setText(QString::number(Lavadora->get_PreciosEfectivo(PROGRAMA_LIGERO)));
    ui->intTarjetaSel2_2 ->setText(QString::number(Lavadora->get_PreciosTarjeta(PROGRAMA_LIGERO)));
    ui->intTotalSel2_2->setText(QString::number(Lavadora->get_PreciosEfectivo(PROGRAMA_LIGERO)));
    ui->intTotalTarSel2_2->setText(QString::number(Lavadora->get_PreciosEfectivo(PROGRAMA_LIGERO)));
    //ui->Seleccion_Maquina->setText(QString("Seleccionada Lavadora Nº 1"));
   // ui->Seleccion_Maquina_2->setText(QString("Seleccionada Lavadora Nº 1"));
   // ui->Seleccion_Maquina_3->setText(QString("Seleccionada Lavadora Nº 1"));

    QPropertyAnimation *animation = new QPropertyAnimation(ui->B09_Lavadora01, "geometry");
    animation->setDuration(1000);
    animation->setStartValue(QRect(50, 560, 250, 250));
    animation->setEndValue(QRect(0, 510, 350, 350));
    animation->setEasingCurve(QEasingCurve::OutCirc);
    animation->start();

    connect(animation, SIGNAL(finished()), this, SLOT(ventana5()));

}


void MainWindow::on_B10_Lavadora02_clicked()
{
    Lavadora->set_numTipoMaquina(1);
    Lavadora->set_numMaquina(2);

    Lavadora->set_CmdNumMaq(0x02);

    ui->intTamaLavSel2->setText(QString("8 KG"));
    ui->intEfectivoSel2 ->setText(QString::number(Lavadora->get_PreciosEfectivo(PROGRAMA_LIGERO)));
    ui->intTarjetaSel2 ->setText(QString::number(Lavadora->get_PreciosTarjeta(PROGRAMA_LIGERO)));
    ui->intTotalSel2->setText(QString::number(Lavadora->get_PreciosEfectivo(PROGRAMA_LIGERO)));
    ui->intTotalTarSel2->setText(QString::number(Lavadora->get_PreciosEfectivo(PROGRAMA_LIGERO)));

    ui->intTamaLavSel2_2->setText(QString("8 KG"));
    ui->intEfectivoSel2_2 ->setText(QString::number(Lavadora->get_PreciosEfectivo(PROGRAMA_LIGERO)));
    ui->intTarjetaSel2_2 ->setText(QString::number(Lavadora->get_PreciosTarjeta(PROGRAMA_LIGERO)));
    ui->intTotalSel2_2->setText(QString::number(Lavadora->get_PreciosEfectivo(PROGRAMA_LIGERO)));
    ui->intTotalTarSel2_2->setText(QString::number(Lavadora->get_PreciosEfectivo(PROGRAMA_LIGERO)));
    //ui->Seleccion_Maquina->setText(QString("Seleccionada Lavadora Nº 2"));
   // ui->Seleccion_Maquina_2->setText(QString("Seleccionada Lavadora Nº 2"));
  //  ui->Seleccion_Maquina_3->setText(QString("Seleccionada Lavadora Nº 2"));

    QPropertyAnimation *animation = new QPropertyAnimation(ui->B10_Lavadora02, "geometry");
    animation->setDuration(1000);
    animation->setStartValue(QRect(350, 560, 250, 250));
    animation->setEndValue(QRect(300, 510, 350, 350));
    animation->setEasingCurve(QEasingCurve::OutElastic);
    animation->start();

    connect(animation, SIGNAL(finished()), this, SLOT(ventana5()));

}


void MainWindow::on_B11_Lavadora03_clicked()
{
    Lavadora->set_numTipoMaquina(1);
    Lavadora->set_numMaquina(3);

    Lavadora->set_CmdNumMaq(0x03);

    ui->intTamaLavSel2->setText(QString("13 KG"));
    ui->intEfectivoSel2 ->setText(QString::number(Lavadora->get_PreciosEfectivo(PROGRAMA_MEDIO)));
    ui->intTarjetaSel2 ->setText(QString::number(Lavadora->get_PreciosTarjeta(PROGRAMA_MEDIO)));
    ui->intTotalSel2->setText(QString::number(Lavadora->get_PreciosEfectivo(PROGRAMA_MEDIO)));
    ui->intTotalTarSel2->setText(QString::number(Lavadora->get_PreciosEfectivo(PROGRAMA_MEDIO)));

    ui->intTamaLavSel2_2->setText(QString("13 KG"));
    ui->intEfectivoSel2_2 ->setText(QString::number(Lavadora->get_PreciosEfectivo(PROGRAMA_MEDIO)));
    ui->intTarjetaSel2_2 ->setText(QString::number(Lavadora->get_PreciosTarjeta(PROGRAMA_MEDIO)));
    ui->intTotalSel2_2->setText(QString::number(Lavadora->get_PreciosEfectivo(PROGRAMA_MEDIO)));
    ui->intTotalTarSel2_2->setText(QString::number(Lavadora->get_PreciosEfectivo(PROGRAMA_MEDIO)));
   // ui->Seleccion_Maquina_3->setText(QString("Seleccionada Lavadora Nº 3"));

    QPropertyAnimation *animation = new QPropertyAnimation(ui->B11_Lavadora03, "geometry");
    animation->setDuration(1000);
    animation->setStartValue(QRect(650, 560, 250, 250));
    animation->setEndValue(QRect(600, 510, 350, 350));
    animation->setEasingCurve(QEasingCurve::InOutBack);
    animation->start();

    connect(animation, SIGNAL(finished()), this, SLOT(ventana5()));
}



void MainWindow::on_B12_Lavadora04_clicked()
{
    Lavadora->set_numTipoMaquina(1);
    Lavadora->set_numMaquina(4);

    Lavadora->set_CmdNumMaq(0x04);

    ui->intTamaLavSel2->setText(QString("13 KG"));
    ui->intEfectivoSel2 ->setText(QString::number(Lavadora->get_PreciosEfectivo(PROGRAMA_MEDIO)));
    ui->intTarjetaSel2 ->setText(QString::number(Lavadora->get_PreciosTarjeta(PROGRAMA_MEDIO)));
    ui->intTotalSel2->setText(QString::number(Lavadora->get_PreciosEfectivo(PROGRAMA_MEDIO)));
    ui->intTotalTarSel2->setText(QString::number(Lavadora->get_PreciosEfectivo(PROGRAMA_MEDIO)));

    ui->intTamaLavSel2_2->setText(QString("13 KG"));
    ui->intEfectivoSel2_2 ->setText(QString::number(Lavadora->get_PreciosEfectivo(PROGRAMA_MEDIO)));
    ui->intTarjetaSel2_2 ->setText(QString::number(Lavadora->get_PreciosTarjeta(PROGRAMA_MEDIO)));
    ui->intTotalSel2_2->setText(QString::number(Lavadora->get_PreciosEfectivo(PROGRAMA_MEDIO)));
    ui->intTotalTarSel2_2->setText(QString::number(Lavadora->get_PreciosEfectivo(PROGRAMA_MEDIO)));
    //ui->Seleccion_Maquina->setText(QString("Seleccionada Lavadora Nº 4"));
  //  ui->Seleccion_Maquina_2->setText(QString("Seleccionada Lavadora Nº 4"));
  //  ui->Seleccion_Maquina_3->setText(QString("Seleccionada Lavadora Nº 4"));

    QPropertyAnimation *animation = new QPropertyAnimation(ui->B12_Lavadora04, "geometry");
    animation->setDuration(1000);
    animation->setStartValue(QRect(950, 560, 250, 250));
    animation->setEndValue(QRect(900, 510, 350, 350));
    animation->setEasingCurve(QEasingCurve::OutCirc);
    animation->start();

    connect(animation, SIGNAL(finished()), this, SLOT(ventana5()));
}


void MainWindow::on_B13_Lavadora05_clicked()
{
    Lavadora->set_numTipoMaquina(1);
    Lavadora->set_numMaquina(5);


    Lavadora->set_CmdNumMaq(0x05);

    ui->intTamaLavSel2->setText(QString("17 KG"));
    ui->intEfectivoSel2 ->setText(QString::number(Lavadora->get_PreciosEfectivo(PROGRAMA_PESADO)));
    ui->intTarjetaSel2 ->setText(QString::number(Lavadora->get_PreciosTarjeta(PROGRAMA_PESADO)));
    ui->intTotalSel2->setText(QString::number(Lavadora->get_PreciosEfectivo(PROGRAMA_PESADO)));
    ui->intTotalTarSel2->setText(QString::number(Lavadora->get_PreciosEfectivo(PROGRAMA_PESADO)));

    ui->intTamaLavSel2_2->setText(QString("17 KG"));
    ui->intEfectivoSel2_2 ->setText(QString::number(Lavadora->get_PreciosEfectivo(PROGRAMA_PESADO)));
    ui->intTarjetaSel2_2 ->setText(QString::number(Lavadora->get_PreciosTarjeta(PROGRAMA_PESADO)));
    ui->intTotalSel2_2->setText(QString::number(Lavadora->get_PreciosEfectivo(PROGRAMA_PESADO)));
    ui->intTotalTarSel2_2->setText(QString::number(Lavadora->get_PreciosEfectivo(PROGRAMA_PESADO)));


    //ui->Seleccion_Maquina->setText(QString("Seleccionada Lavadora Nº 5"));
  //  ui->Seleccion_Maquina_2->setText(QString("Seleccionada Lavadora Nº 5"));
  //  ui->Seleccion_Maquina_3->setText(QString("Seleccionada Lavadora Nº 5"));

    QPropertyAnimation *animation = new QPropertyAnimation(ui->B13_Lavadora05, "geometry");
    animation->setDuration(1000);
    animation->setStartValue(QRect(1250, 560, 250, 250));
    animation->setEndValue(QRect(1200, 510, 350, 350));
    animation->setEasingCurve(QEasingCurve::InElastic);
    animation->start();

    connect(animation, SIGNAL(finished()), this, SLOT(ventana5()));
}


void MainWindow::on_B14_Lavadora06_clicked()
{
    Lavadora->set_numTipoMaquina(1);
    Lavadora->set_numMaquina(6);

    Lavadora->set_CmdNumMaq(0x06);


    ui->intTamaLavSel2->setText(QString("17 KG"));
    ui->intEfectivoSel2 ->setText(QString::number(Lavadora->get_PreciosEfectivo(PROGRAMA_PESADO)));
    ui->intTarjetaSel2 ->setText(QString::number(Lavadora->get_PreciosTarjeta(PROGRAMA_PESADO)));
    ui->intTotalSel2->setText(QString::number(Lavadora->get_PreciosEfectivo(PROGRAMA_PESADO)));
    ui->intTotalTarSel2->setText(QString::number(Lavadora->get_PreciosEfectivo(PROGRAMA_PESADO)));

    ui->intTamaLavSel2_2->setText(QString("17 KG"));
    ui->intEfectivoSel2_2 ->setText(QString::number(Lavadora->get_PreciosEfectivo(PROGRAMA_PESADO)));
    ui->intTarjetaSel2_2 ->setText(QString::number(Lavadora->get_PreciosTarjeta(PROGRAMA_PESADO)));
    ui->intTotalSel2_2->setText(QString::number(Lavadora->get_PreciosEfectivo(PROGRAMA_PESADO)));
    ui->intTotalTarSel2_2->setText(QString::number(Lavadora->get_PreciosEfectivo(PROGRAMA_PESADO)));
    //ui->Seleccion_Maquina->setText(QString("Seleccionada Lavadora Nº 6"));
   // ui->Seleccion_Maquina_2->setText(QString("Seleccionada Lavadora Nº 6"));
  //  ui->Seleccion_Maquina_3->setText(QString("Seleccionada Lavadora Nº 6"));

    QPropertyAnimation *animation = new QPropertyAnimation(ui->B14_Lavadora06, "geometry");
    animation->setDuration(1000);
    animation->setStartValue(QRect(1550, 560, 250, 250));
    animation->setEndValue(QRect(1500, 510, 350, 350));
    animation->setEasingCurve(QEasingCurve::OutElastic);
    animation->start();

    connect(animation, SIGNAL(finished()), this, SLOT(ventana5()));
}


void MainWindow::ventana4()
{
 ui->stackedWidget->setCurrentIndex(4);
 ui->B05_Lavar->setGeometry(420, 590, 200, 190);
}





void MainWindow::ventana5()
{

 ui->stackedWidget->setCurrentIndex(5);
 ui->B09_Lavadora01->setGeometry(50, 560, 250, 250);
 ui->B10_Lavadora02->setGeometry(350, 560, 250, 250);
 ui->B11_Lavadora03->setGeometry(650, 560, 250, 250);
 ui->B12_Lavadora04->setGeometry(950, 560, 250, 250);
 ui->B13_Lavadora05->setGeometry(1250, 560, 250, 250);
 ui->B14_Lavadora06->setGeometry(1550, 560, 250, 250);

 Lavadora->start();
 //emit EstadoPuertaLav();
 //connect(ui->stackedWidget, SIGNAL(currentChanged(int==5)),this,SLOT(onEstadoPuertaLav()));


}



void MainWindow::ventana7()
{
 ui->stackedWidget->setCurrentIndex(7);
 ui->B16_MuySucio->setGeometry(420, 590, 200, 190);
 ui->B17_Sucio->setGeometry(720, 590, 200, 190);
 ui->B18_Normal->setGeometry(1020, 590, 200, 190);
 ui->B19_Delicado->setGeometry(1320, 590, 200, 190);

}
void MainWindow::ventana9()
{
 ui->stackedWidget->setCurrentIndex(9);
 ui->B09_Secadora1->setGeometry(50, 560, 250, 250);
 ui->B10_Secadora2->setGeometry(350, 560, 250, 250);
 ui->B11_Secadora3->setGeometry(650, 560, 250, 250);
 ui->B12_Secadora4->setGeometry(950, 560, 250, 250);
 ui->B13_Secadora5->setGeometry(1250, 560, 250, 250);
 ui->B14_Secadora6->setGeometry(1550, 560, 250, 250);
}
void MainWindow::ventana10()
{
 ui->stackedWidget->setCurrentIndex(10);
 ui->B09_Secadora1->setGeometry(50, 560, 250, 250);
 ui->B10_Secadora2->setGeometry(350, 560, 250, 250);
 ui->B11_Secadora3->setGeometry(650, 560, 250, 250);
 ui->B12_Secadora4->setGeometry(950, 560, 250, 250);
 ui->B13_Secadora5->setGeometry(1250, 560, 250, 250);
 ui->B14_Secadora6->setGeometry(1550, 560, 250, 250);

 Secadora->start();
}

void MainWindow::ventana12()
{
 ui->stackedWidget->setCurrentIndex(12);
 ui->B16_Caliente_2->setGeometry(570, 590, 180, 180);
 ui->B17_Templado_2->setGeometry(870, 590, 180, 180);
 ui->B18_Frio_2->setGeometry(1170, 590, 180, 180);


}




void MainWindow::on_B10_Lavadora02_clicked(bool checked)
{
    if (checked)
           {
            ui->B09_Lavadora01->setChecked(false);
            ui->B11_Lavadora03->setChecked(false);
            ui->B12_Lavadora04->setChecked(false);
            ui->B13_Lavadora05->setChecked(false);
            ui->B14_Lavadora06->setChecked(false);
           }
}

void MainWindow::on_B11_Lavadora03_clicked(bool checked)
{
    if (checked)
           {
            ui->B09_Lavadora01->setChecked(false);
            ui->B10_Lavadora02->setChecked(false);
            ui->B12_Lavadora04->setChecked(false);
            ui->B13_Lavadora05->setChecked(false);
            ui->B14_Lavadora06->setChecked(false);
           }
}

void MainWindow::on_B12_Lavadora04_clicked(bool checked)
{
    if (checked)
           {
            ui->B09_Lavadora01->setChecked(false);
            ui->B10_Lavadora02->setChecked(false);
            ui->B11_Lavadora03->setChecked(false);
            ui->B13_Lavadora05->setChecked(false);
            ui->B14_Lavadora06->setChecked(false);
           }

}

void MainWindow::on_B13_Lavadora05_clicked(bool checked)
{
    if (checked)
           {
            ui->B09_Lavadora01->setChecked(false);
            ui->B10_Lavadora02->setChecked(false);
            ui->B11_Lavadora03->setChecked(false);
            ui->B12_Lavadora04->setChecked(false);
            ui->B14_Lavadora06->setChecked(false);
           }

}

void MainWindow::on_B14_Lavadora06_clicked(bool checked)
{
    if (checked)
           {
            ui->B09_Lavadora01->setChecked(false);
            ui->B10_Lavadora02->setChecked(false);
            ui->B11_Lavadora03->setChecked(false);
            ui->B12_Lavadora04->setChecked(false);
            ui->B13_Lavadora05->setChecked(false);
           }


}

void MainWindow::on_B04_Back_2_clicked()
{
        ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_B04_Back_clicked()
{
        ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_B05_Lavar_clicked()
{
    Lavadora->set_numTipoMaquina(1);

    //emit TestEstadosLav();
    Lavadora->SlotHilo();



    QPropertyAnimation *animation = new QPropertyAnimation(ui->B05_Lavar, "geometry");
    animation->setDuration(1000);
    animation->setStartValue(QRect(420, 590, 200, 190));
    animation->setEndValue(QRect(370, 540, 300, 290));
    animation->setEasingCurve(QEasingCurve::OutCirc);
    animation->start();

    connect(animation, SIGNAL(finished()), this, SLOT(ventana4()));




}

void MainWindow::on_B04_Back_5_clicked()
{
        ui->stackedWidget->setCurrentIndex(14);
}

void MainWindow::on_B15_Adelante_clicked()
{
        ui->stackedWidget->setCurrentIndex(5);
}

void MainWindow::on_B15_Adelante_2_clicked()
{
        ui->stackedWidget->setCurrentIndex(6);
}

void MainWindow::on_B04_Back_6_clicked()
{
        ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_B15_Adelante_3_clicked()
{
        ui->stackedWidget->setCurrentIndex(4);
        Lavadora->terminate();
}




void MainWindow::on_B04_Back_7_clicked()
{
        ui->stackedWidget->setCurrentIndex(6);
}

void MainWindow::on_B15_Adelante_4_clicked()
{
    float LavadoEfectivo;
    float LavadoTarjeta;
    float TotalEfectivo;
    float TotalTarjeta;








        ui->stackedWidget->setCurrentIndex(8);
        if(get_extra1() == false && get_extra2() == false && get_extra3() == false)
        {
            Lavadora->set_numExtras(0);


        }
        if(get_extra1() == false && get_extra2() == false && get_extra3() == true)
        {
            Lavadora->set_numExtras(3);
            Lavadora->set_CmdNumProgram(((unsigned char)(Lavadora->get_numMaquina()+16)));
            printf("Unsigned lavadora get maq = %x", (unsigned char)(Lavadora->get_numMaquina()));
            printf("Unsigned lavadora get maq + 16 = %x", (unsigned char)(Lavadora->get_numMaquina()+16));
            printf("Unsigned lavadora get maq + 16 - 0 = %x", ((unsigned char)(Lavadora->get_numMaquina()+16))-'0');
        }
        if(get_extra1() == false && get_extra2() == true && get_extra3() == false)
        {
            Lavadora->set_numExtras(2);
            Lavadora->set_CmdNumProgram(((unsigned char)(Lavadora->get_numPrograma()+8)));
        }
        if(get_extra1() == false && get_extra2() == true && get_extra3() == true)
        {
            Lavadora->set_numExtras(6);
            Lavadora->set_CmdNumProgram(((unsigned char)(Lavadora->get_numPrograma()+24)));
        }
        if(get_extra1() == true && get_extra2() == false && get_extra3() == false)
        {
            Lavadora->set_numExtras(1);
            Lavadora->set_CmdNumProgram(((unsigned char)(Lavadora->get_numPrograma()+4)));
        }
        if(get_extra1() == true && get_extra2() == false && get_extra3() == true)
        {
            Lavadora->set_numExtras(5);
            Lavadora->set_CmdNumProgram(((unsigned char)(Lavadora->get_numPrograma()+20)));
        }
        if(get_extra1() == true && get_extra2() == true && get_extra3() == false)
        {
            Lavadora->set_numExtras(4);
            Lavadora->set_CmdNumProgram(((unsigned char)(Lavadora->get_numPrograma()+12)));
        }
        if(get_extra1() == true && get_extra2() == true && get_extra3() == true)
        {
            Lavadora->set_numExtras(7);
            Lavadora->set_CmdNumProgram(((unsigned char)(Lavadora->get_numPrograma()+28)));
        }

        string EnvioAux ="ALE";
        char AuxEx = Lavadora->get_numExtras();
        AuxEx = (AuxEx+'0');
        EnvioAux+=AuxEx;
        emit PrinterFunction(EnvioAux);


        AuxEx = Lavadora->get_numMaquina();
        EnvioAux = "ALL",(AuxEx+'0');

        cout << "Numero de Maquina"<<AuxEx;
        printf("%x",AuxEx);
        AuxEx = (AuxEx+'0');
        EnvioAux+=AuxEx;
       // strcat(EnvioAux,AuxEx);
        printf("%x",EnvioAux[3]);
        cout<< "cout EnvioAux"<<EnvioAux<<endl;
        emit PrinterFunction(EnvioAux);

        EnvioAux = "ALINI";
        emit PrinterFunction(EnvioAux);

        EnvioAux = "AI";
        emit PrinterFunction(EnvioAux);




        cout<<"El valor de extras es = "<<Lavadora->get_numExtras()<<endl<< "El valor de los extras son. EXTRA1 = "<<get_extra1()<<" EXTRA2 = "<<get_extra2()<<"Extra3 = "<<get_extra3()<<endl;

        switch (Lavadora->get_numMaquina()) {
        case 1:

            switch (Lavadora->get_numPrograma()) {
            case 1:
                ui->Resumen_Lavado->setText("Lavadora número "+(QString::number(Lavadora->get_numMaquina()))+
                                            "<br> Programa: Muy Sucio"+"<br>  Precio:"+(QString::number(Lavadora->get_PreciosEfectivo(PROGRAMA_SECADO))));
                ui->Resumen_Lavado_Tarjeta->setText("Lavadora número "+(QString::number(Lavadora->get_numMaquina()))+
                                            "<br> Programa: Muy Sucio"+"<br>  Precio:"+(QString::number(Lavadora->get_PreciosTarjeta(PROGRAMA_LIGERO))));
                LavadoEfectivo = Lavadora->get_PreciosEfectivo(PROGRAMA_LIGERO);
                LavadoTarjeta = Lavadora->get_PreciosTarjeta(PROGRAMA_LIGERO);
                break;
            case 2:
                ui->Resumen_Lavado->setText("Lavadora número "+(QString::number(Lavadora->get_numMaquina()))+
                                            "<br> Programa: Sucio"+"<br>  Precio:"+(QString::number(Lavadora->get_PreciosEfectivo(PROGRAMA_LIGERO))));
                ui->Resumen_Lavado_Tarjeta->setText("Lavadora número "+(QString::number(Lavadora->get_numMaquina()))+
                                            "<br> Programa: Sucio"+"<br>  Precio:"+(QString::number(Lavadora->get_PreciosTarjeta(PROGRAMA_LIGERO))));
                LavadoEfectivo = Lavadora->get_PreciosEfectivo(PROGRAMA_LIGERO);
                LavadoTarjeta = Lavadora->get_PreciosTarjeta(PROGRAMA_LIGERO);
                break;
            case 3:
                ui->Resumen_Lavado->setText("Lavadora número "+(QString::number(Lavadora->get_numMaquina()))+
                                            "<br> Programa: Normal"+"<br>  Precio:"+(QString::number(Lavadora->get_PreciosEfectivo(PROGRAMA_LIGERO))));
                ui->Resumen_Lavado_Tarjeta->setText("Lavadora número "+(QString::number(Lavadora->get_numMaquina()))+
                                            "<br> Programa: Normal"+"<br>  Precio:"+(QString::number(Lavadora->get_PreciosTarjeta(PROGRAMA_LIGERO))));
                LavadoEfectivo = Lavadora->get_PreciosEfectivo(PROGRAMA_LIGERO);
                LavadoTarjeta = Lavadora->get_PreciosTarjeta(PROGRAMA_LIGERO);
                break;
            case 4:
                ui->Resumen_Lavado->setText("Lavadora número "+(QString::number(Lavadora->get_numMaquina()))+
                                            "<br> Programa: Delicado"+"<br>  Precio:"+(QString::number(Lavadora->get_PreciosEfectivo(PROGRAMA_LIGERO))));
                ui->Resumen_Lavado_Tarjeta->setText("Lavadora número "+(QString::number(Lavadora->get_numMaquina()))+
                                            "<br> Programa: Delicado"+"<br>  Precio:"+(QString::number(Lavadora->get_PreciosTarjeta(PROGRAMA_LIGERO))));
                LavadoEfectivo = Lavadora->get_PreciosEfectivo(PROGRAMA_LIGERO);
                LavadoTarjeta = Lavadora->get_PreciosTarjeta(PROGRAMA_LIGERO);
                break;
            default:
                break;
            }


            break;
        case 2:
            switch (Lavadora->get_numPrograma()) {
            case 1:
                ui->Resumen_Lavado->setText("Lavadora número "+(QString::number(Lavadora->get_numMaquina()))+
                                            "<br> Programa: Muy Sucio"+"<br>  Precio:"+(QString::number(Lavadora->get_PreciosEfectivo(PROGRAMA_LIGERO))));
                ui->Resumen_Lavado_Tarjeta->setText("Lavadora número "+(QString::number(Lavadora->get_numMaquina()))+
                                            "<br> Programa: Muy Sucio"+"<br>  Precio:"+(QString::number(Lavadora->get_PreciosTarjeta(PROGRAMA_LIGERO))));
                LavadoEfectivo = Lavadora->get_PreciosEfectivo(PROGRAMA_LIGERO);
                LavadoTarjeta = Lavadora->get_PreciosTarjeta(PROGRAMA_LIGERO);
                break;
            case 2:
                ui->Resumen_Lavado->setText("Lavadora número "+(QString::number(Lavadora->get_numMaquina()))+
                                            "<br> Programa: Sucio"+"<br>  Precio:"+(QString::number(Lavadora->get_PreciosEfectivo(PROGRAMA_LIGERO))));
                ui->Resumen_Lavado_Tarjeta->setText("Lavadora número "+(QString::number(Lavadora->get_numMaquina()))+
                                            "<br> Programa: Sucio"+"<br>  Precio:"+(QString::number(Lavadora->get_PreciosTarjeta(PROGRAMA_LIGERO))));
                LavadoEfectivo = Lavadora->get_PreciosEfectivo(PROGRAMA_LIGERO);
                LavadoTarjeta = Lavadora->get_PreciosTarjeta(PROGRAMA_LIGERO);
                break;
            case 3:
                ui->Resumen_Lavado->setText("Lavadora número "+(QString::number(Lavadora->get_numMaquina()))+
                                            "<br> Programa: Normal"+"<br>  Precio:"+(QString::number(Lavadora->get_PreciosEfectivo(PROGRAMA_LIGERO))));
                ui->Resumen_Lavado_Tarjeta->setText("Lavadora número "+(QString::number(Lavadora->get_numMaquina()))+
                                            "<br> Programa: Normal"+"<br>  Precio:"+(QString::number(Lavadora->get_PreciosTarjeta(PROGRAMA_LIGERO))));
                LavadoEfectivo = Lavadora->get_PreciosEfectivo(PROGRAMA_LIGERO);
                LavadoTarjeta = Lavadora->get_PreciosTarjeta(PROGRAMA_LIGERO);
                break;
            case 4:
                ui->Resumen_Lavado->setText("Lavadora número "+(QString::number(Lavadora->get_numMaquina()))+
                                            "<br> Programa: Delicado"+"<br>  Precio:"+(QString::number(Lavadora->get_PreciosEfectivo(PROGRAMA_LIGERO))));
                ui->Resumen_Lavado_Tarjeta->setText("Lavadora número "+(QString::number(Lavadora->get_numMaquina()))+
                                            "<br> Programa: Delicado"+"<br>  Precio:"+(QString::number(Lavadora->get_PreciosTarjeta(PROGRAMA_LIGERO))));
                LavadoEfectivo = Lavadora->get_PreciosEfectivo(PROGRAMA_LIGERO);
                LavadoTarjeta = Lavadora->get_PreciosTarjeta(PROGRAMA_LIGERO);
                break;
            default:
                break;
            }
            //ui->Resumen_Lavado->setText("Lavadora número "+(QString::number(Lavadora->get_numMaquina()))+" seleccionada. Precio: "+(QString::number(Lavadora->get_PreciosEfectivo(PROGRAMA_LIGERO))));
            break;
        case 3:
            switch (Lavadora->get_numPrograma()) {
            case 1:
                ui->Resumen_Lavado->setText("Lavadora número "+(QString::number(Lavadora->get_numMaquina()))+
                                            "<br> Programa: Muy Sucio"+"<br>  Precio:"+(QString::number(Lavadora->get_PreciosEfectivo(PROGRAMA_MEDIO))));
                ui->Resumen_Lavado_Tarjeta->setText("Lavadora número "+(QString::number(Lavadora->get_numMaquina()))+
                                            "<br> Programa: Muy Sucio"+"<br>  Precio:"+(QString::number(Lavadora->get_PreciosTarjeta(PROGRAMA_MEDIO))));
                LavadoEfectivo = Lavadora->get_PreciosEfectivo(PROGRAMA_MEDIO);
                LavadoTarjeta = Lavadora->get_PreciosTarjeta(PROGRAMA_MEDIO);
                break;
            case 2:
                ui->Resumen_Lavado->setText("Lavadora número "+(QString::number(Lavadora->get_numMaquina()))+
                                            "<br> Programa: Sucio"+"<br>  Precio:"+(QString::number(Lavadora->get_PreciosEfectivo(PROGRAMA_MEDIO))));
                ui->Resumen_Lavado_Tarjeta->setText("Lavadora número "+(QString::number(Lavadora->get_numMaquina()))+
                                            "<br> Programa: Sucio"+"<br>  Precio:"+(QString::number(Lavadora->get_PreciosTarjeta(PROGRAMA_MEDIO))));
                LavadoEfectivo = Lavadora->get_PreciosEfectivo(PROGRAMA_MEDIO);
                LavadoTarjeta = Lavadora->get_PreciosTarjeta(PROGRAMA_MEDIO);
                break;
            case 3:
                ui->Resumen_Lavado->setText("Lavadora número "+(QString::number(Lavadora->get_numMaquina()))+
                                            "<br> Programa: Normal"+"<br>  Precio:"+(QString::number(Lavadora->get_PreciosEfectivo(PROGRAMA_MEDIO))));
                ui->Resumen_Lavado_Tarjeta->setText("Lavadora número "+(QString::number(Lavadora->get_numMaquina()))+
                                            "<br> Programa: Normal"+"<br>  Precio:"+(QString::number(Lavadora->get_PreciosTarjeta(PROGRAMA_MEDIO))));
                LavadoEfectivo = Lavadora->get_PreciosEfectivo(PROGRAMA_MEDIO);
                LavadoTarjeta = Lavadora->get_PreciosTarjeta(PROGRAMA_MEDIO);
                break;
            case 4:
                ui->Resumen_Lavado->setText("Lavadora número "+(QString::number(Lavadora->get_numMaquina()))+
                                            "<br> Programa: Delicado"+"<br>  Precio:"+(QString::number(Lavadora->get_PreciosEfectivo(PROGRAMA_MEDIO))));
                ui->Resumen_Lavado_Tarjeta->setText("Lavadora número "+(QString::number(Lavadora->get_numMaquina()))+
                                            "<br> Programa: Delicado"+"<br>  Precio:"+(QString::number(Lavadora->get_PreciosTarjeta(PROGRAMA_MEDIO))));
                LavadoEfectivo = Lavadora->get_PreciosEfectivo(PROGRAMA_MEDIO);
                LavadoTarjeta = Lavadora->get_PreciosTarjeta(PROGRAMA_MEDIO);
                break;
            }
            //ui->Resumen_Lavado->setText("Lavadora número "+(QString::number(Lavadora->get_numMaquina()))+" seleccionada. Precio: "+(QString::number(Lavadora->get_PreciosEfectivo(PROGRAMA_MEDIO))));
            break;
        case 4:

            switch (Lavadora->get_numPrograma()) {
            case 1:
                ui->Resumen_Lavado->setText("Lavadora número "+(QString::number(Lavadora->get_numMaquina()))+
                                            "<br> Programa: Muy Sucio"+"<br>  Precio:"+(QString::number(Lavadora->get_PreciosEfectivo(PROGRAMA_MEDIO))));
                ui->Resumen_Lavado_Tarjeta->setText("Lavadora número "+(QString::number(Lavadora->get_numMaquina()))+
                                            "<br> Programa: Muy Sucio"+"<br>  Precio:"+(QString::number(Lavadora->get_PreciosTarjeta(PROGRAMA_MEDIO))));
                LavadoEfectivo = Lavadora->get_PreciosEfectivo(PROGRAMA_MEDIO);
                LavadoTarjeta = Lavadora->get_PreciosTarjeta(PROGRAMA_MEDIO);
                break;
            case 2:
                ui->Resumen_Lavado->setText("Lavadora número "+(QString::number(Lavadora->get_numMaquina()))+
                                            "<br> Programa: Sucio"+"<br>  Precio:"+(QString::number(Lavadora->get_PreciosEfectivo(PROGRAMA_MEDIO))));
                ui->Resumen_Lavado_Tarjeta->setText("Lavadora número "+(QString::number(Lavadora->get_numMaquina()))+
                                            "<br> Programa: Sucio"+"<br>  Precio:"+(QString::number(Lavadora->get_PreciosTarjeta(PROGRAMA_MEDIO))));
                LavadoEfectivo = Lavadora->get_PreciosEfectivo(PROGRAMA_MEDIO);
                LavadoTarjeta = Lavadora->get_PreciosTarjeta(PROGRAMA_MEDIO);
                break;
            case 3:
                ui->Resumen_Lavado->setText("Lavadora número "+(QString::number(Lavadora->get_numMaquina()))+
                                            "<br> Programa: Normal"+"<br>  Precio:"+(QString::number(Lavadora->get_PreciosEfectivo(PROGRAMA_MEDIO))));
                ui->Resumen_Lavado_Tarjeta->setText("Lavadora número "+(QString::number(Lavadora->get_numMaquina()))+
                                            "<br> Programa: Normal"+"<br>  Precio:"+(QString::number(Lavadora->get_PreciosTarjeta(PROGRAMA_MEDIO))));
                LavadoEfectivo = Lavadora->get_PreciosEfectivo(PROGRAMA_MEDIO);
                LavadoTarjeta = Lavadora->get_PreciosTarjeta(PROGRAMA_MEDIO);
                break;
            case 4:
                ui->Resumen_Lavado->setText("Lavadora número "+(QString::number(Lavadora->get_numMaquina()))+
                                            "<br> Programa: Delicado"+"<br>  Precio:"+(QString::number(Lavadora->get_PreciosEfectivo(PROGRAMA_MEDIO))));
                ui->Resumen_Lavado_Tarjeta->setText("Lavadora número "+(QString::number(Lavadora->get_numMaquina()))+
                                            "<br> Programa: Delicado"+"<br>  Precio:"+(QString::number(Lavadora->get_PreciosTarjeta(PROGRAMA_MEDIO))));
                LavadoEfectivo = Lavadora->get_PreciosEfectivo(PROGRAMA_MEDIO);
                LavadoTarjeta = Lavadora->get_PreciosTarjeta(PROGRAMA_MEDIO);
                break;
            }
           // ui->Resumen_Lavado->setText("Lavadora número "+(QString::number(Lavadora->get_numMaquina()))+" seleccionada. Precio: "+(QString::number(Lavadora->get_PreciosEfectivo(PROGRAMA_MEDIO))));
            break;
        case 5:

            switch (Lavadora->get_numPrograma()) {
            case 1:
                ui->Resumen_Lavado->setText("Lavadora número "+(QString::number(Lavadora->get_numMaquina()))+
                                            "<br> Programa: Muy Sucio"+"<br>  Precio:"+(QString::number(Lavadora->get_PreciosEfectivo(PROGRAMA_PESADO))));
                ui->Resumen_Lavado_Tarjeta->setText("Lavadora número "+(QString::number(Lavadora->get_numMaquina()))+
                                            "<br> Programa: Muy Sucio"+"<br>  Precio:"+(QString::number(Lavadora->get_PreciosTarjeta(PROGRAMA_PESADO))));
                LavadoEfectivo = Lavadora->get_PreciosEfectivo(PROGRAMA_PESADO);
                LavadoTarjeta = Lavadora->get_PreciosTarjeta(PROGRAMA_PESADO);
                break;
            case 2:
                ui->Resumen_Lavado->setText("Lavadora número "+(QString::number(Lavadora->get_numMaquina()))+
                                            "<br> Programa: Sucio"+"<br>  Precio:"+(QString::number(Lavadora->get_PreciosEfectivo(PROGRAMA_PESADO))));
                ui->Resumen_Lavado_Tarjeta->setText("Lavadora número "+(QString::number(Lavadora->get_numMaquina()))+
                                            "<br> Programa: Sucio"+"<br>  Precio:"+(QString::number(Lavadora->get_PreciosTarjeta(PROGRAMA_PESADO))));
                LavadoEfectivo = Lavadora->get_PreciosEfectivo(PROGRAMA_PESADO);
                LavadoTarjeta = Lavadora->get_PreciosTarjeta(PROGRAMA_PESADO);
                break;
            case 3:
                ui->Resumen_Lavado->setText("Lavadora número "+(QString::number(Lavadora->get_numMaquina()))+
                                            "<br> Programa: Normal"+"<br>  Precio:"+(QString::number(Lavadora->get_PreciosEfectivo(PROGRAMA_PESADO))));
                ui->Resumen_Lavado_Tarjeta->setText("Lavadora número "+(QString::number(Lavadora->get_numMaquina()))+
                                            "<br> Programa: Normal"+"<br>  Precio:"+(QString::number(Lavadora->get_PreciosTarjeta(PROGRAMA_PESADO))));
                LavadoEfectivo = Lavadora->get_PreciosEfectivo(PROGRAMA_PESADO);
                LavadoTarjeta = Lavadora->get_PreciosTarjeta(PROGRAMA_PESADO);
                break;
            case 4:
                ui->Resumen_Lavado->setText("Lavadora número "+(QString::number(Lavadora->get_numMaquina()))+
                                            "<br> Programa: Delicado"+"<br>  Precio:"+(QString::number(Lavadora->get_PreciosEfectivo(PROGRAMA_PESADO))));
                ui->Resumen_Lavado_Tarjeta->setText("Lavadora número "+(QString::number(Lavadora->get_numMaquina()))+
                                            "<br> Programa: Delicado"+"<br>  Precio:"+(QString::number(Lavadora->get_PreciosTarjeta(PROGRAMA_PESADO))));
                LavadoEfectivo = Lavadora->get_PreciosEfectivo(PROGRAMA_PESADO);
                LavadoTarjeta = Lavadora->get_PreciosTarjeta(PROGRAMA_PESADO);
                break;
            }

            //ui->Resumen_Lavado->setText("Lavadora número "+(QString::number(Lavadora->get_numMaquina()))+" seleccionada. Precio: "+(QString::number(Lavadora->get_PreciosEfectivo(PROGRAMA_PESADO))));
            break;
        case 6:
            switch (Lavadora->get_numPrograma()) {
            case 1:
                ui->Resumen_Lavado->setText("Lavadora número "+(QString::number(Lavadora->get_numMaquina()))+
                                            "<br> Programa: Muy Sucio"+"<br>  Precio:"+(QString::number(Lavadora->get_PreciosEfectivo(PROGRAMA_PESADO))));
                ui->Resumen_Lavado_Tarjeta->setText("Lavadora número "+(QString::number(Lavadora->get_numMaquina()))+
                                            "<br> Programa: Muy Sucio"+"<br>  Precio:"+(QString::number(Lavadora->get_PreciosTarjeta(PROGRAMA_PESADO))));
                LavadoEfectivo = Lavadora->get_PreciosEfectivo(PROGRAMA_PESADO);
                LavadoTarjeta = Lavadora->get_PreciosTarjeta(PROGRAMA_PESADO);
                break;
            case 2:
                ui->Resumen_Lavado->setText("Lavadora número "+(QString::number(Lavadora->get_numMaquina()))+
                                            "<br> Programa: Sucio"+"<br>  Precio:"+(QString::number(Lavadora->get_PreciosEfectivo(PROGRAMA_PESADO))));
                ui->Resumen_Lavado_Tarjeta->setText("Lavadora número "+(QString::number(Lavadora->get_numMaquina()))+
                                            "<br> Programa: Sucio"+"<br>  Precio:"+(QString::number(Lavadora->get_PreciosTarjeta(PROGRAMA_PESADO))));
                LavadoEfectivo = Lavadora->get_PreciosEfectivo(PROGRAMA_PESADO);
                LavadoTarjeta = Lavadora->get_PreciosTarjeta(PROGRAMA_PESADO);
                break;
            case 3:
                ui->Resumen_Lavado->setText("Lavadora número "+(QString::number(Lavadora->get_numMaquina()))+
                                            "<br> Programa: Normal"+"<br>  Precio:"+(QString::number(Lavadora->get_PreciosEfectivo(PROGRAMA_PESADO))));
                ui->Resumen_Lavado_Tarjeta->setText("Lavadora número "+(QString::number(Lavadora->get_numMaquina()))+
                                            "<br> Programa: Normal"+"<br>  Precio:"+(QString::number(Lavadora->get_PreciosTarjeta(PROGRAMA_PESADO))));
                LavadoEfectivo = Lavadora->get_PreciosEfectivo(PROGRAMA_PESADO);
                LavadoTarjeta = Lavadora->get_PreciosTarjeta(PROGRAMA_PESADO);
                break;
            case 4:
                ui->Resumen_Lavado->setText("Lavadora número "+(QString::number(Lavadora->get_numMaquina()))+
                                            "<br> Programa: Delicado"+" <br> Precio:"+(QString::number(Lavadora->get_PreciosEfectivo(PROGRAMA_PESADO))));
                ui->Resumen_Lavado_Tarjeta->setText("Lavadora número "+(QString::number(Lavadora->get_numMaquina()))+
                                            "<br> Programa: Delicado"+"<br>  Precio:"+(QString::number(Lavadora->get_PreciosTarjeta(PROGRAMA_PESADO))));
                LavadoEfectivo = Lavadora->get_PreciosEfectivo(PROGRAMA_PESADO);
                LavadoTarjeta = Lavadora->get_PreciosTarjeta(PROGRAMA_PESADO);
                break;
            }

            //ui->Resumen_Lavado->setText("Lavadora número "+(QString::number(Lavadora->get_numMaquina()))+" seleccionada. Precio: "+(QString::number(Lavadora->get_PreciosEfectivo(PROGRAMA_PESADO))));
            break;
        default:
            break;
        }


        switch (Lavadora->get_numExtras()) {
        case 0:
            TotalEfectivo = LavadoEfectivo;
            TotalTarjeta = LavadoTarjeta;
            TotalPagoEfectivo = TotalEfectivo*100;
            TotalPagoTarjeta = TotalTarjeta*100;
            ui->Seleccion_Extra->setText("Ningún Extra seleccionado<br> TOTAL: "+QString::number(TotalEfectivo));
            ui->Seleccion_Extra_Tarjeta->setText("Ningún Extra seleccionado <br> TOTAL: "+QString::number(TotalTarjeta));

            break;
        case 1:
            TotalEfectivo = LavadoEfectivo+Lavadora->get_PreciosEfectivo(EXTRA_1);
            TotalTarjeta = LavadoTarjeta+Lavadora->get_PreciosTarjeta(EXTRA_1);
            TotalPagoEfectivo = TotalEfectivo*100;
            TotalPagoTarjeta = TotalTarjeta*100;
            ui->Seleccion_Extra->setText("Extra1 Seleccionado. Precio: "+QString::number(Lavadora->get_PreciosEfectivo(EXTRA_1))+"<br> TOTAL: "+QString::number(TotalEfectivo));
            ui->Seleccion_Extra->setWordWrap(true);
            ui->Seleccion_Extra_Tarjeta->setText("Extra1 Seleccionado. Precio: "+QString::number(Lavadora->get_PreciosTarjeta(EXTRA_1))+"<br> TOTAL: "+QString::number(TotalTarjeta));
            ui->Seleccion_Extra_Tarjeta->setWordWrap(true);

            break;
        case 2:
            TotalEfectivo = LavadoEfectivo+Lavadora->get_PreciosEfectivo(EXTRA_2);
            TotalTarjeta = LavadoTarjeta+Lavadora->get_PreciosTarjeta(EXTRA_2);
            TotalPagoEfectivo = TotalEfectivo*100;
            TotalPagoTarjeta = TotalTarjeta*100;
            ui->Seleccion_Extra->setText("Extra2 Seleccionado. Precio: "+QString::number(Lavadora->get_PreciosEfectivo(EXTRA_2))+"<br> TOTAL: "+QString::number(TotalEfectivo));
            ui->Seleccion_Extra->setWordWrap(true);
            ui->Seleccion_Extra_Tarjeta->setText("Extra2 Seleccionado. Precio: "+QString::number(Lavadora->get_PreciosTarjeta(EXTRA_2))+"<br> TOTAL: "+QString::number(TotalTarjeta));
            ui->Seleccion_Extra_Tarjeta->setWordWrap(true);
            break;
        case 3:
            TotalEfectivo = LavadoEfectivo+Lavadora->get_PreciosEfectivo(EXTRA_3);
            TotalTarjeta = LavadoTarjeta+Lavadora->get_PreciosTarjeta(EXTRA_3);
            TotalPagoEfectivo = TotalEfectivo*100;
            TotalPagoTarjeta = TotalTarjeta*100;
            ui->Seleccion_Extra->setText("Extra3 Seleccionado. Precio: "+QString::number(Lavadora->get_PreciosEfectivo(EXTRA_3))+"<br> TOTAL: "+QString::number(TotalEfectivo));
            ui->Seleccion_Extra->setWordWrap(true);
            ui->Seleccion_Extra_Tarjeta->setText("Extra3 Seleccionado. Precio: "+QString::number(Lavadora->get_PreciosTarjeta(EXTRA_3))+"<br> TOTAL: "+QString::number(TotalTarjeta));
            ui->Seleccion_Extra_Tarjeta->setWordWrap(true);
            break;
        case 4:
            TotalEfectivo = LavadoEfectivo+Lavadora->get_PreciosEfectivo(EXTRA_1)+Lavadora->get_PreciosEfectivo(EXTRA_2);
            TotalTarjeta = LavadoTarjeta+Lavadora->get_PreciosTarjeta(EXTRA_1)+Lavadora->get_PreciosTarjeta(EXTRA_2);
            TotalPagoEfectivo = TotalEfectivo*100;
            TotalPagoTarjeta = TotalTarjeta*100;
            ui->Seleccion_Extra->setText("Extra1 Seleccionado. Precio: "+QString::number(Lavadora->get_PreciosEfectivo(EXTRA_1))+
             "/n EXTRA2 Seleccionado. Precio: "+QString::number(Lavadora->get_PreciosEfectivo(EXTRA_2))+"<br> TOTAL: "+QString::number(TotalEfectivo));
            ui->Seleccion_Extra->setWordWrap(true);

            ui->Seleccion_Extra_Tarjeta->setText("Extra1 Seleccionado. Precio: "+QString::number(Lavadora->get_PreciosTarjeta(EXTRA_1))+
             "/n EXTRA2 Seleccionado. Precio: "+QString::number(Lavadora->get_PreciosTarjeta(EXTRA_2))+"<br> TOTAL: "+QString::number(TotalTarjeta));
            ui->Seleccion_Extra_Tarjeta->setWordWrap(true);
            break;
        case 5:
            TotalEfectivo = LavadoEfectivo+Lavadora->get_PreciosEfectivo(EXTRA_1)+Lavadora->get_PreciosEfectivo(EXTRA_3);
            TotalTarjeta = LavadoTarjeta+Lavadora->get_PreciosTarjeta(EXTRA_1)+Lavadora->get_PreciosTarjeta(EXTRA_3);
            TotalPagoEfectivo = TotalEfectivo*100;
            TotalPagoTarjeta = TotalTarjeta*100;
            ui->Seleccion_Extra->setText("Extra1 Seleccionado. Precio: "+QString::number(Lavadora->get_PreciosEfectivo(EXTRA_1))+
             "<br> EXTRA3 Seleccionado. Precio: "+QString::number(Lavadora->get_PreciosEfectivo(EXTRA_3))+"<br> TOTAL: "+QString::number(TotalEfectivo));
            ui->Seleccion_Extra->setWordWrap(true);
            ui->Seleccion_Extra_Tarjeta->setText("Extra1 Seleccionado. Precio: "+QString::number(Lavadora->get_PreciosTarjeta(EXTRA_1))+
             "<br> EXTRA3 Seleccionado. Precio: "+QString::number(Lavadora->get_PreciosTarjeta(EXTRA_3))+"<br> TOTAL: "+QString::number(TotalTarjeta));
            ui->Seleccion_Extra_Tarjeta->setWordWrap(true);
            break;
        case 6:
            TotalEfectivo = LavadoEfectivo+Lavadora->get_PreciosEfectivo(EXTRA_3)+Lavadora->get_PreciosEfectivo(EXTRA_2);
            TotalTarjeta = LavadoTarjeta+Lavadora->get_PreciosTarjeta(EXTRA_3)+Lavadora->get_PreciosTarjeta(EXTRA_2);
            TotalPagoEfectivo = TotalEfectivo*100;
            TotalPagoTarjeta = TotalTarjeta*100;
            ui->Seleccion_Extra->setText("Extra2 Seleccionado. Precio: "+QString::number(Lavadora->get_PreciosEfectivo(EXTRA_2))+
             "<br> EXTRA3 Seleccionado. Precio: "+QString::number(Lavadora->get_PreciosEfectivo(EXTRA_3))+"<br> TOTAL: "+QString::number(TotalEfectivo));
            ui->Seleccion_Extra->setWordWrap(true);

            ui->Seleccion_Extra_Tarjeta->setText("Extra2 Seleccionado. Precio: "+QString::number(Lavadora->get_PreciosTarjeta(EXTRA_2))+
             "<br> EXTRA3 Seleccionado. Precio: "+QString::number(Lavadora->get_PreciosTarjeta(EXTRA_3))+"<br> TOTAL: "+QString::number(TotalTarjeta));
            ui->Seleccion_Extra_Tarjeta->setWordWrap(true);
            break;
        case 7:
            TotalEfectivo = LavadoEfectivo+Lavadora->get_PreciosEfectivo(EXTRA_1)+Lavadora->get_PreciosEfectivo(EXTRA_2)+Lavadora->get_PreciosEfectivo(EXTRA_3);
            TotalTarjeta = LavadoTarjeta+Lavadora->get_PreciosTarjeta(EXTRA_1)+Lavadora->get_PreciosTarjeta(EXTRA_2)+Lavadora->get_PreciosTarjeta(EXTRA_3);
            TotalPagoEfectivo = TotalEfectivo*100;
            TotalPagoTarjeta = TotalTarjeta*100;
            ui->Seleccion_Extra->setText("Extra1 Seleccionado. Precio: "+QString::number(Lavadora->get_PreciosEfectivo(EXTRA_1))+
             "<br> EXTRA2 Seleccionado. Precio: "+QString::number(Lavadora->get_PreciosEfectivo(EXTRA_2))+
             "<br> EXTRA3 Seleccionado. Precio: "+QString::number(Lavadora->get_PreciosEfectivo(EXTRA_3))+"<br> TOTAL: "+QString::number(TotalEfectivo));
            ui->Seleccion_Extra->setWordWrap(true);

            ui->Seleccion_Extra_Tarjeta->setText("Extra1 Seleccionado. Precio: "+QString::number(Lavadora->get_PreciosTarjeta(EXTRA_1))+
             "<br> EXTRA2 Seleccionado. Precio: "+QString::number(Lavadora->get_PreciosTarjeta(EXTRA_2))+
             "<br> EXTRA3 Seleccionado. Precio: "+QString::number(Lavadora->get_PreciosTarjeta(EXTRA_3))+"<br> TOTAL: "+QString::number(TotalTarjeta));
            ui->Seleccion_Extra_Tarjeta->setWordWrap(true);
            break;
        default:
            break;
        }

      //  ui->Resumen_Lavado->setText("Lavado");
}


void MainWindow::on_Button01_clicked()
{

}


void MainWindow::on_Button02_clicked()
{

}


void MainWindow::on_Button03_clicked()
{

}


void MainWindow::on_B16_MuySucio_clicked()
{
    Lavadora->set_numPrograma(1);

    Lavadora->set_CmdNumProgram(0x01);
    Lavadora->SendCmd(Lavadora->CmdProgramSelectionLav);

    ui->B20_ExtraLavado->setChecked(false);
    ui->B21_ExtraAclarado->setChecked(false);
    ui->B22_ExtraCentrifugado->setChecked(false);

    set_extra1(false);
    set_extra2(false);
    set_extra3(false);

    QPropertyAnimation *animation = new QPropertyAnimation(ui->B16_MuySucio, "geometry");
    animation->setDuration(1000);
    animation->setStartValue(QRect(420, 590, 200, 190));
    animation->setEndValue(QRect(370, 540, 300, 290));
    animation->setEasingCurve(QEasingCurve::OutElastic);
    animation->start();

    connect(animation, SIGNAL(finished()), this, SLOT(ventana7()));

    Lavadora->InfoStatus((unsigned char) Lavadora->get_numMaquina());


}


void MainWindow::set_extra1 (bool e1){
    extra1 = e1;
}

bool MainWindow::get_extra1(){
    return extra1;
}

void MainWindow::set_extra2 (bool e2){
    extra2 = e2;
}

bool MainWindow::get_extra2(){
    return extra2;
}


void MainWindow::set_extra3 (bool e3){
    extra3 = e3;
}

bool MainWindow::get_extra3(){
    return extra3;
}




void MainWindow::on_B06_Secar_clicked()
{
    Secadora->set_numTipoMaquina(2);

    Secadora->SlotHilo();

    ventana9();



}




void MainWindow::on_B17_Sucio_clicked()
{

    Lavadora->set_numPrograma(2);

    Lavadora->set_CmdNumProgram(0x02);
    Lavadora->SendCmd(Lavadora->CmdProgramSelectionLav);

    ui->B20_ExtraLavado->setChecked(false);
    ui->B21_ExtraAclarado->setChecked(false);
    ui->B22_ExtraCentrifugado->setChecked(false);

    set_extra1(false);
    set_extra2(false);
    set_extra3(false);

    QPropertyAnimation *animation = new QPropertyAnimation(ui->B17_Sucio, "geometry");
    animation->setDuration(1000);
    animation->setStartValue(QRect(720, 590, 200, 190));
    animation->setEndValue(QRect(670, 540, 300, 290));
    animation->setEasingCurve(QEasingCurve::OutElastic);
    animation->start();

    connect(animation, SIGNAL(finished()), this, SLOT(ventana7()));

    Lavadora->InfoStatus((unsigned char) Lavadora->get_numMaquina());

}

void MainWindow::on_B18_Normal_clicked()
{

   Lavadora->set_numPrograma(3);

   Lavadora->set_CmdNumProgram(0x03);
   Lavadora->SendCmd(Lavadora->CmdProgramSelectionLav);

    ui->B20_ExtraLavado->setChecked(false);
    ui->B21_ExtraAclarado->setChecked(false);
    ui->B22_ExtraCentrifugado->setChecked(false);

    set_extra1(false);
    set_extra2(false);
    set_extra3(false);

    QPropertyAnimation *animation = new QPropertyAnimation(ui->B18_Normal, "geometry");
    animation->setDuration(1000);
    animation->setStartValue(QRect(1020, 590, 200, 190));
    animation->setEndValue(QRect(970, 540, 300, 290));
    animation->setEasingCurve(QEasingCurve::OutElastic);
    animation->start();

    connect(animation, SIGNAL(finished()), this, SLOT(ventana7()));

    Lavadora->InfoStatus((unsigned char) Lavadora->get_numMaquina());


}

void MainWindow::on_B19_Delicado_clicked()
{

    Lavadora->set_numPrograma(4);

    Lavadora->set_CmdNumProgram(0x04);
    Lavadora->SendCmd(Lavadora->CmdProgramSelectionLav);

    ui->B20_ExtraLavado->setChecked(false);
    ui->B21_ExtraAclarado->setChecked(false);
    ui->B22_ExtraCentrifugado->setChecked(false);

    set_extra1(false);
    set_extra2(false);
    set_extra3(false);

    QPropertyAnimation *animation = new QPropertyAnimation(ui->B19_Delicado, "geometry");
    animation->setDuration(1000);
    animation->setStartValue(QRect(1320, 590, 200, 190));
    animation->setEndValue(QRect(1270, 540, 300, 290));
    animation->setEasingCurve(QEasingCurve::OutElastic);
    animation->start();

    connect(animation, SIGNAL(finished()), this, SLOT(ventana7()));

    Lavadora->InfoStatus((unsigned char) Lavadora->get_numMaquina());
}





void MainWindow::on_B20_ExtraLavado_clicked(bool checked)
{
    QPropertyAnimation *animation = new QPropertyAnimation(ui->B20_ExtraLavado, "geometry");
    animation->setDuration(1000);


    if (checked)
        {
        set_extra1(true);


        }
    else
        {
        set_extra1(false);


        }

    ui->Seleccion_Extra->setText(QString("Programa Delicado"));


}

void MainWindow::on_B21_ExtraAclarado_clicked(bool checked)
{
    if (checked)
        {
        set_extra2(true);
        }
    else
        {
        set_extra2(false);
        }
}

void MainWindow::on_B22_ExtraCentrifugado_clicked(bool checked)
{
    if (checked)
        {
        set_extra3(true);
        }
    else
        {
        set_extra3(false);
        }
}



void MainWindow::on_B08_Tarjeta_clicked()
{
     ui->stackedWidget->setCurrentIndex(15);
     ui->intNuevTarjeta->setText("20");
     intNuevaTarjeta = 20;
}





void MainWindow::on_Menos_clicked()
{
    if(intNuevaTarjeta>20)
    {
        intNuevaTarjeta=intNuevaTarjeta-5;
    }
    ui->intNuevTarjeta->setText(QString::number(intNuevaTarjeta));
}





void MainWindow::on_Mas_clicked()
{
    if(intNuevaTarjeta<50)
    {
        intNuevaTarjeta=intNuevaTarjeta+5;
    }
    ui->intNuevTarjeta->setText(QString::number(intNuevaTarjeta));
}

void MainWindow::on_btnCrearTarjeta_clicked()
{

    ui->stackedWidget->setCurrentIndex(16);
}

void MainWindow::on_B04_Back_9_clicked()
{
     ui->stackedWidget->setCurrentIndex(3);

}

void MainWindow::on_B07_Saldo_clicked()
{
    //K720_Dispenser.EnableMouth();
    K720_Dispenser.BaseDatos=BaseDatos;
    ui->intRecarga->setText("0");

    ui->stackedWidget->setCurrentIndex(20);

    if(TarjetaThread->isRunning())
    {
        TarjetaThread->terminate();
    }
    TarjetaThread->Function=33;
    TarjetaThread->start();



}



void MainWindow::on_GuardarFormulario_clicked()
{
    UltimaPagina = 16;
    TotalPago = (ui->intNuevTarjeta->text().toFloat())*100;

    ui->intEfectivoRestante->setText(QString::number(TotalPago/100));
    ui->stackedWidget->setCurrentIndex(17);


    if(EfectivoThread->isRunning())
    {
        EfectivoThread->Enable();
    }
    else
    {
        EfectivoThread->start();
    }

    EfectivoThread2->start(QThread::HighPriority);
   /* HANDLE hComPortAux=NULL;

    QString saldo = NULL;
    QString saldoString =NULL;
    QString nombre = NULL;
    QString apellidos = NULL;
    QString LastID = NULL;
    QString strCardID = NULL;
    QString ntarj = NULL;
    QString ID = NULL;

    BYTE numCardAux = NULL;
    BYTE numCard[5];

    nombre = ui->NombreValor->text();
    apellidos = ui->ApellidosValor->text();
    saldoString = ui->intNuevTarjeta->text();
    saldo = ui->intNuevTarjeta->text();

   hComPortAux = K720_Dispenser.ConnectCOM();

   if(hComPortAux==0)
   {
       cout<<"Error de conexión al puerto del dispensador de tarjetas.";
   }

   bool dbConectado = BaseDatos.ConectarServidor();

   cout<<"dbConectado = "<<dbConectado<<endl;

   if (dbConectado)
   {
       K720_Dispenser.BaseDatos = BaseDatos;
   }

   LastID=BaseDatos.IDNuevoCliente();

   strCardID = K720_Dispenser.CrearTarjeta(nombre,apellidos,LastID);

   bool NuevoCliente = false;

   NuevoCliente = BaseDatos.NuevoCliente(nombre,apellidos,saldo,strCardID);

   if(NuevoCliente)
   {
       cout <<"Cliente creado correctamente"<<endl;

   }
   else
   {
       QMessageBox::critical(this,"Error","Error al crear el nuevo cliente");
   }






   ui->stackedWidget->setCurrentIndex(0);
   float saldofloat = BaseDatos.SaldoCliente(ntarj,ID);
   cout<<"saldofloat = " <<saldofloat<<endl;*/

  /*  QSqlQuery query(db);


    if(db.isOpen())
    {
        qDebug() << "La conexion esta establecida";
    //    query.exec("SELECT * FROM base_datos_cp.clientes");
   //     query.isActive();
   //     query.isSelect();
   //     query.isValid();
        query.exec("SELECT max(id+1) FROM base_datos_cp.clientes");
        query.first();
        LastID = query.value(0).toString();

        qDebug() << query.lastError().text();

       // LastID = query.lastInsertId().toChar().toLatin1();
        cout<<"Last ID1 = "<<LastID.toStdString()<<endl;
        qDebug()<<"LastID1" <<LastID<<endl;
    }
    else
    {
        qDebug() << "La conexion NO esta establecida";
    }
    ID = LastID.toStdString();
    cout<<"Last ID2 = "<<ID<<endl;
    //qDebug()<<"LastID2" <<ID<<endl;

    QMessageBox::critical(this,"Nombre y Saldo", nombre + apellidos + saldoString);

     hComPortAux = K720_Dispenser.ConnectCOM(PortDispenser);
     if(hComPortAux==0)
     {
         cout<<"Error de conexión al puerto del dispensador de tarjetas.";
     }
     else
     {

         cout<<"Puerto COM del dispensador de tarjetas conectado";
         strCardID = K720_Dispenser.CrearTarjeta(nombre,apellidos,LastID);
        // qDebug () << "numero tarjeta aux" << numCardAux;
      //   numCard = numCardAux;
      //   qDebug () << "numero tarjeta aux" << numCard;


        printf("numCardAux %x",numCardAux);
        cout <<"Pasa por aqui come bolsas"<<endl;
        //cout<<"string"<<strCardID;
         if(db.isOpen())
         {
             qDebug() << "La conexion esta establecida";
             QString insertvalues = "INSERT INTO base_datos_cp.clientes (Nombre, Apellidos, Numero_de_tarjeta, Saldo) VALUES (:nombre, :apellidos, :CardID, :saldoString)";

             query.prepare(insertvalues);
             query.bindValue(":nombre",nombre);
             query.bindValue(":apellidos",apellidos);
             query.bindValue(":saldoString",saldoString);
             query.bindValue(":CardID",strCardID);
             query.exec();
             query.finish();
             qDebug() << query.lastError().text();


         }
         else
         {
             qDebug() << "La conexion NO esta establecida";
         }

     }*/




}

void MainWindow::on_B04_Back_10_clicked()
{
    ui->stackedWidget->setCurrentIndex(15);

}

void MainWindow::on_B04_Back_8_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_B09_Secadora1_clicked()
{
    Secadora->set_numTipoMaquina(2);
    Secadora->set_numMaquina(1);

    Secadora->set_CmdNumMaq(0x01);


    Secadora->InfoStatus((unsigned char) Secadora->get_numMaquina());

    ui->intTamaSecSel2_3->setText(QString("8 KG"));
    ui->intEfectivoSel2_3 ->setText(QString::number(Secadora->get_PreciosEfectivo(PROGRAMA_LIGERO)));
    ui->intTarjetaSel2_3 ->setText(QString::number(Secadora->get_PreciosTarjeta(PROGRAMA_LIGERO)));
    ui->intTotalSel2_3->setText(QString::number(Secadora->get_PreciosEfectivo(PROGRAMA_LIGERO)));
    ui->intTotalTarSel2_3->setText(QString::number(Secadora->get_PreciosEfectivo(PROGRAMA_LIGERO)));

    ui->intTamaSecSel2_4->setText(QString("8 KG"));
    ui->intEfectivoSel2_4 ->setText(QString::number(Secadora->get_PreciosEfectivo(PROGRAMA_LIGERO)));
    ui->intTarjetaSel2_4 ->setText(QString::number(Secadora->get_PreciosTarjeta(PROGRAMA_LIGERO)));
    ui->intTotalSel2_4->setText(QString::number(Secadora->get_PreciosEfectivo(PROGRAMA_LIGERO)));
    ui->intTotalTarSel2_4->setText(QString::number(Secadora->get_PreciosEfectivo(PROGRAMA_LIGERO)));

 //   ui->Seleccion_Maquina->setText(QString("Seleccionada Secadora Nº 1"));
 //   ui->Seleccion_Maquina_2->setText(QString("Seleccionada Secadora Nº 1"));
 //   ui->Seleccion_Maquina_3->setText(QString("Seleccionada Secadora Nº 1"));

    QPropertyAnimation *animation = new QPropertyAnimation(ui->B09_Secadora1, "geometry");
    animation->setDuration(1000);
    animation->setStartValue(QRect(50, 560, 250, 250));
    animation->setEndValue(QRect(0, 510, 350, 350));
    animation->setEasingCurve(QEasingCurve::OutCirc);
    animation->start();

    connect(animation, SIGNAL(finished()), this, SLOT(ventana10()));
}

void MainWindow::on_B10_Secadora2_clicked()
{
    Secadora->set_numTipoMaquina(2);
    Secadora->set_numMaquina(2);

    Secadora->set_CmdNumMaq(0x02);


    Secadora->InfoStatus((unsigned char) Secadora->get_numMaquina());


    ui->intTamaSecSel2_3->setText(QString("8 KG"));
    ui->intEfectivoSel2_3 ->setText(QString::number(Secadora->get_PreciosEfectivo(PROGRAMA_LIGERO)));
    ui->intTarjetaSel2_3 ->setText(QString::number(Secadora->get_PreciosTarjeta(PROGRAMA_LIGERO)));
    ui->intTotalSel2_3->setText(QString::number(Secadora->get_PreciosEfectivo(PROGRAMA_LIGERO)));
    ui->intTotalTarSel2_3->setText(QString::number(Secadora->get_PreciosEfectivo(PROGRAMA_LIGERO)));

    ui->intTamaSecSel2_4->setText(QString("8 KG"));
    ui->intEfectivoSel2_4 ->setText(QString::number(Secadora->get_PreciosEfectivo(PROGRAMA_LIGERO)));
    ui->intTarjetaSel2_4 ->setText(QString::number(Secadora->get_PreciosTarjeta(PROGRAMA_LIGERO)));
    ui->intTotalSel2_4->setText(QString::number(Secadora->get_PreciosEfectivo(PROGRAMA_LIGERO)));
    ui->intTotalTarSel2_4->setText(QString::number(Secadora->get_PreciosEfectivo(PROGRAMA_LIGERO)));
    //ui->Seleccion_Maquina->setText(QString("Seleccionada Secadora Nº 2"));
 //   ui->Seleccion_Maquina_2->setText(QString("Seleccionada Secadora Nº 2"));
 //   ui->Seleccion_Maquina_3->setText(QString("Seleccionada Secadora Nº 2"));

    QPropertyAnimation *animation = new QPropertyAnimation(ui->B10_Secadora2, "geometry");
    animation->setDuration(1000);
    animation->setStartValue(QRect(350, 560, 250, 250));
    animation->setEndValue(QRect(300, 510, 350, 350));
    animation->setEasingCurve(QEasingCurve::OutElastic);
    animation->start();

    connect(animation, SIGNAL(finished()), this, SLOT(ventana10()));
}

void MainWindow::on_B11_Secadora3_clicked()
{
    Secadora->set_numTipoMaquina(2);
    Secadora->set_numMaquina(3);

    Secadora->set_CmdNumMaq(0x03);


    Secadora->InfoStatus((unsigned char) Secadora->get_numMaquina());



    ui->intTamaSecSel2_3->setText(QString("13 KG"));
    ui->intEfectivoSel2_3 ->setText(QString::number(Secadora->get_PreciosEfectivo(PROGRAMA_MEDIO)));
    ui->intTarjetaSel2_3 ->setText(QString::number(Secadora->get_PreciosTarjeta(PROGRAMA_MEDIO)));
    ui->intTotalSel2_3->setText(QString::number(Secadora->get_PreciosEfectivo(PROGRAMA_MEDIO)));
    ui->intTotalTarSel2_3->setText(QString::number(Secadora->get_PreciosEfectivo(PROGRAMA_MEDIO)));

    ui->intTamaSecSel2_4->setText(QString("13 KG"));
    ui->intEfectivoSel2_4 ->setText(QString::number(Secadora->get_PreciosEfectivo(PROGRAMA_MEDIO)));
    ui->intTarjetaSel2_4 ->setText(QString::number(Secadora->get_PreciosTarjeta(PROGRAMA_MEDIO)));
    ui->intTotalSel2_4->setText(QString::number(Secadora->get_PreciosEfectivo(PROGRAMA_MEDIO)));
    ui->intTotalTarSel2_4->setText(QString::number(Secadora->get_PreciosEfectivo(PROGRAMA_MEDIO)));
  //  ui->Seleccion_Maquina->setText(QString("Seleccionada Secadora Nº 3"));
  //  ui->Seleccion_Maquina_2->setText(QString("Seleccionada Secadora Nº 3"));
  //  ui->Seleccion_Maquina_3->setText(QString("Seleccionada Secadora Nº 3"));

    QPropertyAnimation *animation = new QPropertyAnimation(ui->B11_Secadora3, "geometry");
    animation->setDuration(1000);
    animation->setStartValue(QRect(650, 560, 250, 250));
    animation->setEndValue(QRect(600, 510, 350, 350));
    animation->setEasingCurve(QEasingCurve::InOutBack);
    animation->start();

    connect(animation, SIGNAL(finished()), this, SLOT(ventana10()));
}

void MainWindow::on_B12_Secadora4_clicked()
{
    Secadora->set_numTipoMaquina(2);
    Secadora->set_numMaquina(4);

    Secadora->set_CmdNumMaq(0x04);


    Secadora->InfoStatus((unsigned char) Secadora->get_numMaquina());

    ui->intTamaSecSel2_3->setText(QString("13 KG"));
    ui->intEfectivoSel2_3 ->setText(QString::number(Secadora->get_PreciosEfectivo(PROGRAMA_MEDIO)));
    ui->intTarjetaSel2_3 ->setText(QString::number(Secadora->get_PreciosTarjeta(PROGRAMA_MEDIO)));
    ui->intTotalSel2_3->setText(QString::number(Secadora->get_PreciosEfectivo(PROGRAMA_MEDIO)));
    ui->intTotalTarSel2_3->setText(QString::number(Secadora->get_PreciosEfectivo(PROGRAMA_MEDIO)));

    ui->intTamaSecSel2_4->setText(QString("13 KG"));
    ui->intEfectivoSel2_4 ->setText(QString::number(Secadora->get_PreciosEfectivo(PROGRAMA_MEDIO)));
    ui->intTarjetaSel2_4 ->setText(QString::number(Secadora->get_PreciosTarjeta(PROGRAMA_MEDIO)));
    ui->intTotalSel2_4->setText(QString::number(Secadora->get_PreciosEfectivo(PROGRAMA_MEDIO)));
    ui->intTotalTarSel2_4->setText(QString::number(Secadora->get_PreciosEfectivo(PROGRAMA_MEDIO)));
 //   ui->Seleccion_Maquina->setText(QString("Seleccionada Secadora Nº 4"));
//    ui->Seleccion_Maquina_2->setText(QString("Seleccionada Secadora Nº 4"));
//    ui->Seleccion_Maquina_3->setText(QString("Seleccionada Secadora Nº 4"));

    QPropertyAnimation *animation = new QPropertyAnimation(ui->B12_Secadora4, "geometry");
    animation->setDuration(1000);
    animation->setStartValue(QRect(950, 560, 250, 250));
    animation->setEndValue(QRect(900, 510, 350, 350));
    animation->setEasingCurve(QEasingCurve::OutCirc);
    animation->start();

    connect(animation, SIGNAL(finished()), this, SLOT(ventana10()));
}

void MainWindow::on_B13_Secadora5_clicked()
{
    Secadora->set_numTipoMaquina(2);
    Secadora->set_numMaquina(5);

    Secadora->set_CmdNumMaq(0x05);


    Secadora->InfoStatus((unsigned char) Secadora->get_numMaquina());


    ui->intTamaSecSel2_3->setText(QString("17 KG"));
    ui->intEfectivoSel2_3 ->setText(QString::number(Secadora->get_PreciosEfectivo(PROGRAMA_PESADO)));
    ui->intTarjetaSel2_3 ->setText(QString::number(Secadora->get_PreciosTarjeta(PROGRAMA_PESADO)));
    ui->intTotalSel2_3->setText(QString::number(Secadora->get_PreciosEfectivo(PROGRAMA_PESADO)));
    ui->intTotalTarSel2_3->setText(QString::number(Secadora->get_PreciosEfectivo(PROGRAMA_PESADO)));

    ui->intTamaSecSel2_4->setText(QString("17 KG"));
    ui->intEfectivoSel2_4 ->setText(QString::number(Secadora->get_PreciosEfectivo(PROGRAMA_PESADO)));
    ui->intTarjetaSel2_4 ->setText(QString::number(Secadora->get_PreciosTarjeta(PROGRAMA_PESADO)));
    ui->intTotalSel2_4->setText(QString::number(Secadora->get_PreciosEfectivo(PROGRAMA_PESADO)));
    ui->intTotalTarSel2_4->setText(QString::number(Secadora->get_PreciosEfectivo(PROGRAMA_PESADO)));
 //   ui->Seleccion_Maquina->setText(QString("Seleccionada Secadora Nº 5"));
 //   ui->Seleccion_Maquina_2->setText(QString("Seleccionada Secadora Nº 5"));
 //   ui->Seleccion_Maquina_3->setText(QString("Seleccionada Secadora Nº 5"));

    QPropertyAnimation *animation = new QPropertyAnimation(ui->B13_Secadora5, "geometry");
    animation->setDuration(1000);
    animation->setStartValue(QRect(1250, 560, 250, 250));
    animation->setEndValue(QRect(1200, 510, 350, 350));
    animation->setEasingCurve(QEasingCurve::InElastic);
    animation->start();

    connect(animation, SIGNAL(finished()), this, SLOT(ventana10()));
}

void MainWindow::on_B14_Secadora6_clicked()
{
    Secadora->set_numTipoMaquina(2);
    Secadora->set_numMaquina(6);

    Secadora->set_CmdNumMaq(0x06);


    Secadora->InfoStatus((unsigned char) Secadora->get_numMaquina());


    ui->intTamaSecSel2_3->setText(QString("17 KG"));
    ui->intEfectivoSel2_3 ->setText(QString::number(Secadora->get_PreciosEfectivo(PROGRAMA_PESADO)));
    ui->intTarjetaSel2_3 ->setText(QString::number(Secadora->get_PreciosTarjeta(PROGRAMA_PESADO)));
    ui->intTotalSel2_3->setText(QString::number(Secadora->get_PreciosEfectivo(PROGRAMA_PESADO)));
    ui->intTotalTarSel2_3->setText(QString::number(Secadora->get_PreciosEfectivo(PROGRAMA_PESADO)));

    ui->intTamaSecSel2_4->setText(QString("17 KG"));
    ui->intEfectivoSel2_4 ->setText(QString::number(Secadora->get_PreciosEfectivo(PROGRAMA_PESADO)));
    ui->intTarjetaSel2_4 ->setText(QString::number(Secadora->get_PreciosTarjeta(PROGRAMA_PESADO)));
    ui->intTotalSel2_4->setText(QString::number(Secadora->get_PreciosEfectivo(PROGRAMA_PESADO)));
    ui->intTotalTarSel2_4->setText(QString::number(Secadora->get_PreciosEfectivo(PROGRAMA_PESADO)));
    //ui->Seleccion_Maquina->setText(QString("Seleccionada Secadora Nº 6"));
 //   ui->Seleccion_Maquina_2->setText(QString("Seleccionada Secadora Nº 6"));
 //   ui->Seleccion_Maquina_3->setText(QString("Seleccionada Secadora Nº 6"));

    QPropertyAnimation *animation = new QPropertyAnimation(ui->B14_Secadora6, "geometry");
    animation->setDuration(1000);
    animation->setStartValue(QRect(1550, 560, 250, 250));
    animation->setEndValue(QRect(1500, 510, 350, 350));
    animation->setEasingCurve(QEasingCurve::OutElastic);
    animation->start();

    connect(animation, SIGNAL(finished()), this, SLOT(ventana10()));
}

void MainWindow::on_B04_Back_13_clicked()
{
    ui->stackedWidget->setCurrentIndex(9);
    Secadora->terminate();
}

void MainWindow::on_B15_Adelante_6_clicked()
{
    ui->stackedWidget->setCurrentIndex(11);
}

void MainWindow::on_B16_Caliente_2_clicked()
{
    Secadora->set_numPrograma(1);


    Secadora->set_CmdNumProgram(0x01);

    Sleep(50);

    Secadora->SendCmd(Secadora->CmdProgramSelectionSec);

    Sleep(50);

    Secadora->InfoStatus((unsigned char) Secadora->get_numMaquina());

    ui->intTiempoSecadoExtra->setText(QString("0"));

    QPropertyAnimation *animation = new QPropertyAnimation(ui->B16_Caliente_2, "geometry");
    animation->setDuration(1000);
    animation->setStartValue(QRect(570, 590, 180, 180));
    animation->setEndValue(QRect(520, 540, 280, 280));
    animation->setEasingCurve(QEasingCurve::OutElastic);
    animation->start();

    connect(animation, SIGNAL(finished()), this, SLOT(ventana12()));

}

void MainWindow::on_B17_Templado_2_clicked()
{

    Secadora->set_numPrograma(2);

    Secadora->set_CmdNumProgram(0x02);
    Sleep(50);
    Secadora->SendCmd(Secadora->CmdProgramSelectionSec);

    Sleep(50);

    Secadora->InfoStatus((unsigned char) Secadora->get_numMaquina());

    ui->intTiempoSecadoExtra->setText(QString("0"));

    QPropertyAnimation *animation = new QPropertyAnimation(ui->B17_Templado_2, "geometry");
    animation->setDuration(1000);
    animation->setStartValue(QRect(870, 590, 180, 180));
    animation->setEndValue(QRect(820, 540, 280, 280));
    animation->setEasingCurve(QEasingCurve::OutElastic);
    animation->start();

    connect(animation, SIGNAL(finished()), this, SLOT(ventana12()));

    //Secadora->InfoStatus((unsigned char) Secadora->get_numMaquina());
}

void MainWindow::on_B18_Frio_2_clicked()
{
    Secadora->set_numPrograma(3);

    Secadora->set_CmdNumProgram(0x03);
    Sleep(50);
    Secadora->SendCmd(Secadora->CmdProgramSelectionSec);
    Sleep(50);

    Secadora->InfoStatus((unsigned char) Secadora->get_numMaquina());

    ui->intTiempoSecadoExtra->setText(QString("0"));

    QPropertyAnimation *animation = new QPropertyAnimation(ui->B18_Frio_2, "geometry");
    animation->setDuration(1000);
    animation->setStartValue(QRect(1170, 590, 180, 180));
    animation->setEndValue(QRect(1120, 540, 280, 280));
    animation->setEasingCurve(QEasingCurve::OutElastic);
    animation->start();

    connect(animation, SIGNAL(finished()), this, SLOT(ventana12()));

   // Secadora->InfoStatus((unsigned char) Secadora->get_numMaquina());
}

void MainWindow::on_B04_Back_12_clicked()
{
     ui->stackedWidget->setCurrentIndex(10);
}

void MainWindow::on_B04_Back_11_clicked()
{
     ui->stackedWidget->setCurrentIndex(11);
}

void MainWindow::on_Mas_2_clicked()
{
    if(intTiempoSecadoExtra<50)
    {
        intTiempoSecadoExtra=intTiempoSecadoExtra+5;
    }
    ui->intTiempoSecadoExtra->setText(QString::number(intTiempoSecadoExtra));
}

void MainWindow::on_Menos_2_clicked()
{
    if(intTiempoSecadoExtra>0)
    {
        intTiempoSecadoExtra=intTiempoSecadoExtra-5;
    }
    ui->intTiempoSecadoExtra->setText(QString::number(intTiempoSecadoExtra));
}

void MainWindow::on_B15_Adelante_5_clicked()
{
    float TiempoExtra;
    float SecadoEfectivo = 0;
    float SecadoTarjeta = 0;
    float TotalEfectivo = 0;
    float TotalTarjeta = 0;

    UltimaPagina = 12;

    Secadora->set_numTiempoExtra(ui->intTiempoSecadoExtra->text().toInt());

    Secadora->SendCmd(Secadora->CmdProgramSelectionSec);

    Secadora->set_CmdMinExtraSecado((unsigned char)Secadora->numTiempoExtra);



   TiempoExtra = ui->intTiempoSecadoExtra->text().toFloat();

   string EnvioAux ="ALS";
   char AuxEx = Secadora->get_numMaquina();
   AuxEx = (AuxEx+'0');
   EnvioAux+=AuxEx;

   emit PrinterFunction(EnvioAux);

   EnvioAux = "ALINI";
   emit PrinterFunction(EnvioAux);

   EnvioAux = "AI";
   emit PrinterFunction(EnvioAux);


   switch (Secadora->get_numMaquina()) {
   case 1:

       switch (Secadora->get_numPrograma()) {
       case 1:
           ui->Resumen_Secado->setText("Secadora número "+(QString::number(Secadora->get_numMaquina()))+
                                       "<br> Programa: Caliente"+"<br>  Precio:"+(QString::number(Secadora->get_PreciosEfectivo(PROGRAMA_SECADO))));
           ui->Resumen_Secado_Tarjeta->setText("Secadora número "+(QString::number(Secadora->get_numMaquina()))+
                                       "<br> Programa: Caliente"+"<br>  Precio:"+(QString::number(Secadora->get_PreciosTarjeta(PROGRAMA_SECADO))));
           SecadoEfectivo = Secadora->get_PreciosEfectivo(PROGRAMA_SECADO);
           SecadoTarjeta = Secadora->get_PreciosTarjeta(PROGRAMA_SECADO);
           break;
       case 2:
           ui->Resumen_Secado->setText("Secadora número "+(QString::number(Secadora->get_numMaquina()))+
                                       "<br> Programa: Templado"+"<br>  Precio:"+(QString::number(Secadora->get_PreciosEfectivo(PROGRAMA_SECADO))));
           ui->Resumen_Secado_Tarjeta->setText("Secadora número "+(QString::number(Secadora->get_numMaquina()))+
                                       "<br> Programa: Templado"+"<br>  Precio:"+(QString::number(Secadora->get_PreciosTarjeta(PROGRAMA_SECADO))));
           SecadoEfectivo = Secadora->get_PreciosEfectivo(PROGRAMA_SECADO);
           SecadoTarjeta = Secadora->get_PreciosTarjeta(PROGRAMA_SECADO);
           break;
       case 3:
           ui->Resumen_Secado->setText("Secadora número "+(QString::number(Secadora->get_numMaquina()))+
                                       "<br> Programa: Frío"+"<br>  Precio:"+(QString::number(Secadora->get_PreciosEfectivo(PROGRAMA_SECADO))));
           ui->Resumen_Secado_Tarjeta->setText("Secadora número "+(QString::number(Secadora->get_numMaquina()))+
                                       "<br> Programa: Frío"+"<br>  Precio:"+(QString::number(Secadora->get_PreciosTarjeta(PROGRAMA_SECADO))));
           SecadoEfectivo = Secadora->get_PreciosEfectivo(PROGRAMA_SECADO);
           SecadoTarjeta = Secadora->get_PreciosTarjeta(PROGRAMA_SECADO);
           break;

       default:
           break;
       }


       break;
   case 2:
       switch (Secadora->get_numPrograma()) {
       case 1:
           ui->Resumen_Secado->setText("Secadora número "+(QString::number(Secadora->get_numMaquina()))+
                                       "<br> Programa: Caliente"+"<br>  Precio:"+(QString::number(Secadora->get_PreciosEfectivo(PROGRAMA_SECADO))));
           ui->Resumen_Secado_Tarjeta->setText("Secadora número "+(QString::number(Secadora->get_numMaquina()))+
                                       "<br> Programa: Caliente"+"<br>  Precio:"+(QString::number(Secadora->get_PreciosTarjeta(PROGRAMA_SECADO))));
           SecadoEfectivo = Secadora->get_PreciosEfectivo(PROGRAMA_SECADO);
           SecadoTarjeta = Secadora->get_PreciosTarjeta(PROGRAMA_SECADO);
           break;
       case 2:
           ui->Resumen_Secado->setText("Secadora número "+(QString::number(Secadora->get_numMaquina()))+
                                       "<br> Programa: Templado"+"<br>  Precio:"+(QString::number(Secadora->get_PreciosEfectivo(PROGRAMA_SECADO))));
           ui->Resumen_Secado_Tarjeta->setText("Secadora número "+(QString::number(Secadora->get_numMaquina()))+
                                       "<br> Programa: Templado"+"<br>  Precio:"+(QString::number(Secadora->get_PreciosTarjeta(PROGRAMA_SECADO))));
           SecadoEfectivo = Secadora->get_PreciosEfectivo(PROGRAMA_SECADO);
           SecadoTarjeta = Secadora->get_PreciosTarjeta(PROGRAMA_SECADO);
           break;
       case 3:
           ui->Resumen_Secado->setText("Secadora número "+(QString::number(Secadora->get_numMaquina()))+
                                       "<br> Programa: Frío"+"<br>  Precio:"+(QString::number(Secadora->get_PreciosEfectivo(PROGRAMA_SECADO))));
           ui->Resumen_Secado_Tarjeta->setText("Secadora número "+(QString::number(Secadora->get_numMaquina()))+
                                       "<br> Programa: Frío"+"<br>  Precio:"+(QString::number(Secadora->get_PreciosTarjeta(PROGRAMA_SECADO))));
           SecadoEfectivo = Secadora->get_PreciosEfectivo(PROGRAMA_SECADO);
           SecadoTarjeta = Secadora->get_PreciosTarjeta(PROGRAMA_SECADO);
           break;

       default:
           break;
       }
       //ui->Resumen_Secado->setText("Secadora número "+(QString::number(Secadora->get_numMaquina()))+" seleccionada. Precio: "+(QString::number(Secadora->get_PreciosEfectivo(PROGRAMA_SECADO))));
       break;
   case 3:
       switch (Secadora->get_numPrograma()) {
       case 1:
           ui->Resumen_Secado->setText("Secadora número "+(QString::number(Secadora->get_numMaquina()))+
                                       "<br> Programa: Caliente"+"<br>  Precio:"+(QString::number(Secadora->get_PreciosEfectivo(PROGRAMA_SECADO))));
           ui->Resumen_Secado_Tarjeta->setText("Secadora número "+(QString::number(Secadora->get_numMaquina()))+
                                       "<br> Programa: Caliente"+"<br>  Precio:"+(QString::number(Secadora->get_PreciosTarjeta(PROGRAMA_SECADO))));
           SecadoEfectivo = Secadora->get_PreciosEfectivo(PROGRAMA_SECADO);
           SecadoTarjeta = Secadora->get_PreciosTarjeta(PROGRAMA_SECADO);
           break;
       case 2:
           ui->Resumen_Secado->setText("Secadora número "+(QString::number(Secadora->get_numMaquina()))+
                                       "<br> Programa: Templado"+"<br>  Precio:"+(QString::number(Secadora->get_PreciosEfectivo(PROGRAMA_SECADO))));
           ui->Resumen_Secado_Tarjeta->setText("Secadora número "+(QString::number(Secadora->get_numMaquina()))+
                                       "<br> Programa: Templado"+"<br>  Precio:"+(QString::number(Secadora->get_PreciosTarjeta(PROGRAMA_SECADO))));
           SecadoEfectivo = Secadora->get_PreciosEfectivo(PROGRAMA_SECADO);
           SecadoTarjeta = Secadora->get_PreciosTarjeta(PROGRAMA_SECADO);
           break;
       case 3:
           ui->Resumen_Secado->setText("Secadora número "+(QString::number(Secadora->get_numMaquina()))+
                                       "<br> Programa: Frío"+"<br>  Precio:"+(QString::number(Secadora->get_PreciosEfectivo(PROGRAMA_SECADO))));
           ui->Resumen_Secado_Tarjeta->setText("Secadora número "+(QString::number(Secadora->get_numMaquina()))+
                                       "<br> Programa: Frío"+"<br>  Precio:"+(QString::number(Secadora->get_PreciosTarjeta(PROGRAMA_SECADO))));
           SecadoEfectivo = Secadora->get_PreciosEfectivo(PROGRAMA_SECADO);
           SecadoTarjeta = Secadora->get_PreciosTarjeta(PROGRAMA_SECADO);
           break;

       }
       //ui->Resumen_Secado->setText("Secadora número "+(QString::number(Secadora->get_numMaquina()))+" seleccionada. Precio: "+(QString::number(Secadora->get_PreciosEfectivo(PROGRAMA_SECADO))));
       break;
   case 4:

       switch (Secadora->get_numPrograma()) {
       case 1:
           ui->Resumen_Secado->setText("Secadora número "+(QString::number(Secadora->get_numMaquina()))+
                                       "<br> Programa: Caliente"+"<br>  Precio:"+(QString::number(Secadora->get_PreciosEfectivo(PROGRAMA_SECADO))));
           ui->Resumen_Secado_Tarjeta->setText("Secadora número "+(QString::number(Secadora->get_numMaquina()))+
                                       "<br> Programa: Caliente"+"<br>  Precio:"+(QString::number(Secadora->get_PreciosTarjeta(PROGRAMA_SECADO))));
           SecadoEfectivo = Secadora->get_PreciosEfectivo(PROGRAMA_SECADO);
           SecadoTarjeta = Secadora->get_PreciosTarjeta(PROGRAMA_SECADO);
           break;
       case 2:
           ui->Resumen_Secado->setText("Secadora número "+(QString::number(Secadora->get_numMaquina()))+
                                       "<br> Programa: Templado"+"<br>  Precio:"+(QString::number(Secadora->get_PreciosEfectivo(PROGRAMA_SECADO))));
           ui->Resumen_Secado_Tarjeta->setText("Secadora número "+(QString::number(Secadora->get_numMaquina()))+
                                       "<br> Programa: Templado"+"<br>  Precio:"+(QString::number(Secadora->get_PreciosTarjeta(PROGRAMA_SECADO))));
           SecadoEfectivo = Secadora->get_PreciosEfectivo(PROGRAMA_SECADO);
           SecadoTarjeta = Secadora->get_PreciosTarjeta(PROGRAMA_SECADO);
           break;
       case 3:
           ui->Resumen_Secado->setText("Secadora número "+(QString::number(Secadora->get_numMaquina()))+
                                       "<br> Programa: Frío"+"<br>  Precio:"+(QString::number(Secadora->get_PreciosEfectivo(PROGRAMA_SECADO))));
           ui->Resumen_Secado_Tarjeta->setText("Secadora número "+(QString::number(Secadora->get_numMaquina()))+
                                       "<br> Programa: Frío"+"<br>  Precio:"+(QString::number(Secadora->get_PreciosTarjeta(PROGRAMA_SECADO))));
           SecadoEfectivo = Secadora->get_PreciosEfectivo(PROGRAMA_SECADO);
           SecadoTarjeta = Secadora->get_PreciosTarjeta(PROGRAMA_SECADO);
           break;

       }
      // ui->Resumen_Secado->setText("Secadora número "+(QString::number(Secadora->get_numMaquina()))+" seleccionada. Precio: "+(QString::number(Secadora->get_PreciosEfectivo(PROGRAMA_SECADO))));
       break;
   case 5:

       switch (Secadora->get_numPrograma()) {
       case 1:
           ui->Resumen_Secado->setText("Secadora número "+(QString::number(Secadora->get_numMaquina()))+
                                       "<br> Programa: Caliente"+"<br>  Precio:"+(QString::number(Secadora->get_PreciosEfectivo(PROGRAMA_SECADO))));
           ui->Resumen_Secado_Tarjeta->setText("Secadora número "+(QString::number(Secadora->get_numMaquina()))+
                                       "<br> Programa: Caliente"+"<br>  Precio:"+(QString::number(Secadora->get_PreciosTarjeta(PROGRAMA_SECADO))));
           SecadoEfectivo = Secadora->get_PreciosEfectivo(PROGRAMA_SECADO);
           SecadoTarjeta = Secadora->get_PreciosTarjeta(PROGRAMA_SECADO);
           break;
       case 2:
           ui->Resumen_Secado->setText("Secadora número "+(QString::number(Secadora->get_numMaquina()))+
                                       "<br> Programa: Templado"+"<br>  Precio:"+(QString::number(Secadora->get_PreciosEfectivo(PROGRAMA_SECADO))));
           ui->Resumen_Secado_Tarjeta->setText("Secadora número "+(QString::number(Secadora->get_numMaquina()))+
                                       "<br> Programa: Templado"+"<br>  Precio:"+(QString::number(Secadora->get_PreciosTarjeta(PROGRAMA_SECADO))));
           SecadoEfectivo = Secadora->get_PreciosEfectivo(PROGRAMA_SECADO);
           SecadoTarjeta = Secadora->get_PreciosTarjeta(PROGRAMA_SECADO);
           break;
       case 3:
           ui->Resumen_Secado->setText("Secadora número "+(QString::number(Secadora->get_numMaquina()))+
                                       "<br> Programa: Frío"+"<br>  Precio:"+(QString::number(Secadora->get_PreciosEfectivo(PROGRAMA_SECADO))));
           ui->Resumen_Secado_Tarjeta->setText("Secadora número "+(QString::number(Secadora->get_numMaquina()))+
                                       "<br> Programa: Frío"+"<br>  Precio:"+(QString::number(Secadora->get_PreciosTarjeta(PROGRAMA_SECADO))));
           SecadoEfectivo = Secadora->get_PreciosEfectivo(PROGRAMA_SECADO);
           SecadoTarjeta = Secadora->get_PreciosTarjeta(PROGRAMA_SECADO);
           break;

       }

       //ui->Resumen_Secado->setText("Secadora número "+(QString::number(Secadora->get_numMaquina()))+" seleccionada. Precio: "+(QString::number(Secadora->get_PreciosEfectivo(PROGRAMA_SECADO))));
       break;
   case 6:
       switch (Secadora->get_numPrograma()) {
       case 1:
           ui->Resumen_Secado->setText("Secadora número "+(QString::number(Secadora->get_numMaquina()))+
                                       "<br> Programa: Caliente"+"<br>  Precio:"+(QString::number(Secadora->get_PreciosEfectivo(PROGRAMA_SECADO))));
           ui->Resumen_Secado_Tarjeta->setText("Secadora número "+(QString::number(Secadora->get_numMaquina()))+
                                       "<br> Programa: Caliente"+"<br>  Precio:"+(QString::number(Secadora->get_PreciosTarjeta(PROGRAMA_SECADO))));
           SecadoEfectivo = Secadora->get_PreciosEfectivo(PROGRAMA_SECADO);
           SecadoTarjeta = Secadora->get_PreciosTarjeta(PROGRAMA_SECADO);
           break;
       case 2:
           ui->Resumen_Secado->setText("Secadora número "+(QString::number(Secadora->get_numMaquina()))+
                                       "<br> Programa: Templado"+"<br>  Precio:"+(QString::number(Secadora->get_PreciosEfectivo(PROGRAMA_SECADO))));
           ui->Resumen_Secado_Tarjeta->setText("Secadora número "+(QString::number(Secadora->get_numMaquina()))+
                                       "<br> Programa: Templado"+"<br>  Precio:"+(QString::number(Secadora->get_PreciosTarjeta(PROGRAMA_SECADO))));
           SecadoEfectivo = Secadora->get_PreciosEfectivo(PROGRAMA_SECADO);
           SecadoTarjeta = Secadora->get_PreciosTarjeta(PROGRAMA_SECADO);
           break;
       case 3:
           ui->Resumen_Secado->setText("Secadora número "+(QString::number(Secadora->get_numMaquina()))+
                                       "<br> Programa: Frío"+"<br>  Precio:"+(QString::number(Secadora->get_PreciosEfectivo(PROGRAMA_SECADO))));
           ui->Resumen_Secado_Tarjeta->setText("Secadora número "+(QString::number(Secadora->get_numMaquina()))+
                                       "<br> Programa: Frío"+"<br>  Precio:"+(QString::number(Secadora->get_PreciosTarjeta(PROGRAMA_SECADO))));
           SecadoEfectivo = Secadora->get_PreciosEfectivo(PROGRAMA_SECADO);
           SecadoTarjeta = Secadora->get_PreciosTarjeta(PROGRAMA_SECADO);
           break;

       }

       //ui->Resumen_Secado->setText("Secadora número "+(QString::number(Secadora->get_numMaquina()))+" seleccionada. Precio: "+(QString::number(Secadora->get_PreciosEfectivo(PROGRAMA_SECADO))));
       break;
   default:
       break;
   }

   TotalEfectivo = SecadoEfectivo+(Secadora->get_PreciosEfectivo(MINUTO_SECADO)*TiempoExtra);
   TotalTarjeta = SecadoTarjeta+(Secadora->get_PreciosTarjeta(MINUTO_SECADO)*TiempoExtra);
   TotalPagoEfectivo = TotalEfectivo*100;
   TotalPagoTarjeta = TotalTarjeta*100;
   ui->Seleccion_Extra_Tiempo->setText("Tiempo Extra seleccionado = "+QString::number(TiempoExtra)+ " minutos. Precio: " +QString::number((Secadora->get_PreciosEfectivo(MINUTO_SECADO)*TiempoExtra))+"<br><br> TOTAL: "+QString::number(TotalEfectivo));
   ui->Seleccion_Extra_Tiempo->setWordWrap(true);
   ui->Seleccion_Extra_Tiempo_Tarjeta->setText("Tiempo Extra seleccionado = "+QString::number(TiempoExtra)+ " minutos. Precio: " +QString::number((Secadora->get_PreciosTarjeta(MINUTO_SECADO)*TiempoExtra))+"<br><br> TOTAL: "+QString::number(TotalTarjeta));
   ui->Seleccion_Extra_Tiempo_Tarjeta->setWordWrap(true);



    ui->stackedWidget->setCurrentIndex(13);
}

void MainWindow::on_B04_Back_14_clicked()
{
    emit PrinterFunction("CL");
    ventana7();
}

void MainWindow::on_B04_Back_15_clicked()
{
     emit PrinterFunction("CL");
     ui->stackedWidget->setCurrentIndex(12);

}

void MainWindow::onLecturaMoneda(float number)
{
    if(UltimaPagina==19)//Recarga tarjeta
    {


        if((TotalPago-number)>0)
        {
            TotalPago = TotalPago - number;
            cout << "TotalPago> = " << TotalPago<< endl;
            ui->intEfectivoRestante->setText(QString::number(TotalPago/100));

        }
        else if ((TotalPago-number)==0)
        {
            TotalPago = 0;
            cout << "TotalPago= = " << TotalPago<< endl;
            ui->intEfectivoRestante->setText("Pago Exacto");
            BaseDatos.RecargaTarjeta(K720_Dispenser.UltimaID,(RecargaTarjeta*100));
            K720_Dispenser.ExpulsarTarjeta();
            Sleep(2000);
            ui->stackedWidget->setCurrentIndex(0);
            player->play();
            EfectivoThread->Stop();
            EfectivoThread2->Stop();
        }
        else if((TotalPago-number)<0)
        {
            cout << "TotalPago< = " << TotalPago<< endl;
            EfectivoThread->SistemaMonedas.DevolucionMonedas(number-TotalPago);
            ui->intEfectivoRestante->setText("Devolución "+QString::number(number-TotalPago));
            TotalPago = 0;
            BaseDatos.RecargaTarjeta(K720_Dispenser.UltimaID,(RecargaTarjeta*100));
            K720_Dispenser.ExpulsarTarjeta();
            Sleep(2000);
            ui->stackedWidget->setCurrentIndex(0);
            player->play();
            EfectivoThread->Stop();
            EfectivoThread2->Stop();

        }
    }
    else if(UltimaPagina==16)//Crea Tarjeta
    {
        if((TotalPago-number)>0)
        {
            TotalPago = TotalPago - number;
            cout << "TotalPago> = " << TotalPago<< endl;
            ui->intEfectivoRestante->setText(QString::number(TotalPago/100));

        }
        else if ((TotalPago-number)==0)
        {
            TotalPago = 0;
            cout << "TotalPago= = " << TotalPago<< endl;
            HANDLE hComPortAux=NULL;

            QString saldo = NULL;
            QString saldoString =NULL;
            QString nombre = NULL;
            QString apellidos = NULL;
            QString LastID = NULL;
            QString strCardID = NULL;
            QString ntarj = NULL;
            QString ID = NULL;

            BYTE numCardAux = NULL;
            BYTE numCard[5];

            nombre = ui->NombreValor->text();
            apellidos = ui->ApellidosValor->text();
            saldoString = ui->intNuevTarjeta->text();
            saldo = ui->intNuevTarjeta->text();

           hComPortAux = K720_Dispenser.ConnectCOM();

           if(hComPortAux==0)
           {
               cout<<"Error de conexión al puerto del dispensador de tarjetas.";
           }

           bool dbConectado = BaseDatos.ConectarServidor();

           cout<<"dbConectado = "<<dbConectado<<endl;

           if (dbConectado)
           {
               K720_Dispenser.BaseDatos = BaseDatos;
           }

           LastID=BaseDatos.IDNuevoCliente();

           strCardID = K720_Dispenser.CrearTarjeta(nombre,apellidos,LastID);

           bool NuevoCliente = false;

           NuevoCliente = BaseDatos.NuevoCliente(nombre,apellidos,saldo,strCardID);

           if(NuevoCliente)
           {
               cout <<"Cliente creado correctamente"<<endl;

           }
           else
           {
               QMessageBox::critical(this,"Error","Error al crear el nuevo cliente");
           }


            Sleep(2000);
            ui->stackedWidget->setCurrentIndex(0);
            player->play();
            EfectivoThread->Stop();
            EfectivoThread2->Stop();
        }
        else if((TotalPago-number)<0)
        {
            cout << "TotalPago< = " << TotalPago<< endl;
            EfectivoThread->SistemaMonedas.DevolucionMonedas(number-TotalPago);
            ui->intEfectivoRestante->setText("Devolución "+QString::number(number-TotalPago));
            TotalPago = 0;

            HANDLE hComPortAux=NULL;

            QString saldo = NULL;
            QString saldoString =NULL;
            QString nombre = NULL;
            QString apellidos = NULL;
            QString LastID = NULL;
            QString strCardID = NULL;
            QString ntarj = NULL;
            QString ID = NULL;

            BYTE numCardAux = NULL;
            BYTE numCard[5];

            nombre = ui->NombreValor->text();
            apellidos = ui->ApellidosValor->text();
            saldoString = ui->intNuevTarjeta->text();
            saldo = ui->intNuevTarjeta->text();

           hComPortAux = K720_Dispenser.ConnectCOM();

           if(hComPortAux==0)
           {
               cout<<"Error de conexión al puerto del dispensador de tarjetas.";
           }

           bool dbConectado = BaseDatos.ConectarServidor();

           cout<<"dbConectado = "<<dbConectado<<endl;

           if (dbConectado)
           {
               K720_Dispenser.BaseDatos = BaseDatos;
           }

           LastID=BaseDatos.IDNuevoCliente();

           strCardID = K720_Dispenser.CrearTarjeta(nombre,apellidos,LastID);

           bool NuevoCliente = false;

           NuevoCliente = BaseDatos.NuevoCliente(nombre,apellidos,saldo,strCardID);

           if(NuevoCliente)
           {
               cout <<"Cliente creado correctamente"<<endl;

           }
           else
           {
               QMessageBox::critical(this,"Error","Error al crear el nuevo cliente");
           }

            Sleep(2000);
            ui->stackedWidget->setCurrentIndex(0);
            player->play();
            EfectivoThread->Stop();
            EfectivoThread2->Stop();

        }
    }
    else
    {


        if((TotalPago-number)>0)
        {
            TotalPago = TotalPago - number;
            cout << "TotalPago> = " << TotalPago<< endl;
            ui->intEfectivoRestante->setText(QString::number(TotalPago/100));

        }
        else if ((TotalPago-number)==0)
        {
            emit PrinterFunction("PR");


            TotalPago = 0;
            cout << "TotalPago= = " << TotalPago<< endl;
            if(UltimaPagina==8)
            {
                c_LogFile LogUI;
                QString Log = "Accionada la Lavadora ";
                Log.append(QString::number(Lavadora->numMaquina));
                Log.append(" en el programa ");
                Log.append(QString::number(Lavadora->numPrograma));
                Log.append(" con el código de extras ");
                Log.append(QString::number(Lavadora->numExtras));
                LogUI.InsertarLineaLog(Log);

                Lavadora->SendCmd(Lavadora->CmdProgramStartLav);

            }
            else if(UltimaPagina == 13)
            {
                cout <<"Envío comando comenzar secadora"<<endl;

                c_LogFile LogUI;
                QString Log = "Accionada la Secadora ";
                Log.append(QString::number(Secadora->numMaquina));
                Log.append(" en el programa ");
                Log.append(QString::number(Secadora->numPrograma));
                Log.append(" con un tiempo extra de ");
                Log.append(QString::number(Secadora->numTiempoExtra));
                LogUI.InsertarLineaLog(Log);

                Secadora->SendCmd(Secadora->CmdProgramStartSec);
                Sleep(10);
                Secadora->SendCmd(Secadora->CmdProgramSelectionSec);

            }
            Sleep(2000);
            ui->stackedWidget->setCurrentIndex(0);
            player->play();
            EfectivoThread->Stop();
            EfectivoThread2->Stop();
        }
        else if((TotalPago-number)<0)
        {
            emit PrinterFunction("PR");
            cout << "TotalPago< = " << TotalPago<< endl;
            EfectivoThread->SistemaMonedas.DevolucionMonedas(number-TotalPago);
            ui->intEfectivoRestante->setText("Devolución "+QString::number(number-TotalPago));
            TotalPago = 0;
            if(UltimaPagina==8)
            {
                c_LogFile LogUI;
                QString Log = "Accionada la Lavadora ";
                Log.append(QString::number(Lavadora->numMaquina));
                Log.append(" en el programa ");
                Log.append(QString::number(Lavadora->numPrograma));
                Log.append(" con el código de extras ");
                Log.append(QString::number(Lavadora->numExtras));
                LogUI.InsertarLineaLog(Log);

                Lavadora->SendCmd(Lavadora->CmdProgramStartLav);

            }
            else if(UltimaPagina == 13)
            {

                c_LogFile LogUI;
                QString Log = "Accionada la Secadora ";
                Log.append(QString::number(Secadora->numMaquina));
                Log.append(" en el programa ");
                Log.append(QString::number(Secadora->numPrograma));
                Log.append(" con un tiempo extra de ");
                Log.append(QString::number(Secadora->numTiempoExtra));
                LogUI.InsertarLineaLog(Log);

                cout <<"Envío comando comenzar secadora"<<endl;
                Secadora->SendCmd(Secadora->CmdProgramStartSec);
                Sleep(10);
                Secadora->SendCmd(Secadora->CmdProgramSelectionSec);

            }
            Sleep(2000);
            ui->stackedWidget->setCurrentIndex(0);
            player->play();
            EfectivoThread->Stop();
            EfectivoThread2->Stop();

        }
    }
}

void MainWindow::onLecturaBillete(float number)
{
    if(UltimaPagina==19)//Recarga tarjeta
    {
        if((TotalPago-number)>0)
        {
            TotalPago = TotalPago - number;
            cout << "TotalPago> = " << TotalPago<< endl;
            ui->intEfectivoRestante->setText(QString::number(TotalPago/100));

        }
        else if ((TotalPago-number)==0)
        {
            TotalPago = 0;
            cout << "TotalPago= = " << TotalPago<< endl;
            BaseDatos.RecargaTarjeta(K720_Dispenser.UltimaID,RecargaTarjeta*100);
            K720_Dispenser.ExpulsarTarjeta();
            Sleep(2000);
            ui->stackedWidget->setCurrentIndex(0);
            player->play();
            EfectivoThread->Stop();
            EfectivoThread2->Stop();
        }
        else if((TotalPago-number)<0)
        {
            cout << "TotalPago< = " << TotalPago<< endl;
            EfectivoThread->SistemaMonedas.DevolucionMonedas(number-TotalPago);
            ui->intEfectivoRestante->setText("Devolución "+QString::number(number-TotalPago));
            TotalPago = 0;
            BaseDatos.RecargaTarjeta(K720_Dispenser.UltimaID,RecargaTarjeta*100);
            K720_Dispenser.ExpulsarTarjeta();
            Sleep(2000);
            ui->stackedWidget->setCurrentIndex(0);
            player->play();
            EfectivoThread->Stop();
            EfectivoThread2->Stop();

        }
    }

    else if(UltimaPagina==16)//crea tarjeta
    {
        if((TotalPago-number)>0)
        {
            TotalPago = TotalPago - number;
            cout << "TotalPago> = " << TotalPago<< endl;
            ui->intEfectivoRestante->setText(QString::number(TotalPago/100));

        }
        else if ((TotalPago-number)==0)
        {
            TotalPago = 0;
            cout << "TotalPago= = " << TotalPago<< endl;
            HANDLE hComPortAux=NULL;

            QString saldo = NULL;
            QString saldoString =NULL;
            QString nombre = NULL;
            QString apellidos = NULL;
            QString LastID = NULL;
            QString strCardID = NULL;
            QString ntarj = NULL;
            QString ID = NULL;

            BYTE numCardAux = NULL;
            BYTE numCard[5];

            nombre = ui->NombreValor->text();
            apellidos = ui->ApellidosValor->text();
            saldoString = ui->intNuevTarjeta->text();
            saldo = ui->intNuevTarjeta->text();

           hComPortAux = K720_Dispenser.ConnectCOM();

           if(hComPortAux==0)
           {
               cout<<"Error de conexión al puerto del dispensador de tarjetas.";
           }

           bool dbConectado = BaseDatos.ConectarServidor();

           cout<<"dbConectado = "<<dbConectado<<endl;

           if (dbConectado)
           {
               K720_Dispenser.BaseDatos = BaseDatos;
           }

           LastID=BaseDatos.IDNuevoCliente();

           strCardID = K720_Dispenser.CrearTarjeta(nombre,apellidos,LastID);

           bool NuevoCliente = false;

           NuevoCliente = BaseDatos.NuevoCliente(nombre,apellidos,saldo,strCardID);

           if(NuevoCliente)
           {
               cout <<"Cliente creado correctamente"<<endl;

           }
           else
           {
               QMessageBox::critical(this,"Error","Error al crear el nuevo cliente");
           }


            Sleep(2000);
            ui->stackedWidget->setCurrentIndex(0);
            player->play();
            EfectivoThread->Stop();
            EfectivoThread2->Stop();
        }
        else if((TotalPago-number)<0)
        {
            cout << "TotalPago< = " << TotalPago<< endl;
            EfectivoThread->SistemaMonedas.DevolucionMonedas(number-TotalPago);
            ui->intEfectivoRestante->setText("Devolución "+QString::number(number-TotalPago));
            TotalPago = 0;

            HANDLE hComPortAux=NULL;

            QString saldo = NULL;
            QString saldoString =NULL;
            QString nombre = NULL;
            QString apellidos = NULL;
            QString LastID = NULL;
            QString strCardID = NULL;
            QString ntarj = NULL;
            QString ID = NULL;

            BYTE numCardAux = NULL;
            BYTE numCard[5];

            nombre = ui->NombreValor->text();
            apellidos = ui->ApellidosValor->text();
            saldoString = ui->intNuevTarjeta->text();
            saldo = ui->intNuevTarjeta->text();

           hComPortAux = K720_Dispenser.ConnectCOM();

           if(hComPortAux==0)
           {
               cout<<"Error de conexión al puerto del dispensador de tarjetas.";
           }

           bool dbConectado = BaseDatos.ConectarServidor();

           cout<<"dbConectado = "<<dbConectado<<endl;

           if (dbConectado)
           {
               K720_Dispenser.BaseDatos = BaseDatos;
           }

           LastID=BaseDatos.IDNuevoCliente();

           strCardID = K720_Dispenser.CrearTarjeta(nombre,apellidos,LastID);

           bool NuevoCliente = false;

           NuevoCliente = BaseDatos.NuevoCliente(nombre,apellidos,saldo,strCardID);

           if(NuevoCliente)
           {
               cout <<"Cliente creado correctamente"<<endl;

           }
           else
           {
               QMessageBox::critical(this,"Error","Error al crear el nuevo cliente");
           }

            Sleep(2000);
            ui->stackedWidget->setCurrentIndex(0);
            player->play();
            EfectivoThread->Stop();
            EfectivoThread2->Stop();

        }
    }
    else
    {


        if((TotalPago-number)>0)
        {
            TotalPago = TotalPago - number;
            cout << "TotalPago> = " << TotalPago<< endl;
            ui->intEfectivoRestante->setText(QString::number(TotalPago/100));

        }
        else if ((TotalPago-number)==0)
        {


           emit PrinterFunction("PR");

            TotalPago = 0;
            cout << "TotalPago= = " << TotalPago<< endl;

            if(UltimaPagina==8)
            {
                c_LogFile LogUI;
                QString Log = "Accionada la Lavadora ";
                Log.append(QString::number(Lavadora->numMaquina));
                Log.append(" en el programa ");
                Log.append(QString::number(Lavadora->numPrograma));
                Log.append(" con el código de extras ");
                Log.append(QString::number(Lavadora->numExtras));
                LogUI.InsertarLineaLog(Log);

                Lavadora->SendCmd(Lavadora->CmdProgramStartLav);

            }
            else if(UltimaPagina == 13)
            {
                c_LogFile LogUI;
                QString Log = "Accionada la Secadora ";
                Log.append(QString::number(Secadora->numMaquina));
                Log.append(" en el programa ");
                Log.append(QString::number(Secadora->numPrograma));
                Log.append(" con un tiempo extra de ");
                Log.append(QString::number(Secadora->numTiempoExtra));
                LogUI.InsertarLineaLog(Log);

                Secadora->SendCmd(Secadora->CmdProgramStartSec);
                Sleep(10);
                Secadora->SendCmd(Secadora->CmdProgramSelectionSec);


            }
            Sleep(2000);
            ui->stackedWidget->setCurrentIndex(0);
            player->play();
            EfectivoThread->Stop();
            EfectivoThread2->Stop();
        }
        else if((TotalPago-number)<0)
        {

            emit PrinterFunction("PR");

            cout << "TotalPago< = " << TotalPago<< endl;
            EfectivoThread->SistemaMonedas.DevolucionMonedas(number-TotalPago);
            ui->intEfectivoRestante->setText("Devolución "+QString::number(number-TotalPago));
            TotalPago = 0;
            if(UltimaPagina==8)
            {
                c_LogFile LogUI;
                QString Log = "Accionada la Lavadora ";
                Log.append(QString::number(Lavadora->numMaquina));
                Log.append(" en el programa ");
                Log.append(QString::number(Lavadora->numPrograma));
                Log.append(" con el código de extras ");
                Log.append(QString::number(Lavadora->numExtras));
                LogUI.InsertarLineaLog(Log);

                Lavadora->SendCmd(Lavadora->CmdProgramStartLav);

            }
            else if(UltimaPagina == 13)
            {

                c_LogFile LogUI;
                QString Log = "Accionada la Secadora ";
                Log.append(QString::number(Secadora->numMaquina));
                Log.append(" en el programa ");
                Log.append(QString::number(Secadora->numPrograma));
                Log.append(" con un tiempo extra de ");
                Log.append(QString::number(Secadora->numTiempoExtra));
                LogUI.InsertarLineaLog(Log);

                Secadora->SendCmd(Secadora->CmdProgramStartSec);
                Sleep(10);
                Secadora->SendCmd(Secadora->CmdProgramSelectionSec);


            }
            Sleep(2000);
            ui->stackedWidget->setCurrentIndex(0);
            player->play();
            EfectivoThread->Stop();
            EfectivoThread2->Stop();

        }
    }

}


void MainWindow::on_PagoEfectivo_2_clicked()
{


    UltimaPagina = 8;
    TotalPago = TotalPagoEfectivo;
    ui->intEfectivoRestante->setText(QString::number(TotalPago/100));
    ui->stackedWidget->setCurrentIndex(17);
    Lavadora->SendCmd(Lavadora->CmdProgramSelectionLav);

    if(EfectivoThread->isRunning())
    {
        EfectivoThread->Enable();
    }
    else
    {
        EfectivoThread->start();
    }



    EfectivoThread2->start(QThread::HighPriority);
}

void MainWindow::on_PagoEfectivo_clicked()
{
    UltimaPagina = 13;

    TotalPago = TotalPagoEfectivo;
    ui->intEfectivoRestante->setText(QString::number(TotalPago/100));
    ui->stackedWidget->setCurrentIndex(17);


    if(EfectivoThread->isRunning())
    {
        EfectivoThread->Enable();
    }
    else
    {
        EfectivoThread->start();
    }


    EfectivoThread2->start(QThread::HighPriority);
}

void MainWindow::on_B04_Back_16_clicked()
{
    ui->stackedWidget->setCurrentIndex(UltimaPagina);
    K720_Dispenser.ExpulsarTarjeta();
    if(EfectivoThread->isRunning())    EfectivoThread->terminate();
    if(EfectivoThread2->BillReadThread->isRunning()) EfectivoThread2->BillReadThread->terminate();
    if(EfectivoThread2->isRunning()) EfectivoThread2->terminate();

}

void MainWindow::on_PagoTarjeta_2_clicked()
{

    SaldoTarjeta = 0;
    UltimaPagina = 8;

    //K720_Dispenser.EnableMouth();
    TotalPago = TotalPagoTarjeta;
    ui->intPagarTarjeta->setText(QString::number(TotalPago/100));
    ui->intSaldoTarjeta->setText("");
    ui->textPagoTarjeta->setText("Por favor inserte su tarjeta RFID");
    Lavadora->SendCmd(Lavadora->CmdProgramSelectionLav);





    ui->stackedWidget->setCurrentIndex(18);

    TarjetaThread->start();




}

void MainWindow::on_B04_Back_17_clicked()
{
    K720_Dispenser.ExpulsarTarjeta();
    if(EfectivoThread->isRunning())    EfectivoThread->terminate();
    if(EfectivoThread2->BillReadThread->isRunning()) EfectivoThread2->BillReadThread->terminate();
    if(EfectivoThread2->isRunning()) EfectivoThread2->terminate();

    ui->stackedWidget->setCurrentIndex(UltimaPagina);
}

void MainWindow::on_PagoTarjeta_3_clicked()
{

    K720_Dispenser.DisableMouth();
    Sleep(100);
    if(TotalPago<=SaldoTarjeta)
    {
        QString auxID = K720_Dispenser.UltimaID;
        bool check = false;
        SaldoTarjeta = SaldoTarjeta-TotalPago;

        cout << "Ultima ID = "<<auxID.toStdString()<<endl;



        if(BaseDatos.NuevoSaldo(auxID,SaldoTarjeta))
        {
            cout << "Actualizado saldo "<< SaldoTarjeta <<endl;
            ui->stackedWidget->setCurrentIndex(0);
            player->play();
            K720_Dispenser.ExpulsarTarjeta();
        }
        else
        {
            QMessageBox::critical(this, "Error en base de datos","No acutalizado el nuevo saldo");
            cout <<"Saldo error = "<<SaldoTarjeta;
            ui->stackedWidget->setCurrentIndex(0);
            player->play();
            K720_Dispenser.ExpulsarTarjeta();
        }
    }
    else if(TotalPago>SaldoTarjeta)
    {
        ui->textPagoTarjeta->setText("Saldo insuficiente. Recargue Tarjeta");
    }

}






void MainWindow::onLecturaTarjeta(float number)
{



    if(number==100)
    {
        Sleep(100);
        K720_Dispenser.BaseDatos=BaseDatos;

        SaldoTarjeta = K720_Dispenser.LeerTarjeta();


        if(SaldoTarjeta==999)
        {
            ui->textPagoTarjeta->setText("Tarjeta Errónea o tiempo de espera superado");
            Sleep(3000);
            ui->stackedWidget->setCurrentIndex(0);
            player->play();
            K720_Dispenser.DisableMouth();
        }
        else
        {
            ui->intSaldoTarjeta->setText(QString::number(SaldoTarjeta/100));
            ui->textPagoTarjeta->setText("Tarjeta Correcta");
            K720_Dispenser.DisableMouth();
            if(UltimaPagina==8)
            {
                Lavadora->SendCmd(Lavadora->CmdProgramStartLav);

            }
            else if(UltimaPagina == 13)
            {
                Secadora->SendCmd(Secadora->CmdProgramStartSec);
                Sleep(10);
                Secadora->SendCmd(Secadora->CmdProgramSelectionSec);


            }
        }
    }
    else if(number==33)
    {
        Sleep(1000);
        K720_Dispenser.BaseDatos=BaseDatos;

        SaldoTarjeta = K720_Dispenser.LeerTarjeta();


        if(SaldoTarjeta==999)
        {
            ui->textPagoTarjeta->setText("Tarjeta Errónea o tiempo de espera superado");
            Sleep(3000);
            ui->stackedWidget->setCurrentIndex(0);
            player->play();
            K720_Dispenser.DisableMouth();
        }
        else
        {
            ui->intSaldoActual->setText(QString::number(SaldoTarjeta/100));
            ui->intRecarga->setText(QString::number(RecargaTarjeta));
            RecargaTarjeta =0;
            ui->intRecarga->setText("0");
            ui->stackedWidget->setCurrentIndex(19);
            K720_Dispenser.DisableMouth();



        }

    }
    else cout<<"Orden del hilo incorrecta";
    K720_Dispenser.DisableMouth();

}

void MainWindow::on_B04_Back_18_clicked()
{
    ui->stackedWidget->setCurrentIndex(UltimaPagina);
    K720_Dispenser.ExpulsarTarjeta();
    if(EfectivoThread->isRunning())    EfectivoThread->terminate();
    if(EfectivoThread2->BillReadThread->isRunning()) EfectivoThread2->BillReadThread->terminate();
    if(EfectivoThread2->isRunning()) EfectivoThread2->terminate();
}

void MainWindow::on_B15_Adelante_7_clicked()
{
    UltimaPagina = 19;
    TotalPago = RecargaTarjeta*100;
    ui->intEfectivoRestante->setText(QString::number(TotalPago/100));
    ui->intRecarga->setText("0");
    ui->stackedWidget->setCurrentIndex(17);


    if(EfectivoThread->isRunning())
    {
        EfectivoThread->Enable();
    }
    else
    {
        EfectivoThread->start();
    }

    EfectivoThread2->start(QThread::HighPriority);
}


void MainWindow::on_Menos1_clicked()
{
    if(RecargaTarjeta>0)
    {
        RecargaTarjeta = RecargaTarjeta -1;
        ui->intRecarga->setText(QString::number(RecargaTarjeta));
    }
}

void MainWindow::on_Menos5_clicked()
{
    if(RecargaTarjeta>0)
    {
        RecargaTarjeta = RecargaTarjeta - 5;
        ui->intRecarga->setText(QString::number(RecargaTarjeta));
    }

}

void MainWindow::on_Mas1_clicked()
{
    if(RecargaTarjeta<=50)
    {
        RecargaTarjeta = RecargaTarjeta + 1;
        ui->intRecarga->setText(QString::number(RecargaTarjeta));
    }
}

void MainWindow::on_Mas5_clicked()
{
    if(RecargaTarjeta<=50)
    {
        RecargaTarjeta = RecargaTarjeta + 5;
        ui->intRecarga->setText(QString::number(RecargaTarjeta));
    }
}

void MainWindow::on_RecargaTarjeta_clicked()
{
    RecargaTarjeta = 0;
    UltimaPagina = 18;
    K720_Dispenser.DisableMouth();
    ui->intRecarga->setText(QString::number(RecargaTarjeta));
    ui->intSaldoActual->setText(QString::number(SaldoTarjeta/100));
    ui->stackedWidget->setCurrentIndex(19);
    ui->intRecarga->setText("0");
}

void MainWindow::on_B04_Back_19_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    if(TarjetaThread->isRunning())
    {
        TarjetaThread->terminate();
    }
   // TarjetaThread->Function=33;
   // TarjetaThread->start();

    K720_Dispenser.ExpulsarTarjeta();
    if(EfectivoThread->isRunning())    EfectivoThread->terminate();
    if(EfectivoThread2->BillReadThread->isRunning()) EfectivoThread2->BillReadThread->terminate();
    if(EfectivoThread2->isRunning()) EfectivoThread2->terminate();
}

void MainWindow::on_PagoTarjeta_clicked()
{
    SaldoTarjeta = 0;
    UltimaPagina = 13;

    //K720_Dispenser.EnableMouth();
    TotalPago = TotalPagoTarjeta;
    ui->intPagarTarjeta->setText(QString::number(TotalPago/100));
    ui->intSaldoTarjeta->setText("");
    ui->textPagoTarjeta->setText("Por favor inserte su tarjeta RFID");





    ui->stackedWidget->setCurrentIndex(18);

    TarjetaThread->start();
}



void MainWindow::onEventoImpresora(int evento)
{
    cout <<"Evento onEventoImpresora del principal"<<endl;

}



void MainWindow::on_pushButton_14_clicked()
{

}

void MainWindow::on_B04_Ajustes_clicked()
{
     ui->stackedWidget->setCurrentIndex(14);
}

void MainWindow::on_B04_Back_24_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_B05_Administracion_clicked()
{
    ui->stackedWidget->setCurrentIndex(25);
}

void MainWindow::on_B06_Clientes_clicked()
{
    ui->stackedWidget->setCurrentIndex(21);
}

void MainWindow::on_B07_TarifasPromo_clicked()
{
    ui->stackedWidget->setCurrentIndex(26);
}

void MainWindow::on_IdentificacionTarjeta_clicked()
{
    ui->stackedWidget->setCurrentIndex(23);
}

void MainWindow::on_GestionTarjetas_clicked()
{
    ui->stackedWidget->setCurrentIndex(22);
}

void MainWindow::on_TarjetaAdmin_clicked()
{
    ui->stackedWidget->setCurrentIndex(24);
}

void MainWindow::on_B04_Back_21_clicked()
{
    ui->stackedWidget->setCurrentIndex(14);
}

void MainWindow::on_B04_Back_20_clicked()
{
    ui->stackedWidget->setCurrentIndex(21);
}

void MainWindow::on_B04_Back_22_clicked()
{
    ui->stackedWidget->setCurrentIndex(21);
}

void MainWindow::on_B04_Back_23_clicked()
{
    ui->stackedWidget->setCurrentIndex(21);
}

void MainWindow::on_B04_Back_25_clicked()
{
    ui->stackedWidget->setCurrentIndex(14);
}



void MainWindow::on_BtnConfigMaq_clicked()
{
     ui->stackedWidget->setCurrentIndex(29);
}

void MainWindow::on_B04_Back_27_clicked()
{
     ui->stackedWidget->setCurrentIndex(30);
}

void MainWindow::on_NuevoCliente_2_clicked()
{
     ui->stackedWidget->setCurrentIndex(30);
}

void MainWindow::on_B04_Back_28_clicked()
{
    ui->stackedWidget->setCurrentIndex(25);
}

void MainWindow::on_BtnLavadora_clicked()
{
    ui->stackedWidget->setCurrentIndex(29);
}

void MainWindow::on_BtnActualizar_clicked()
{
    int Maquina = 0;
    int Programa = 0;
    int NumMaquinas = 0;
    int NumProgramas = 0;
    string Comando;

   /* Lavadora->set_CmdNumMaq((unsigned char)ui->BoxSelMaq->currentIndex());
    printf("Lavadora index = %x\n",(unsigned char)ui->BoxSelMaq->currentIndex());
    Lavadora->set_CmdNumProgram((unsigned char) ui->BoxSelProg->currentIndex());
    for(int i=1;i<=6;i++)
    {
        Lavadora->set_CmdNumFase((unsigned char)i);
        printf("Lavadora phase = %x\n",(unsigned char)i);
        //Sleep(100);

        Lavadora->SendCmd(Lavadora->CmdReadPhaseLav);
        Sleep(100);
    }*/



    unsigned char IDMaquina = ((unsigned char) ui->BoxSelMaq->currentIndex());// Aquí está el hexadecimal con el numero de identificación de la máquina
    unsigned char IDPrograma = ((unsigned char) ui->BoxSelProg->currentIndex());//Aquí está el hexadecimal con el número de programa seleccionado
    cout<<"Máquina seleccionada" <<IDMaquina<<endl;
    cout<<"Programa Seleciionado" << IDPrograma<<endl;

    if(IDMaquina == 0x00||IDPrograma==0x00)
    {
        QMessageBox::information(this,"Selección No Válida","Por favor seleccione una máquina y un programa");
    }
    else
    {
        Comando.resize(2);
        Comando[0]=IDMaquina;
        Comando[1]=IDPrograma;
        emit ActualizarConfiguracionLav(Comando);
    }
  //  NumMaquinas = ui->BoxSelMaq->maxCount();
  //  NumProgramas = ui->BoxSelProg->maxCount();

   // unsigned char IDMaquina = ((unsigned char) Maquina);

    printf("Hola %x",IDMaquina);

    cout<<"Hola"<<endl;


}

void MainWindow::onLecturaLavadora(string buffer)
{

    int SizeMensaje =QString::fromStdString(buffer).count();
    cout << "Llegada emision"<<endl<<SizeMensaje<<endl<<buffer.length();
    string AuxMensaje;// = LecturaLavadorasThread->BufferAuxiliar;
    AuxMensaje.append(buffer);
    cout << "Llegada emision"<<endl<<SizeMensaje<<endl<<buffer.length()<<endl<<AuxMensaje.length()<<endl;
    for(int i = 0; i<SizeMensaje ;i++)
    {
        //AuxMensaje[i]=LecturaLavadorasThread->BufferAuxiliar[i];
        printf("Llegada emision. Byte %d = %x. /n %x",i,AuxMensaje[i],buffer[i]);
    }

    cout << "Pasado Mensaje"<<endl;

    switch (AuxMensaje[1]) {
    case 0x0a:
    {
        int LongitudMensaje = 14;
        //unsigned char AuxMensaje[LongitudMensaje];

        unsigned char NumMaq = AuxMensaje[0];
        unsigned char Alarma = AuxMensaje[4];
        unsigned char TiempoRestante = AuxMensaje[2];
        unsigned char ProgramaEjeucion = AuxMensaje[3];
        unsigned char EstadoPuerta = AuxMensaje[7];
        string ErrorLavadoraAux;
        ErrorLavadoraAux.resize(2);
        if(Alarma != 0 || TiempoRestante !=0 || ProgramaEjeucion !=0)
        {
            cout << "Lavadora no disponible"<<endl;
            if(Alarma !=0)
            {

                printf("Alarma Lavadora número %x = %x",NumMaq,Alarma);
                ErrorLavadoraAux[0] = NumMaq;
                ErrorLavadoraAux[1] = Alarma;
                RegistroErroresLav(ErrorLavadoraAux);

                switch (NumMaq) {
                case 0x01:
                    ui->B09_Lavadora01->setIcon(QIcon(":/Iconos/material/iconos/icono_lavar_tamañokg01.png"));
                    //ui->B09_Lavadora01->set

                    cout<<"Pasado por el cambio de icono del primer botón"<<endl;
                    break;
                case 0x02:
                    ui->B10_Lavadora02->setIcon(QIcon(":/Iconos/material/iconos/icono_lavar_tamañokg01.png"));
                    break;
                case 0x03:
                    ui->B11_Lavadora03->setIcon(QIcon(":/Iconos/material/iconos/icono_lavar_tamañokg02.png"));
                    break;
                case 0x04:
                    ui->B12_Lavadora04->setIcon(QIcon(":/Iconos/material/iconos/icono_lavar_tamañokg02.png"));
                    break;
                case 0x05:
                    ui->B13_Lavadora05->setIcon(QIcon(":/Iconos/material/iconos/icono_lavar_tamañokg03.png"));
                    break;
                case 0x06:
                    ui->B14_Lavadora06->setIcon(QIcon(":/Iconos/material/iconos/icono_lavar_tamañokg03.png"));
                    break;

                default:
                    break;
                }



                //Poner lavadora en gris
            }
            else
            {

                switch (NumMaq) {
                case 0x01:
                    ui->B09_Lavadora01->setIcon(QIcon(":/Iconos/material/iconos/icono_lavar_tamañokg01 - Rojo.png"));
                    cout<<"Pasado por el cambio de icono del primer botón"<<endl;
                    break;
                case 0x02:
                    ui->B10_Lavadora02->setIcon(QIcon(":/Iconos/material/iconos/icono_lavar_tamañokg01 - Rojo.png"));
                    break;
                case 0x03:
                    ui->B11_Lavadora03->setIcon(QIcon(":/Iconos/material/iconos/icono_lavar_tamañokg02 - Rojo.png"));
                    break;
                case 0x04:
                    ui->B12_Lavadora04->setIcon(QIcon(":/Iconos/material/iconos/icono_lavar_tamañokg02 - Rojo.png"));
                    break;
                case 0x05:
                    ui->B13_Lavadora05->setIcon(QIcon(":/Iconos/material/iconos/icono_lavar_tamañokg03 - Rojo.png"));
                    break;
                case 0x06:
                    ui->B14_Lavadora06->setIcon(QIcon(":/Iconos/material/iconos/icono_lavar_tamañokg03 - Rojo.png"));
                    break;

                default:
                    break;
                }

                //Poner lavadora en rojo

            }

        }
        else if (Alarma == 0 && TiempoRestante == 0 && ProgramaEjeucion == 0 )
        {
            cout<< "Lavadora disponible"<<endl;
            //Poner en verde la pantalla de la lavadora
            switch (NumMaq) {
            case 0x01:
                ui->B09_Lavadora01->setIcon(QIcon(":/Iconos/material/iconos/icono_lavar_tamañokg01 - Verde.png"));
                cout<<"Pasado por el cambio de icono del primer botón"<<endl;
                break;
            case 0x02:
                ui->B10_Lavadora02->setIcon(QIcon(":/Iconos/material/iconos/icono_lavar_tamañokg01 - Verde.png"));
                break;
            case 0x03:
                ui->B11_Lavadora03->setIcon(QIcon(":/Iconos/material/iconos/icono_lavar_tamañokg02 - Verde.png"));
                break;
            case 0x04:
                ui->B12_Lavadora04->setIcon(QIcon(":/Iconos/material/iconos/icono_lavar_tamañokg02 - Verde.png"));
                break;
            case 0x05:
                ui->B13_Lavadora05->setIcon(QIcon(":/Iconos/material/iconos/icono_lavar_tamañokg03 - Verde.png"));
                break;
            case 0x06:
                ui->B14_Lavadora06->setIcon(QIcon(":/Iconos/material/iconos/icono_lavar_tamañokg03 - Verde.png"));
                break;

            default:
                break;
            }

        }

        if(EstadoPuerta == 0x01)
        {
            PuertaAbierta = true;

        }
        else
        {
            PuertaAbierta = false;
            if(ui->stackedWidget->currentIndex()==5)
            {
                ui->stackedWidget->setCurrentIndex(6);
                Lavadora->terminate();
            }
        }

        break;

    }
    case 0x76:
    {
        int LongitudMensaje = 15;
        //unsigned char AuxMensaje[LongitudMensaje];

        unsigned char NumMaq = AuxMensaje[0];
        unsigned char NumProg = AuxMensaje[2];
        unsigned char NumFase = AuxMensaje[3];
        unsigned char Habilitar = AuxMensaje[4];
        unsigned char NivelBano = AuxMensaje[5];
        unsigned char Temperatura = AuxMensaje[6];
        unsigned char Dosificacion = AuxMensaje[7];
        unsigned char AccionMecanica = AuxMensaje[8];
        unsigned char TiempoRotacion = AuxMensaje[9];
        unsigned char Centrifugado = AuxMensaje[10];
        unsigned char TiempoCentrifugado = AuxMensaje[11];
        unsigned char TiempoDosificacion = AuxMensaje[16];

        switch (NumFase)
        {
        case 0x01:
        {



            int AuxDosi = (int)Dosificacion;

            ui->ComboNivelBano1->setCurrentIndex((int)NivelBano);
            ui->ComboAccionMec1->setCurrentIndex(((int)AccionMecanica));
            ui->ComboTiempoRot1->setCurrentIndex(((int)TiempoRotacion));
            ui->ComboCentrifugado1->setCurrentIndex(((int)Centrifugado));
            ui->ComboTiempoDosi1->setCurrentIndex((int)TiempoDosificacion-1);
            if((int)TiempoCentrifugado==0||(int)Centrifugado == 1||(int)Centrifugado == 0)
            {
                ui->ComboTiempoCentri1->setCurrentIndex(0);
            }
            else
            {
                ui->ComboTiempoCentri1->setCurrentIndex(((int)TiempoCentrifugado)-1);
            }
            ui->ComboHabilitar1->setCurrentIndex((int)Habilitar);

            if(AuxDosi>5)
            {
                switch(AuxDosi)
                {
                    case 12:
                    {
                      ui->ComboDosi1->setCurrentIndex(5);
                    break;
                    }
                    case 13:
                    {
                      ui->ComboDosi1->setCurrentIndex(6);
                    break;
                    }
                    case 14:
                    {
                      ui->ComboDosi1->setCurrentIndex(7);
                    break;
                    }
                    case 23:
                    {
                      ui->ComboDosi1->setCurrentIndex(8);
                    break;
                    }
                    case 24:
                    {
                      ui->ComboDosi1->setCurrentIndex(9);
                    break;
                    }
                    case 34:
                    {
                      ui->ComboDosi1->setCurrentIndex(10);
                    break;
                    }
                }
            }
            else
            {
                ui->ComboDosi1->setCurrentIndex(AuxDosi);
            }

            break;
        }


        case 0x02:
        {
            int TempAux = (int)Temperatura;


            int AuxDosi = (int)Dosificacion;


            ui->ComboNivelBano2->setCurrentIndex((int)NivelBano);

            if(TempAux >= 0 && TempAux<=17) ui->ComboTemperatura2->setCurrentIndex(0);
            else if(TempAux > 18 && TempAux<=23) ui->ComboTemperatura2->setCurrentIndex(1);
            else if(TempAux > 23 && TempAux<=27) ui->ComboTemperatura2->setCurrentIndex(2);
            else if(TempAux > 27 && TempAux<=33) ui->ComboTemperatura2->setCurrentIndex(3);
            else if(TempAux > 33 && TempAux<=37) ui->ComboTemperatura2->setCurrentIndex(4);
            else if(TempAux > 37 && TempAux<=43) ui->ComboTemperatura2->setCurrentIndex(5);
            else if(TempAux > 43 && TempAux<=47) ui->ComboTemperatura2->setCurrentIndex(6);
            else if(TempAux > 47 && TempAux<=53) ui->ComboTemperatura2->setCurrentIndex(7);
            else if(TempAux > 53 && TempAux<=57) ui->ComboTemperatura2->setCurrentIndex(8);
            else if(TempAux > 57 && TempAux<=63) ui->ComboTemperatura2->setCurrentIndex(9);
            else if(TempAux > 63 && TempAux<=90) ui->ComboTemperatura2->setCurrentIndex(10);


            ui->ComboAccionMec2->setCurrentIndex(((int)AccionMecanica)-1);
            ui->ComboTiempoRot2->setCurrentIndex(((int)TiempoRotacion));
            ui->ComboCentrifugado2->setCurrentIndex(((int)Centrifugado));
            ui->ComboTiempoDosi2->setCurrentIndex((int)TiempoDosificacion-1);
            if(AuxDosi>5)
            {
                switch(AuxDosi)
                {
                    case 12:
                    {
                      ui->ComboDosi2->setCurrentIndex(5);
                    break;
                    }
                    case 13:
                    {
                      ui->ComboDosi2->setCurrentIndex(6);
                    break;
                    }
                    case 14:
                    {
                      ui->ComboDosi2->setCurrentIndex(7);
                    break;
                    }
                    case 23:
                    {
                      ui->ComboDosi2->setCurrentIndex(8);
                    break;
                    }
                    case 24:
                    {
                      ui->ComboDosi2->setCurrentIndex(9);
                    break;
                    }
                    case 34:
                    {
                      ui->ComboDosi2->setCurrentIndex(10);
                    break;
                    }
                }
            }

            else
            {
                ui->ComboDosi2->setCurrentIndex(AuxDosi);
            }

            if((int)TiempoCentrifugado==0||(int)Centrifugado == 1||(int)Centrifugado == 0)
            {
                ui->ComboTiempoCentri2->setCurrentIndex(0);
            }
            else
            {
                ui->ComboTiempoCentri2->setCurrentIndex(((int)TiempoCentrifugado)-1);
            }
            ui->ComboHabilitar2->setCurrentIndex((int)Habilitar);


             break;
        }



        case 0x03:
        {
            int AuxDosi = (int)Dosificacion;


            ui->ComboNivelBano3->setCurrentIndex((int)NivelBano);



            ui->ComboAccionMec3->setCurrentIndex(((int)AccionMecanica)-1);
            ui->ComboTiempoRot3->setCurrentIndex(((int)TiempoRotacion));
            ui->ComboCentrifugado3->setCurrentIndex(((int)Centrifugado));
            ui->ComboTiempoDosi3->setCurrentIndex((int)TiempoDosificacion-1);

            if(AuxDosi>5)
            {
                switch(AuxDosi)
                {
                    case 12:
                    {
                      ui->ComboDosi3->setCurrentIndex(5);
                    break;
                    }
                    case 13:
                    {
                      ui->ComboDosi3->setCurrentIndex(6);
                    break;
                    }
                    case 14:
                    {
                      ui->ComboDosi3->setCurrentIndex(7);
                    break;
                    }
                    case 23:
                    {
                      ui->ComboDosi3->setCurrentIndex(8);
                    break;
                    }
                    case 24:
                    {
                      ui->ComboDosi3->setCurrentIndex(9);
                    break;
                    }
                    case 34:
                    {
                      ui->ComboDosi3->setCurrentIndex(10);
                    break;
                    }
                }
            }

            else
            {
                ui->ComboDosi3->setCurrentIndex(AuxDosi);
            }

            if((int)TiempoCentrifugado==0||(int)Centrifugado == 1||(int)Centrifugado == 0)
            {
                ui->ComboTiempoCentri3->setCurrentIndex(0);
            }
            else
            {
                ui->ComboTiempoCentri3->setCurrentIndex(((int)TiempoCentrifugado)-1);
            }

            ui->ComboHabilitar3->setCurrentIndex((int)Habilitar);

             break;


        }

        case 0x04:
        {
            int AuxDosi = (int)Dosificacion;


            ui->ComboNivelBano4->setCurrentIndex((int)NivelBano);
            ui->ComboAccionMec4->setCurrentIndex(((int)AccionMecanica)-1);
            ui->ComboTiempoRot4->setCurrentIndex(((int)TiempoRotacion));
            ui->ComboCentrifugado4->setCurrentIndex(((int)Centrifugado));


            if(AuxDosi>5)
            {
                switch(AuxDosi)
                {
                    case 12:
                    {
                      ui->ComboDosi4->setCurrentIndex(5);
                    break;
                    }
                    case 13:
                    {
                      ui->ComboDosi4->setCurrentIndex(6);
                    break;
                    }
                    case 14:
                    {
                      ui->ComboDosi4->setCurrentIndex(7);
                    break;
                    }
                    case 23:
                    {
                      ui->ComboDosi4->setCurrentIndex(8);
                    break;
                    }
                    case 24:
                    {
                      ui->ComboDosi4->setCurrentIndex(9);
                    break;
                    }
                    case 34:
                    {
                      ui->ComboDosi4->setCurrentIndex(10);
                    break;
                    }
                }
            }

            else
            {
                ui->ComboDosi4->setCurrentIndex(AuxDosi);
            }

            ui->ComboTiempoDosi4->setCurrentIndex((int)TiempoDosificacion-1);

            if((int)TiempoCentrifugado==0||(int)Centrifugado == 1||(int)Centrifugado == 0)
            {
                ui->ComboTiempoCentri4->setCurrentIndex(0);
            }
            else
            {
                ui->ComboTiempoCentri4->setCurrentIndex(((int)TiempoCentrifugado)-1);
            }

            ui->ComboHabilitar4->setCurrentIndex((int)Habilitar);

             break;
        }

        case 0x05:
        {
            int AuxDosi = (int)Dosificacion;


            ui->ComboNivelBano5->setCurrentIndex((int)NivelBano);
            ui->ComboAccionMec5->setCurrentIndex(((int)AccionMecanica)-1);
            ui->ComboTiempoRot5->setCurrentIndex(((int)TiempoRotacion));
            ui->ComboCentrifugado5->setCurrentIndex(((int)Centrifugado));

            if(AuxDosi>5)
            {
                switch(AuxDosi)
                {
                    case 12:
                    {
                      ui->ComboDosi5->setCurrentIndex(5);
                    break;
                    }
                    case 13:
                    {
                      ui->ComboDosi5->setCurrentIndex(6);
                    break;
                    }
                    case 14:
                    {
                      ui->ComboDosi5->setCurrentIndex(7);
                    break;
                    }
                    case 23:
                    {
                      ui->ComboDosi5->setCurrentIndex(8);
                    break;
                    }
                    case 24:
                    {
                      ui->ComboDosi5->setCurrentIndex(9);
                    break;
                    }
                    case 34:
                    {
                      ui->ComboDosi5->setCurrentIndex(10);
                    break;
                    }
                }
            }

            else
            {
                ui->ComboDosi5->setCurrentIndex(AuxDosi);
            }

            if((int)TiempoCentrifugado==0||(int)Centrifugado == 1||(int)Centrifugado == 0)
            {
                ui->ComboTiempoCentri5->setCurrentIndex(0);
            }
            else
            {
                ui->ComboTiempoCentri5->setCurrentIndex(((int)TiempoCentrifugado)-1);
            }

            ui->ComboTiempoDosi5->setCurrentIndex((int)TiempoDosificacion-1);

            ui->ComboHabilitar5->setCurrentIndex((int)Habilitar);

             break;
        }

        case 0x06:
        {
            int AuxDosi = (int)Dosificacion;




            ui->ComboNivelBano6->setCurrentIndex((int)NivelBano-1);



            ui->ComboAccionMec6->setCurrentIndex(((int)AccionMecanica)-1);
            ui->ComboTiempoRot6->setCurrentIndex(((int)TiempoRotacion)-1);
            ui->ComboCentrifugado6->setCurrentIndex(((int)Centrifugado)-1);
            ui->ComboTiempoDosi6->setCurrentIndex((int)TiempoDosificacion-1);

            if(AuxDosi>5)
            {
                switch(AuxDosi)
                {
                    case 12:
                    {
                      ui->ComboDosi6->setCurrentIndex(5);
                    break;
                    }
                    case 13:
                    {
                      ui->ComboDosi6->setCurrentIndex(6);
                    break;
                    }
                    case 14:
                    {
                      ui->ComboDosi6->setCurrentIndex(7);
                    break;
                    }
                    case 23:
                    {
                      ui->ComboDosi6->setCurrentIndex(8);
                    break;
                    }
                    case 24:
                    {
                      ui->ComboDosi6->setCurrentIndex(9);
                    break;
                    }
                    case 34:
                    {
                      ui->ComboDosi6->setCurrentIndex(10);
                    break;
                    }
                }
            }

            else
            {
                ui->ComboDosi6->setCurrentIndex(AuxDosi);
            }

            if((int)TiempoCentrifugado==0||(int)Centrifugado == 1||(int)Centrifugado == 0)
            {
                ui->ComboTiempoCentri6->setCurrentIndex(0);
            }
            else
            {
                ui->ComboTiempoCentri6->setCurrentIndex(((int)TiempoCentrifugado)-1);
            }

             break;
        }


        }

        break;
    }
       // case
    //default:
      //  break;
    }


}

void MainWindow::onLecturaSecadora(string buffer)
{
    int SizeMensaje =QString::fromStdString(buffer).count();
    cout << "Llegada emision"<<endl<<SizeMensaje<<endl<<buffer.length();
    string AuxMensaje;// = LecturaLavadorasThread->BufferAuxiliar;
    AuxMensaje.append(buffer);
    cout << "Llegada emision"<<endl<<SizeMensaje<<endl<<buffer.length()<<endl<<AuxMensaje.length()<<endl;
    for(int i = 0; i<SizeMensaje ;i++)
    {
        //AuxMensaje[i]=LecturaLavadorasThread->BufferAuxiliar[i];
        printf("Llegada emision. Byte %d = %x. /n %x",i,AuxMensaje[i],buffer[i]);
    }

    cout << "Pasado Mensaje"<<endl;

    switch (AuxMensaje[1])
    {
    case 0x0a:
    {
        int LongitudMensaje = 14;
        //unsigned char AuxMensaje[LongitudMensaje];

        unsigned char NumMaq = AuxMensaje[0];
        unsigned char Alarma = AuxMensaje[4];
        unsigned char TiempoRestante = AuxMensaje[2];
        unsigned char ProgramaEjeucion = AuxMensaje[3];
        unsigned char EstadoPuerta = AuxMensaje[7];

        string ErrorSecadoraAux;
        ErrorSecadoraAux.resize(2);

        if(Alarma != 0 || TiempoRestante !=0 || ProgramaEjeucion !=0)
        {
            cout << "Secadora no disponible"<<endl;
            if(Alarma !=0)
            {

                printf("Alarma Secadora número %x = %x",NumMaq,Alarma);
                ErrorSecadoraAux[0]=NumMaq;
                ErrorSecadoraAux[1]=Alarma;
                printf("Alarma Secadora array = %x,%x",ErrorSecadoraAux[0],ErrorSecadoraAux[1]);
                RegistroErroresSec(ErrorSecadoraAux);

                switch (NumMaq) {
                case 0x01:
                    ui->B09_Secadora1->setIcon(QIcon(":/Iconos/material/iconos/icono_secadoratamañokg00.png"));
                    //ui->B09_Lavadora01->set

                    cout<<"Pasado por el cambio de icono del primer botón"<<endl;
                    break;
                case 0x02:
                    ui->B10_Secadora2->setIcon(QIcon(":/Iconos/material/iconos/icono_secadoratamañokg00.png"));
                    break;
                case 0x03:
                    ui->B11_Secadora3->setIcon(QIcon(":/Iconos/material/iconos/icono_secadoratamañokg01.png"));
                    break;
                case 0x04:
                    ui->B12_Secadora4->setIcon(QIcon(":/Iconos/material/iconos/icono_secadoratamañokg01.png"));
                    break;
                case 0x05:
                    ui->B13_Secadora5->setIcon(QIcon(":/Iconos/material/iconos/icono_secadoratamañokg02.png"));
                    break;
                case 0x06:
                    ui->B14_Secadora6->setIcon(QIcon(":/Iconos/material/iconos/icono_secadoratamañokg02.png"));
                    break;

                default:
                    break;
                }


                //Poner lavadora en gris
            }
            else
            {

                switch (NumMaq) {
                case 0x01:
                    ui->B09_Secadora1->setIcon(QIcon(":/Iconos/material/iconos/icono_secadoratamañokg00 - Rojo.png"));
                    //ui->B09_Lavadora01->set

                    cout<<"Pasado por el cambio de icono del primer botón"<<endl;
                    break;
                case 0x02:
                    ui->B10_Secadora2->setIcon(QIcon(":/Iconos/material/iconos/icono_secadoratamañokg00 - Rojo.png"));
                    break;
                case 0x03:
                    ui->B11_Secadora3->setIcon(QIcon(":/Iconos/material/iconos/icono_secadoratamañokg01 - Rojo.png"));
                    break;
                case 0x04:
                    ui->B12_Secadora4->setIcon(QIcon(":/Iconos/material/iconos/icono_secadoratamañokg01 - Rojo.png"));
                    break;
                case 0x05:
                    ui->B13_Secadora5->setIcon(QIcon(":/Iconos/material/iconos/icono_secadoratamañokg02 - Rojo.png"));
                    break;
                case 0x06:
                    ui->B14_Secadora6->setIcon(QIcon(":/Iconos/material/iconos/icono_secadoratamañokg02 - Rojo.png"));
                    break;

                default:
                    break;
                }

                //Poner lavadora en rojo

            }

        }
        else if (Alarma == 0 && TiempoRestante == 0 && ProgramaEjeucion == 0 )
        {
            cout<< "Lavadora disponible"<<endl;

            switch (NumMaq) {
            case 0x01:
                ui->B09_Secadora1->setIcon(QIcon(":/Iconos/material/iconos/icono_secadoratamañokg00 - Verde.png"));
                //ui->B09_Lavadora01->set

                cout<<"Pasado por el cambio de icono del primer botón"<<endl;
                break;
            case 0x02:
                ui->B10_Secadora2->setIcon(QIcon(":/Iconos/material/iconos/icono_secadoratamañokg00 - Verde.png"));
                break;
            case 0x03:
                ui->B11_Secadora3->setIcon(QIcon(":/Iconos/material/iconos/icono_secadoratamañokg01 - Verde.png"));
                break;
            case 0x04:
                ui->B12_Secadora4->setIcon(QIcon(":/Iconos/material/iconos/icono_secadoratamañokg01 - Verde.png"));
                break;
            case 0x05:
                ui->B13_Secadora5->setIcon(QIcon(":/Iconos/material/iconos/icono_secadoratamañokg02 - Verde.png"));
                break;
            case 0x06:
                ui->B14_Secadora6->setIcon(QIcon(":/Iconos/material/iconos/icono_secadoratamañokg02 - Verde.png"));
                break;

            default:
                break;
            }

            //Poner en verde la pantalla de la lavadora

        }

        if(EstadoPuerta == 0x01)
        {
            PuertaAbierta = true;

        }
        else
        {
            PuertaAbierta = false;
            if(ui->stackedWidget->currentIndex()==10)
            {
                ui->stackedWidget->setCurrentIndex(11);
                Secadora->terminate();
            }
        }

        break;

    }
    case 0x50:

        unsigned char numMaq = AuxMensaje[0];
        unsigned char numProg = AuxMensaje[2];
        unsigned char TiempoSecado = AuxMensaje[5];
        unsigned char Calefaccion = AuxMensaje[6];
        unsigned char TempSalida = AuxMensaje[7];
        unsigned char TempEntrada = AuxMensaje[8];
        unsigned char VelRotacion = AuxMensaje[9];
        unsigned char AccionMecanica = AuxMensaje[10];
        unsigned char TiempoEnfriamiento = AuxMensaje[11];

        if(numProg == 0x01)
        {
            ui->ComboAccionMecSec1->setCurrentIndex((int)AccionMecanica-1);
            ui->ComboCalefaccion1->setCurrentIndex((int)Calefaccion);
            ui->ComboTiempoSecado1->setCurrentIndex((int)TiempoSecado - 1);
            if(Calefaccion==0x00)
            {
                ui->ComboTempEntrada1->setCurrentIndex(0);
                ui->ComboTempSalida1->setCurrentIndex(0);
            }
            else
            {
                ui->ComboTempSalida1->setCurrentIndex(((int)TempSalida)-34);
                ui->ComboTempEntrada1->setCurrentIndex(((int)TempEntrada)-39);
            }
            ui->ComboVelRotacion1->setCurrentIndex((int)VelRotacion-1);
            ui->ComboTiempoEnfriamiento1->setCurrentIndex((int)TiempoEnfriamiento);

        }
        else if (numProg == 0x02)
        {
            ui->ComboAccionMecSec2->setCurrentIndex((int)AccionMecanica-1);
            ui->ComboCalefaccion2->setCurrentIndex((int)Calefaccion);
            ui->ComboTiempoSecado2->setCurrentIndex((int)TiempoSecado - 1);
            if(Calefaccion==0x00)
            {
                ui->ComboTempEntrada2->setCurrentIndex(0);
                ui->ComboTempSalida2->setCurrentIndex(0);
            }
            else
            {
                ui->ComboTempSalida2->setCurrentIndex(((int)TempSalida)-34);
                ui->ComboTempEntrada2->setCurrentIndex(((int)TempEntrada)-39);
            }

            ui->ComboVelRotacion2->setCurrentIndex((int)VelRotacion-1);
            ui->ComboTiempoEnfriamiento2->setCurrentIndex((int)TiempoEnfriamiento);

        }
        else if (numProg == 0x03)
        {
            ui->ComboAccionMecSec3->setCurrentIndex((int)AccionMecanica-1);
            ui->ComboCalefaccion3->setCurrentIndex((int)Calefaccion);
            ui->ComboTiempoSecado3->setCurrentIndex((int)TiempoSecado - 1);
            if(Calefaccion==0x00)
            {
                ui->ComboTempEntrada3->setCurrentIndex(0);
                ui->ComboTempSalida3->setCurrentIndex(0);
            }
            else
            {
                ui->ComboTempSalida3->setCurrentIndex(((int)TempSalida)-34);
                ui->ComboTempEntrada3->setCurrentIndex(((int)TempEntrada)-39);
            }

            ui->ComboVelRotacion3->setCurrentIndex((int)VelRotacion-1);
            ui->ComboTiempoEnfriamiento3->setCurrentIndex((int)TiempoEnfriamiento);

        }
        break;
    }

}

void MainWindow::onTestEstadosLav()
{


    for(int i=1;i<=NumLavadoras;i++)
    {
        Lavadora->InfoStatus((unsigned char)i);
        cout << "Enviaro Test a Lavadora "<<i<<endl;
        Sleep(10);

    }
}

void MainWindow::on_BtnAnadirLavadora_clicked()
{

    VentanaCrear.setModal(false);
    VentanaCrear.exec();
}


void MainWindow::ConectarLavadora()
{
    HANDLE hComPortLav = Lavadora->ConectarLav();
    emit ActualizacionHandleLecturaLavadoras(hComPortLav);
}

void MainWindow::ConectarSecadora()
{
    HANDLE hComPortSec = Lavadora->ConectarSec();
    emit ActualizacionHandleLecturaSecadoras(hComPortSec);

}

void MainWindow::onHandleLavadora(HANDLE hComPortLav)
{
    cout<<"hcomPort Lavadora"<<hComPortLav<<endl;
    emit ActualizacionHandleLecturaLavadoras(hComPortLav);
    if(LecturaLavadorasThread->isRunning())
    {
        cout<<"hilo lectura corriendo"<<endl;
    }
    else
    {
        Sleep(100);
        LecturaLavadorasThread->start();
    }

}

void MainWindow::onHandleSecadora(HANDLE hComPortSec)
{
   // emit ActualizacionHandleLecturaSecadoras(hComPortSec);
    cout<<"hcomPort Lavadora"<<hComPortSec<<endl;
    emit ActualizacionHandleLecturaSecadoras(hComPortSec);
    if(LecturaSecadorasThread->isRunning())
    {
        cout<<"hilo lectura corriendo"<<endl;
    }
    else
    {
        Sleep(100);
        LecturaSecadorasThread->start();
    }
}

void MainWindow::onCrearMaquinaAction(string Action)
{
    string AuxAction = Action;
    cout << "Primero = "<<AuxAction[0] <<"Segundo = "<<AuxAction[1]<<endl;
   /* int SizeAction = (int)(AuxAction[0]-'0');
    printf("Size Hex = %x",SizeAction);
    cout << "Tamaño = "<<SizeAction <<endl;*/

    int SizeAction = 0;
    int Comando = 0;
    int Buscador = 0;
    int IndiceAnterior = 0;

    for(int i = 0 ; i<sizeof(AuxAction) ; i++)
    {
    //    cout << "Entrado en bucle. Tamaño de mensaje = "<<sizeof(AuxAction)<<"Parametro de paso = "<<AuxAction[i]<<endl;
     //   printf("%x",AuxAction[i]);
        if(AuxAction[i]==(char)0xb8)
        {
            cout <<"Entrado en el if de control de paso";
            if(Buscador == 0)
            {
                string auxiliar;
                stringstream Conversor;


                auxiliar.append(AuxAction,0,(i+1));
                Conversor<< auxiliar;
                Conversor>>SizeAction;
                Buscador = Buscador + 1;
                IndiceAnterior = i;
            }

            else if(Buscador == 1)
            {

                string auxiliar;
                stringstream Conversor;
                auxiliar.append(AuxAction,(IndiceAnterior+1),((i-IndiceAnterior)-1));
                Conversor<< auxiliar;
                //Conversor.str(auxiliar);
                Conversor>>Comando;
                cout << "Comando = " <<Comando<<endl;
                if(Comando == 1)
                {
                    VentanaCrear.close();
                }

                Buscador = Buscador +1;
                IndiceAnterior = i;

            }
            else if(Buscador == 2)
            {
                if(Comando == 2)
                {
                    string TextoNuevaMaquina;
                    string auxiliar;
                    stringstream Conversor;
                    int Identificador = 0;
                    bool ExisteID = false;

                    auxiliar.append(AuxAction,(IndiceAnterior+1),((i-IndiceAnterior)-1));
                    Conversor<<(auxiliar);
                    Conversor>>Identificador;


                    for(int a = 0; a<ui->BoxSelMaq->count();a++)
                    {
                        string VerifyID;
                        stringstream VerifyConverter;
                        cout << "Identificador 1 cifra"<<Identificador<<endl;
                        if(Identificador<=9)
                        {
                            int VerifierID = 0;
                            if(ui->BoxSelMaq->itemText(a).toStdString()[2]==')')
                            {


                                VerifyID.append(ui->BoxSelMaq->itemText(a).toStdString(),1,1);
                                VerifyConverter<<(VerifyID);
                                VerifyConverter >> VerifierID;
                                cout << "Verificador 1 cifra " << VerifierID <<"Identificador 1 cifra"<<Identificador<<endl;
                                if(VerifierID == Identificador)
                                {
                                    ExisteID = true;
                                }
                            }
                        }
                        else
                        {
                            int VerifierID = 0;
                            VerifyID.append(ui->BoxSelMaq->itemText(a).toStdString(),1,2);
                            VerifyConverter<<(VerifyID);
                            VerifyConverter >> VerifierID;
                            cout << "Verify ID " <<VerifyID<<endl;
                           // if(!VerifyConverter >> VerifierID)
                          //  {
                         //       cout<<"Verificador no convertido"<<endl;
                          //  }
                         //   else
                          //  {
                                cout <<"Verifier ID "<<VerifierID<<endl;
                                if(VerifierID == Identificador)
                                {
                                    ExisteID = true;
                                }
                         //   }

                        }

                    }

                    if(ExisteID == true)
                    {
                        QMessageBox::information(this,"ID Existente","El número de identificación de máquina seleccionado ya existe");
                    }

                    else
                    {
                        stringstream strIDConverter;
                        string strID;


                        strIDConverter << Identificador;
                        strIDConverter>>strID;

                        TextoNuevaMaquina.append("(");
                        TextoNuevaMaquina.append(strID);
                        TextoNuevaMaquina.append(") ");
                        TextoNuevaMaquina.append(AuxAction,(i+1),(SizeAction-i+1));

                        ui->BoxSelMaq->addItem(QString::fromStdString(TextoNuevaMaquina));

                        VentanaCrear.close();
                    }


                }
                Buscador = Buscador + 1;

            }
        }
    }

    if (SizeAction == 2)
    {
        switch((int)(AuxAction[1]-'0'))
        {
        case 1:
        {

            break;
        }

        }

    }



}

void MainWindow::on_BtnEliminarLavadora_clicked()
{
    if(ui->BoxSelMaq->currentIndex()!=0)
    {
        ui->BoxSelMaq->removeItem(ui->BoxSelMaq->currentIndex());
    }
}


void MainWindow::RegistroErroresLav(string errores)
{

    QTime Time = QTime::currentTime();
    QDate Date = QDate::currentDate();
    unsigned char NumMaq = errores[0];
    unsigned char Alarma = errores[1];
    QString LogAlarma = "(1";        // ID de alarma (Tipo de Máquina, Número de Máquina, Número de Error)
    LogAlarma.append(QString::number(NumMaq,16));
    LogAlarma.append(QString::number(Alarma,16));
    LogAlarma.append(") ");
    QString CodigoError;
    CodigoError.append(LogAlarma);
    QString FindItem = LogAlarma;
    LogAlarma.append(Time.toString());
    LogAlarma.append(Date.toString());
    cout<<LogAlarma.toStdString()<<endl;
    //LogAlarma.append(Date.toString());

    cout << "Alarma número ****** = "<<Alarma<<endl;
    printf("Alarma numero %x",Alarma);
   // ui->listAlarmas->setf
    QList <QListWidgetItem *> myList;
    myList = ui->listAlarmas->findItems(FindItem,Qt::MatchFlags::QFlags::enum_type::MatchContains);
    if(myList.count()==0)
    {
        switch(Alarma)
        {
        case 0x03:
        {

            QString auxiliar = "Error en Lavadora ";
            auxiliar.append(QString::number(NumMaq,16));
            auxiliar.append(". Error ALM door.");
            LogAlarma.append(auxiliar);
            CodigoError.append(auxiliar);
            LogMaquinas.InsertarLineaLog(CodigoError);
            ui->listAlarmas->addItem(LogAlarma);

        break;
        }
        case 0x04:
        {
            QString auxiliar = "Error en Lavadora ";
            auxiliar.append(QString::number(NumMaq,16));
            auxiliar.append(". Error  SL Sobrenivel de baño.");
            LogAlarma.append(auxiliar);
            CodigoError.append(auxiliar);
            LogMaquinas.InsertarLineaLog(CodigoError);
            ui->listAlarmas->addItem(LogAlarma);
            break;
        }
        case 0x05:
        {
            QString auxiliar = "Error en Lavadora ";
            auxiliar.append(QString::number(NumMaq,16));
            auxiliar.append(". Error ALM L Electroválvula parada.");
            LogAlarma.append(auxiliar);
            CodigoError.append(auxiliar);
            LogMaquinas.InsertarLineaLog(CodigoError);
            ui->listAlarmas->addItem(LogAlarma);

        break;
        }
        case 0x06:
        {

            QString auxiliar = "Error en Lavadora ";
            auxiliar.append(QString::number(NumMaq,16));
            auxiliar.append(". Error ALM C2.");
            LogAlarma.append(auxiliar);
            CodigoError.append(auxiliar);
            LogMaquinas.InsertarLineaLog(CodigoError);
            ui->listAlarmas->addItem(LogAlarma);


        break;
        }
        case 0x07:
        {



                QString auxiliar = "Error en Lavadora ";
                auxiliar.append(QString::number(NumMaq,16));
                auxiliar.append(". Error ALM E Alerta desagüe.");
                LogAlarma.append(auxiliar);
                CodigoError.append(auxiliar);
                LogMaquinas.InsertarLineaLog(CodigoError);
                ui->listAlarmas->addItem(LogAlarma);




        break;
        }
        case 0x08:
        {




                QString auxiliar = "Error en Lavadora ";
                auxiliar.append(QString::number(NumMaq,16));
                auxiliar.append(". Error ALM A Entrada de agua.");
                LogAlarma.append(auxiliar);
                CodigoError.append(auxiliar);
                LogMaquinas.InsertarLineaLog(CodigoError);
                ui->listAlarmas->addItem(LogAlarma);

        break;
        }
        case 0x09:
        {
            QString auxiliar = "Error en Lavadora ";
            auxiliar.append(QString::number(NumMaq,16));
           auxiliar.append(". Error ALM C Fallo de temperatura .");
           LogAlarma.append(auxiliar);
           CodigoError.append(auxiliar);
           LogMaquinas.InsertarLineaLog(CodigoError);
           ui->listAlarmas->addItem(LogAlarma);

        break;
        }
        case 0x0a:
        {
            QString auxiliar = "Error en Lavadora ";
            auxiliar.append(QString::number(NumMaq,16));
            auxiliar.append(". Error ALM Prob Deficiencia sonda temperatura.");
            LogAlarma.append(auxiliar);
            CodigoError.append(auxiliar);
            LogMaquinas.InsertarLineaLog(CodigoError);
            ui->listAlarmas->addItem(LogAlarma);
        break;
        }
        case 0x0b:
        {
            QString auxiliar = "Error en Lavadora ";
            auxiliar.append(QString::number(NumMaq,16));
            auxiliar.append(". Error ALM BAL Deficiencia en interruptor de control de desequilibrio.");
            LogAlarma.append(auxiliar);
            CodigoError.append(auxiliar);
            LogMaquinas.InsertarLineaLog(CodigoError);
            ui->listAlarmas->addItem(LogAlarma);
        break;
        }
        case 0x14:
        {
            QString auxiliar = "Error en Lavadora ";
            auxiliar.append(QString::number(NumMaq,16));
            auxiliar.append(". Error ALM VAR 0.");
            LogAlarma.append(auxiliar);
            CodigoError.append(auxiliar);
            LogMaquinas.InsertarLineaLog(CodigoError);
            ui->listAlarmas->addItem(LogAlarma);
        break;
        }
        case 0x15:
        {
            QString auxiliar = "Error en Lavadora ";
            auxiliar.append(QString::number(NumMaq,16));
            auxiliar.append(". Error ALM VAR 1.");
            LogAlarma.append(auxiliar);
            CodigoError.append(auxiliar);
            LogMaquinas.InsertarLineaLog(CodigoError);
            ui->listAlarmas->addItem(LogAlarma);
        break;
        }
        case 0x16:
        {
            QString auxiliar = "Error en Lavadora ";
            auxiliar.append(QString::number(NumMaq,16));
            auxiliar.append(". Error ALM VAR 2.");
            LogAlarma.append(auxiliar);
            CodigoError.append(auxiliar);
            LogMaquinas.InsertarLineaLog(CodigoError);
            ui->listAlarmas->addItem(LogAlarma);
        break;
        }
        case 0x17:
        {
            QString auxiliar = "Error en Lavadora ";
            auxiliar.append(QString::number(NumMaq,16));
            auxiliar.append(". Error ALM VAR 3.");
            LogAlarma.append(auxiliar);
            CodigoError.append(auxiliar);
            LogMaquinas.InsertarLineaLog(CodigoError);
            ui->listAlarmas->addItem(LogAlarma);

        break;
        }
        case 0x18:
        {
            QString auxiliar = "Error en Lavadora ";
            auxiliar.append(QString::number(NumMaq,16));
            auxiliar.append(". Error ALM VAR 4.");
            LogAlarma.append(auxiliar);
            CodigoError.append(auxiliar);
            LogMaquinas.InsertarLineaLog(CodigoError);
            ui->listAlarmas->addItem(LogAlarma);
        break;
        }
        case 0x19:
        {
            QString auxiliar = "Error en Lavadora ";
            auxiliar.append(QString::number(NumMaq,16));
            auxiliar.append(". Error ALM VAR 5.");
            LogAlarma.append(auxiliar);
            CodigoError.append(auxiliar);
            LogMaquinas.InsertarLineaLog(CodigoError);
            ui->listAlarmas->addItem(LogAlarma);
        break;
        }
        case 0x1a:
        {
            QString auxiliar = "Error en Lavadora ";
            auxiliar.append(QString::number(NumMaq,16));
            auxiliar.append(". Error ALM VAR 6.");
            LogAlarma.append(auxiliar);
            LogAlarma.append(auxiliar);
            CodigoError.append(auxiliar);
            LogMaquinas.InsertarLineaLog(CodigoError);
            ui->listAlarmas->addItem(LogAlarma);

        break;
        }
        case 0x1b:
        {
            QString auxiliar = "Error en Lavadora ";
            auxiliar.append(QString::number(NumMaq,16));
            auxiliar.append(". Error ALM VAR 7.");
            LogAlarma.append(auxiliar);
            CodigoError.append(auxiliar);
            LogMaquinas.InsertarLineaLog(CodigoError);
            ui->listAlarmas->addItem(LogAlarma);
        break;
        }
        case 0x1c:
        {
            QString auxiliar = "Error en Lavadora ";
            auxiliar.append(QString::number(NumMaq,16));
            auxiliar.append(". Error ALM VAR 8.");
            LogAlarma.append(auxiliar);
            CodigoError.append(auxiliar);
            LogMaquinas.InsertarLineaLog(CodigoError);
            ui->listAlarmas->addItem(LogAlarma);
        break;
        }
        default:
        {
            QString auxiliar = "Error en Lavadora ";
            auxiliar.append(QString::number(NumMaq,16));
            auxiliar.append(". Error indefinido.");
            LogAlarma.append(auxiliar);
            CodigoError.append(auxiliar);
            LogMaquinas.InsertarLineaLog(CodigoError);
            ui->listAlarmas->addItem(LogAlarma);
        break;
        }


        }
    }
}

void MainWindow::RegistroErroresSec(string errores)
{
    
    QTime Time = QTime::currentTime();
    QDate Date = QDate::currentDate();
    unsigned char NumMaq = errores[0];
    char Alarma = errores[1];
    QString LogAlarma = "(2";        // ID de alarma (Tipo de Máquina, Número de Máquina, Número de Error)
    LogAlarma.append(QString::number(NumMaq,16));
    LogAlarma.append(QString::number(Alarma,16));
    LogAlarma.append(") ");
    QString CodigoError;
    CodigoError.append(LogAlarma);
    QString FindItem = LogAlarma;
    LogAlarma.append(Time.toString());
    LogAlarma.append(Date.toString());
    cout<<LogAlarma.toStdString()<<endl;
    //LogAlarma.append(Date.toString());

    cout << "Alarma número ****** = "<<Alarma<<endl;
    printf("Alarma numero %x",Alarma);
   // ui->listAlarmas->setf
    QList <QListWidgetItem *> myList;
    myList = ui->listAlarmas->findItems(FindItem,Qt::MatchFlags::QFlags::enum_type::MatchContains);
    if(myList.count()==0)
    {
        switch(Alarma)
        {
        case 0x02:
        {

            QString auxiliar = "Error en Secadora ";
            auxiliar.append(QString::number(NumMaq,16));
            auxiliar.append(". Error Montaje.");
            LogAlarma.append(auxiliar);
            CodigoError.append(auxiliar);
            LogMaquinas.InsertarLineaLog(CodigoError);
            ui->listAlarmas->addItem(LogAlarma);

        break;
        }
        case 0x03:
        {

            QString auxiliar = "Error en Secadora ";
            auxiliar.append(QString::number(NumMaq,16));
            auxiliar.append(". Error Comunicación con Variador.");
            LogAlarma.append(auxiliar);
            CodigoError.append(auxiliar);
            LogMaquinas.InsertarLineaLog(CodigoError);
            ui->listAlarmas->addItem(LogAlarma);

        break;
        }
        case 0x04:
        {
            QString auxiliar = "Error en Secadora ";
            auxiliar.append(QString::number(NumMaq,16));
            auxiliar.append(". Error  Sobrecorriente del Variador.");
            LogAlarma.append(auxiliar);
            CodigoError.append(auxiliar);
            LogMaquinas.InsertarLineaLog(CodigoError);
            ui->listAlarmas->addItem(LogAlarma);
            break;
        }
        case 0x05:
        {
            QString auxiliar = "Error en Secadora ";
            auxiliar.append(QString::number(NumMaq,16));
            auxiliar.append(". Error Sobretemperatura del Motor.");
            LogAlarma.append(auxiliar);
            CodigoError.append(auxiliar);
            LogMaquinas.InsertarLineaLog(CodigoError);
            ui->listAlarmas->addItem(LogAlarma);

        break;
        }
        case 0x06:
        {

            QString auxiliar = "Error en Secadora ";
            auxiliar.append(QString::number(NumMaq,16));
            auxiliar.append(". Error Fallo General del Variador.");
            LogAlarma.append(auxiliar);
            CodigoError.append(auxiliar);
            LogMaquinas.InsertarLineaLog(CodigoError);
            ui->listAlarmas->addItem(LogAlarma);


        break;
        }
        case 0x07:
        {



                QString auxiliar = "Error en Secadora ";
                auxiliar.append(QString::number(NumMaq,16));
                auxiliar.append(". Error Fallo de Configuración del Variador.");
                LogAlarma.append(auxiliar);
                CodigoError.append(auxiliar);
                LogMaquinas.InsertarLineaLog(CodigoError);
                ui->listAlarmas->addItem(LogAlarma);




        break;
        }
        case 0x08:
        {




                QString auxiliar = "Error en Secadora ";
                auxiliar.append((QString::number(NumMaq,16)));
                auxiliar.append(". Error Puerta del Filtro abierta.");
                LogAlarma.append(auxiliar);
                CodigoError.append(auxiliar);
                LogMaquinas.InsertarLineaLog(CodigoError);
                ui->listAlarmas->addItem(LogAlarma);

        break;
        }
        case 0x09:
        {
            QString auxiliar = "Error en Secadora ";
            auxiliar.append(QString::number(NumMaq,16));
           auxiliar.append(". Error Sobretemperatura.");
           LogAlarma.append(auxiliar);
           CodigoError.append(auxiliar);
           LogMaquinas.InsertarLineaLog(CodigoError);
           ui->listAlarmas->addItem(LogAlarma);

        break;
        }
        case 0x0a:
        {
            QString auxiliar = "Error en Secadora ";
            auxiliar.append(QString::number(NumMaq,16));
            auxiliar.append(". Error Fallo Calentamiento.");
            LogAlarma.append(auxiliar);
            CodigoError.append(auxiliar);
            LogMaquinas.InsertarLineaLog(CodigoError);
            ui->listAlarmas->addItem(LogAlarma);
        break;
        }
        case 0x0b:
        {
            QString auxiliar = "Error en Secadora ";
            auxiliar.append(QString::number(NumMaq,16));
            auxiliar.append(". Error Control Temperatura de entrada.");
            LogAlarma.append(auxiliar);
            CodigoError.append(auxiliar);
            LogMaquinas.InsertarLineaLog(CodigoError);
            ui->listAlarmas->addItem(LogAlarma);
        break;
        }
        case 0x0c:
        {
            QString auxiliar = "Error en Secadora ";
            auxiliar.append(QString::number(NumMaq,16));
            auxiliar.append(". Error Control de Temperatura de salida.");
            LogAlarma.append(auxiliar);
            CodigoError.append(auxiliar);
            LogMaquinas.InsertarLineaLog(CodigoError);
            ui->listAlarmas->addItem(LogAlarma);
        break;
        }
        case 0x0d:
        {
            QString auxiliar = "Error en Secadora ";
            auxiliar.append(QString::number(NumMaq,16));
            auxiliar.append(". Error Alarma Termostato de entrada.");
            LogAlarma.append(auxiliar);
            CodigoError.append(auxiliar);
            LogMaquinas.InsertarLineaLog(CodigoError);
            ui->listAlarmas->addItem(LogAlarma);
        break;
        }
        case 0x0e:
        {
            QString auxiliar = "Error en Secadora ";
            auxiliar.append(NumMaq);
            auxiliar.append(". Error Alarma Termostato de salida.");
            LogAlarma.append(auxiliar);
            CodigoError.append(auxiliar);
            LogMaquinas.InsertarLineaLog(CodigoError);
            ui->listAlarmas->addItem(LogAlarma);
        break;
        }
        case 0x0f:
        {
            QString auxiliar = "Error en Secadora ";
            auxiliar.append(QString::number(NumMaq,16));
            auxiliar.append(". Error Fallo de Rotación.");
            LogAlarma.append(auxiliar);
            CodigoError.append(auxiliar);
            LogMaquinas.InsertarLineaLog(CodigoError);
            ui->listAlarmas->addItem(LogAlarma);

        break;
        }
        case 0x10:
        {
            QString auxiliar = "Error en Secadora ";
            auxiliar.append(QString::number(NumMaq,16));
            auxiliar.append(". Error Fallo del Encendido del gas.");
            LogAlarma.append(auxiliar);
            CodigoError.append(auxiliar);
            LogMaquinas.InsertarLineaLog(CodigoError);
            ui->listAlarmas->addItem(LogAlarma);
        break;
        }
        case 0x11:
        {
            QString auxiliar = "Error en Secadora ";
            auxiliar.append(QString::number(NumMaq,16));
            auxiliar.append(". Error Fallo de Calefacción eléctrica.");
            LogAlarma.append(auxiliar);
            CodigoError.append(auxiliar);
            LogMaquinas.InsertarLineaLog(CodigoError);
            ui->listAlarmas->addItem(LogAlarma);
        break;
        }
        case 0x12:
        {
            QString auxiliar = "Error en Secadora ";
            auxiliar.append(QString::number(NumMaq,16));
            auxiliar.append(". Error Fallo de Calefacción.");
            LogAlarma.append(auxiliar);
            CodigoError.append(auxiliar);
            LogMaquinas.InsertarLineaLog(CodigoError);
            ui->listAlarmas->addItem(LogAlarma);

        break;
        }
        case 0x13:
        {
            QString auxiliar = "Error en Secadora ";
            auxiliar.append(QString::number(NumMaq,16));
            auxiliar.append(". Error Fallo de Aspiración.");
            LogAlarma.append(auxiliar);
            CodigoError.append(auxiliar);
            LogMaquinas.InsertarLineaLog(CodigoError);
            ui->listAlarmas->addItem(LogAlarma);
        break;
        }
        case 0x14:
        {
            QString auxiliar = "Error en Secadora ";
            auxiliar.append(QString::number(NumMaq,16));
            auxiliar.append(". Error Fallo del Ventilador.");
            LogAlarma.append(auxiliar);
            LogAlarma.append(auxiliar);
            CodigoError.append(auxiliar);
            LogMaquinas.InsertarLineaLog(CodigoError);
            ui->listAlarmas->addItem(LogAlarma);
        break;
        }
        case 0x15:
        {

            QString auxiliar = "Error en Secadora ";
            auxiliar.append(QString::number(NumMaq,16));
            auxiliar.append(". Error AFS.");
            LogAlarma.append(auxiliar);
            CodigoError.append(auxiliar);
            LogMaquinas.InsertarLineaLog(CodigoError);
            ui->listAlarmas->addItem(LogAlarma);

        break;
        }
        case 0x16:
        {

            QString auxiliar = "Error en Secadora ";
            auxiliar.append(QString::number(NumMaq,16));
            auxiliar.append(". Error de Modelo de Máquina.");
            LogAlarma.append(auxiliar);
            CodigoError.append(auxiliar);
            LogMaquinas.InsertarLineaLog(CodigoError);
            ui->listAlarmas->addItem(LogAlarma);

        break;
        }
        default:
        {
            QString auxiliar = "Error en Secadora ";
            auxiliar.append(QString::number(NumMaq,16));
            auxiliar.append(". Error indefinido.");
            LogAlarma.append(auxiliar);
            CodigoError.append(auxiliar);
            LogMaquinas.InsertarLineaLog(CodigoError);
            ui->listAlarmas->addItem(LogAlarma);
        break;
        }


        }
    }

}

void MainWindow::on_B04_Back_29_clicked()
{
    ui->stackedWidget->setCurrentIndex(25);
}

void MainWindow::on_B08_Gestion_clicked()
{
    ui->stackedWidget->setCurrentIndex(28);
}

void MainWindow::on_B04_Back_26_clicked()
{
    ui->stackedWidget->setCurrentIndex(14);
}







/*void MainWindow::onPuertaCerradaLav()
{

    if(ui->stackedWidget->currentIndex()==5)
    {
        cout << "Jorge estoy en la 5!!!"<<endl;
       //  ui->stackedWidget->setCurrentIndex(5);
        while(PuertaAbierta)
        {
            Lavadora->InfoStatus(Lavadora->get_numTipoMaquina());
            Sleep(1000);
            PuertaAbierta = LecturaLavadorasThread->EstadoPuerta;

        }
        ui->stackedWidget->setCurrentIndex(6);
    }


}*/

/*void MainWindow::on_stackedWidget_currentChanged(int arg1)
{
    cout<< "Página Actual = ?"<<endl;
    Sleep(1000);
    if(arg1 == 5)
    {
        cout<< "Página Actual = 5"<<endl;
        emit EstadoPuertaLav();
    }
}*/

void MainWindow::on_BtnGuardar_clicked()
{

    if(ui->BoxSelMaq->currentIndex()==0||ui->BoxSelProg->currentIndex()==0)
    {
        QMessageBox::information(this,"Selección No Válida","Por favor seleccione una máquina y un programa");
    }
    else if((ui->ComboDosi1->currentIndex()==0 && ui->ComboTiempoDosi1->currentIndex()!=0)||(ui->ComboDosi2->currentIndex()==0 && ui->ComboTiempoDosi2->currentIndex()!=0)
            ||(ui->ComboDosi3->currentIndex()==0 && ui->ComboTiempoDosi3->currentIndex()!=0)||(ui->ComboDosi4->currentIndex()==0 && ui->ComboTiempoDosi4->currentIndex()!=0)
            ||(ui->ComboDosi5->currentIndex()==0 && ui->ComboTiempoDosi5->currentIndex()!=0)||(ui->ComboDosi6->currentIndex()==0 && ui->ComboTiempoDosi6->currentIndex()!=0))
    {
        QMessageBox::information(this,"Selección No Válida","Por favor revise los tipos y tiempos de dosificación");
    }
    else if((ui->ComboCentrifugado1->currentIndex()==0 && ui->ComboTiempoCentri1->currentIndex()!=0)||(ui->ComboCentrifugado1->currentIndex()==1 && ui->ComboTiempoCentri1->currentIndex()!=0)
            ||(ui->ComboCentrifugado2->currentIndex()==0 && ui->ComboTiempoCentri2->currentIndex()!=0)||(ui->ComboCentrifugado2->currentIndex()==1 && ui->ComboTiempoCentri2->currentIndex()!=0)
            ||(ui->ComboCentrifugado3->currentIndex()==0 && ui->ComboTiempoCentri3->currentIndex()!=0)||(ui->ComboCentrifugado3->currentIndex()==1 && ui->ComboTiempoCentri3->currentIndex()!=0)
            ||(ui->ComboCentrifugado4->currentIndex()==0 && ui->ComboTiempoCentri4->currentIndex()!=0)||(ui->ComboCentrifugado4->currentIndex()==1 && ui->ComboTiempoCentri4->currentIndex()!=0)
            ||(ui->ComboCentrifugado5->currentIndex()==0 && ui->ComboTiempoCentri5->currentIndex()!=0)||(ui->ComboCentrifugado5->currentIndex()==1 && ui->ComboTiempoCentri5->currentIndex()!=0)
            ||(ui->ComboCentrifugado6->currentIndex()==0 && ui->ComboTiempoCentri6->currentIndex()!=0)||(ui->ComboCentrifugado6->currentIndex()==1 && ui->ComboTiempoCentri6->currentIndex()!=0))
    {
        QMessageBox::information(this,"Selección No Válida","Por favor revise los tipos y tiempos de centrifugado");

    }
    else
    {

        Lavadora->set_CmdNumMaq((unsigned char)ui->BoxSelMaq->currentIndex());
        Lavadora->set_CmdNumProgram((unsigned char)ui->BoxSelProg->currentIndex());
        Lavadora->set_CmdNumFase(0x01);
        Lavadora->set_CmdNivelBano((unsigned char)ui->ComboNivelBano1->currentIndex());
        Lavadora->set_CmdTemperatura((unsigned char)(ui->ComboTemperatura1->currentIndex()*4+20));
        if(ui->ComboDosi1->currentIndex()<5)
        {
            Lavadora->set_CmdDosificacion((unsigned char)ui->ComboDosi1->currentIndex());
        }
        else
        {
            cout<<"Combo Dosificacion 1"<<ui->ComboDosi1->currentIndex()<<endl;
            switch(ui->ComboDosi1->currentIndex())
            {
            case 5:
            {
                Lavadora->set_CmdDosificacion(0x0c);
                break;
            }
            case 6:
            {
                Lavadora->set_CmdDosificacion(0x0d);
                break;
            }
            case 7:
            {
                Lavadora->set_CmdDosificacion(0x0e);
                break;
            }
            case 8:
            {
                Lavadora->set_CmdDosificacion(0x17);
                break;
            }
            case 9:
            {
                Lavadora->set_CmdDosificacion(0x18);
                break;
            }
            case 10:
            {
                Lavadora->set_CmdDosificacion(0x22);
                break;
            }

            }
        }
        Lavadora->set_CmdTiempoDosificacion((unsigned char)ui->ComboTiempoDosi1->currentIndex()+1);
        Lavadora->set_CmdAccionMecanica((unsigned char)ui->ComboAccionMec1->currentIndex()+1);
        Lavadora->set_CmdTiempoRotacion((unsigned char)ui->ComboTiempoRot1->currentIndex());
        Lavadora->set_CmdDesague((unsigned char)ui->ComboCentrifugado1->currentIndex());
        if(ui->ComboTiempoCentri1->currentIndex()==0||ui->ComboCentrifugado1->currentIndex()==1
                ||ui->ComboCentrifugado1->currentIndex()==0)
        {
            Lavadora->set_CmdTiempoCentrifugado(0x00);
        }
        else
        {
            Lavadora->set_CmdTiempoCentrifugado((unsigned char)ui->ComboTiempoCentri1->currentIndex()+1);
        }
        Lavadora->set_CmdHabilitarFase((unsigned char)ui->ComboHabilitar1->currentIndex());
        Lavadora->set_CmdEnfriamiento(0x00);
        Lavadora->set_CmdPausa(0x00);
        Lavadora->SendCmd(Lavadora->CmdEditPhaseLav);
        Sleep(100);

        Lavadora->set_CmdNumFase(0x02);
        Lavadora->set_CmdNivelBano((unsigned char)ui->ComboNivelBano2->currentIndex());
        Lavadora->set_CmdTemperatura((unsigned char)(ui->ComboTemperatura2->currentIndex()*4+20));
        if(ui->ComboDosi2->currentIndex()<5)
        {
            Lavadora->set_CmdDosificacion((unsigned char)ui->ComboDosi2->currentIndex());
        }
        else
        {
            cout<<"Combo Dosificacion 2"<<ui->ComboDosi2->currentIndex()<<endl;
            switch(ui->ComboDosi2->currentIndex())
            {
            case 5:
            {
                Lavadora->set_CmdDosificacion(0x0c);
                break;
            }
            case 6:
            {
                Lavadora->set_CmdDosificacion(0x0d);
                break;
            }
            case 7:
            {
                Lavadora->set_CmdDosificacion(0x0e);
                break;
            }
            case 8:
            {
                Lavadora->set_CmdDosificacion(0x17);
                break;
            }
            case 9:
            {
                Lavadora->set_CmdDosificacion(0x18);
                break;
            }
            case 10:
            {
                Lavadora->set_CmdDosificacion(0x22);
                break;
            }

            }
        }
        Lavadora->set_CmdTiempoDosificacion((unsigned char)ui->ComboTiempoDosi2->currentIndex()+1);
        Lavadora->set_CmdAccionMecanica((unsigned char)ui->ComboAccionMec2->currentIndex()+1);
        Lavadora->set_CmdTiempoRotacion((unsigned char)ui->ComboTiempoRot2->currentIndex());
        Lavadora->set_CmdDesague((unsigned char)ui->ComboCentrifugado2->currentIndex());
        if(ui->ComboTiempoCentri2->currentIndex()==0||ui->ComboCentrifugado2->currentIndex()==1
                ||ui->ComboCentrifugado2->currentIndex()==0)
        {
            Lavadora->set_CmdTiempoCentrifugado(0x00);
        }
        else
        {
            Lavadora->set_CmdTiempoCentrifugado((unsigned char)ui->ComboTiempoCentri2->currentIndex()+1);
        }
        Lavadora->set_CmdHabilitarFase((unsigned char)ui->ComboHabilitar2->currentIndex());
        Lavadora->SendCmd(Lavadora->CmdEditPhaseLav);
        Sleep(100);

        Lavadora->set_CmdNumFase(0x03);
        Lavadora->set_CmdNivelBano((unsigned char)ui->ComboNivelBano3->currentIndex());
        Lavadora->set_CmdTemperatura((unsigned char)(ui->ComboTemperatura3->currentIndex()*4+20));
        if(ui->ComboDosi3->currentIndex()<5)
        {
            Lavadora->set_CmdDosificacion((unsigned char)ui->ComboDosi3->currentIndex());
        }
        else
        {
            cout<<"Combo Dosificacion 3"<<ui->ComboDosi3->currentIndex()<<endl;
            switch(ui->ComboDosi3->currentIndex())
            {
            case 5:
            {
                Lavadora->set_CmdDosificacion(0x0c);
                break;
            }
            case 6:
            {
                Lavadora->set_CmdDosificacion(0x0d);
                break;
            }
            case 7:
            {
                Lavadora->set_CmdDosificacion(0x0e);
                break;
            }
            case 8:
            {
                Lavadora->set_CmdDosificacion(0x17);
                break;
            }
            case 9:
            {
                Lavadora->set_CmdDosificacion(0x18);
                break;
            }
            case 10:
            {
                Lavadora->set_CmdDosificacion(0x22);
                break;
            }

            }
        }
        Lavadora->set_CmdTiempoDosificacion((unsigned char)ui->ComboTiempoDosi3->currentIndex()+1);
        Lavadora->set_CmdAccionMecanica((unsigned char)ui->ComboAccionMec3->currentIndex()+1);
        Lavadora->set_CmdTiempoRotacion((unsigned char)ui->ComboTiempoRot3->currentIndex());
        Lavadora->set_CmdDesague((unsigned char)ui->ComboCentrifugado3->currentIndex());
        if(ui->ComboTiempoCentri3->currentIndex()==0||ui->ComboCentrifugado3->currentIndex()==1
                ||ui->ComboCentrifugado3->currentIndex()==0)
        {
            Lavadora->set_CmdTiempoCentrifugado(0x00);
        }
        else
        {
            Lavadora->set_CmdTiempoCentrifugado((unsigned char)ui->ComboTiempoCentri3->currentIndex()+1);
        }
        Lavadora->set_CmdHabilitarFase((unsigned char)ui->ComboHabilitar3->currentIndex());
        Lavadora->SendCmd(Lavadora->CmdEditPhaseLav);
        Sleep(100);

        Lavadora->set_CmdNumFase(0x04);
        Lavadora->set_CmdNivelBano((unsigned char)ui->ComboNivelBano4->currentIndex());
        Lavadora->set_CmdTemperatura((unsigned char)(ui->ComboTemperatura4->currentIndex()*4+20));
        if(ui->ComboDosi4->currentIndex()<5)
        {
            Lavadora->set_CmdDosificacion((unsigned char)ui->ComboDosi4->currentIndex());
        }
        else
        {
            cout<<"Combo Dosificacion 4"<<ui->ComboDosi4->currentIndex()<<endl;
            switch(ui->ComboDosi4->currentIndex())
            {
            case 5:
            {
                Lavadora->set_CmdDosificacion(0x0c);
                break;
            }
            case 6:
            {
                Lavadora->set_CmdDosificacion(0x0d);
                break;
            }
            case 7:
            {
                Lavadora->set_CmdDosificacion(0x0e);
                break;
            }
            case 8:
            {
                Lavadora->set_CmdDosificacion(0x17);
                break;
            }
            case 9:
            {
                Lavadora->set_CmdDosificacion(0x18);
                break;
            }
            case 10:
            {
                Lavadora->set_CmdDosificacion(0x22);
                break;
            }

            }
        }
        Lavadora->set_CmdTiempoDosificacion((unsigned char)ui->ComboTiempoDosi4->currentIndex()+1);
        Lavadora->set_CmdAccionMecanica((unsigned char)ui->ComboAccionMec4->currentIndex()+1);
        Lavadora->set_CmdTiempoRotacion((unsigned char)ui->ComboTiempoRot4->currentIndex());
        Lavadora->set_CmdDesague((unsigned char)ui->ComboCentrifugado4->currentIndex());
        if(ui->ComboTiempoCentri4->currentIndex()==0||ui->ComboCentrifugado4->currentIndex()==1
                ||ui->ComboCentrifugado4->currentIndex()==0)
        {
            Lavadora->set_CmdTiempoCentrifugado(0x00);
        }
        else
        {
            Lavadora->set_CmdTiempoCentrifugado((unsigned char)ui->ComboTiempoCentri4->currentIndex()+1);
        }
        Lavadora->set_CmdHabilitarFase((unsigned char)ui->ComboHabilitar4->currentIndex());
        Lavadora->SendCmd(Lavadora->CmdEditPhaseLav);
        Sleep(100);

        Lavadora->set_CmdNumFase(0x05);
        Lavadora->set_CmdNivelBano((unsigned char)ui->ComboNivelBano5->currentIndex());
        Lavadora->set_CmdTemperatura((unsigned char)(ui->ComboTemperatura5->currentIndex()*4+20));
        if(ui->ComboDosi5->currentIndex()<5)
        {
            Lavadora->set_CmdDosificacion((unsigned char)ui->ComboDosi5->currentIndex());
        }
        else
        {
            cout<<"Combo Dosificacion 5"<<ui->ComboDosi5->currentIndex()<<endl;
            switch(ui->ComboDosi5->currentIndex())
            {
            case 5:
            {
                Lavadora->set_CmdDosificacion(0x0c);
                break;
            }
            case 6:
            {
                Lavadora->set_CmdDosificacion(0x0d);
                break;
            }
            case 7:
            {
                Lavadora->set_CmdDosificacion(0x0e);
                break;
            }
            case 8:
            {
                Lavadora->set_CmdDosificacion(0x17);
                break;
            }
            case 9:
            {
                Lavadora->set_CmdDosificacion(0x18);
                break;
            }
            case 10:
            {
                Lavadora->set_CmdDosificacion(0x22);
                break;
            }

            }
        }
        Lavadora->set_CmdTiempoDosificacion((unsigned char)ui->ComboTiempoDosi5->currentIndex()+1);
        Lavadora->set_CmdAccionMecanica((unsigned char)ui->ComboAccionMec5->currentIndex()+1);
        Lavadora->set_CmdTiempoRotacion((unsigned char)ui->ComboTiempoRot5->currentIndex());
        Lavadora->set_CmdDesague((unsigned char)ui->ComboCentrifugado5->currentIndex());
        if(ui->ComboTiempoCentri5->currentIndex()==0||ui->ComboCentrifugado5->currentIndex()==1
                ||ui->ComboCentrifugado5->currentIndex()==0)
        {
            Lavadora->set_CmdTiempoCentrifugado(0x00);
        }
        else
        {
            Lavadora->set_CmdTiempoCentrifugado((unsigned char)ui->ComboTiempoCentri1->currentIndex()+1);
        }
        Lavadora->set_CmdHabilitarFase((unsigned char)ui->ComboHabilitar5->currentIndex());
        Lavadora->SendCmd(Lavadora->CmdEditPhaseLav);
        Sleep(100);
        Lavadora->set_CmdNumFase(0x06);
        Lavadora->set_CmdNivelBano((unsigned char)ui->ComboNivelBano6->currentIndex()+1);
        Lavadora->set_CmdTemperatura((unsigned char)(ui->ComboTemperatura6->currentIndex()*4+20));
        if(ui->ComboDosi6->currentIndex()<5)
        {
            Lavadora->set_CmdDosificacion((unsigned char)ui->ComboDosi6->currentIndex());
        }
        else
        {
            cout<<"Combo Dosificacion 6"<<ui->ComboDosi6->currentIndex()<<endl;
            switch(ui->ComboDosi6->currentIndex())
            {
            case 5:
            {
                Lavadora->set_CmdDosificacion(0x0c);
                break;
            }
            case 6:
            {
                Lavadora->set_CmdDosificacion(0x0d);
                break;
            }
            case 7:
            {
                Lavadora->set_CmdDosificacion(0x0e);
                break;
            }
            case 8:
            {
                Lavadora->set_CmdDosificacion(0x17);
                break;
            }
            case 9:
            {
                Lavadora->set_CmdDosificacion(0x18);
                break;
            }
            case 10:
            {
                Lavadora->set_CmdDosificacion(0x22);
                break;
            }

            }
        }
        Lavadora->set_CmdTiempoDosificacion((unsigned char)ui->ComboTiempoDosi6->currentIndex()+1);
        Lavadora->set_CmdAccionMecanica((unsigned char)ui->ComboAccionMec6->currentIndex()+1);


        if(ui->ComboTiempoCentri6->currentIndex()==0||ui->ComboCentrifugado6->currentIndex()==1
                ||ui->ComboCentrifugado6->currentIndex()==0)
        {
            Lavadora->set_CmdTiempoCentrifugado(0x00);
        }
        else
        {
            Lavadora->set_CmdTiempoCentrifugado((unsigned char)ui->ComboTiempoCentri6->currentIndex()+1);
        }
        Lavadora->set_CmdDesague((unsigned char)ui->ComboCentrifugado6->currentIndex()+1);
        Lavadora->set_CmdTiempoRotacion((unsigned char)ui->ComboTiempoRot6->currentIndex()+1);
        Lavadora->set_CmdHabilitarFase(0x00);
        Lavadora->SendCmd(Lavadora->CmdEditPhaseLav);
    }

}

void MainWindow::on_BtnSecadora_clicked()
{
    ui->stackedWidget->setCurrentIndex(31);
}

void MainWindow::on_B04_Back_30_clicked()
{
    ui->stackedWidget->setCurrentIndex(30);
}

void MainWindow::on_BtnActualizar_2_clicked()
{

    int Maquina = 0;
    int Programa = 0;
    int NumMaquinas = 0;
    int NumProgramas = 0;
    string Comando;

   /* Lavadora->set_CmdNumMaq((unsigned char)ui->BoxSelMaq->currentIndex());
    printf("Lavadora index = %x\n",(unsigned char)ui->BoxSelMaq->currentIndex());
    Lavadora->set_CmdNumProgram((unsigned char) ui->BoxSelProg->currentIndex());
    for(int i=1;i<=6;i++)
    {
        Lavadora->set_CmdNumFase((unsigned char)i);
        printf("Lavadora phase = %x\n",(unsigned char)i);
        //Sleep(100);

        Lavadora->SendCmd(Lavadora->CmdReadPhaseLav);
        Sleep(100);
    }*/



    unsigned char IDMaquina = ((unsigned char) ui->BoxSelMaqSec->currentIndex());// Aquí está el hexadecimal con el numero de identificación de la máquina

    cout<<"Máquina seleccionada" <<Maquina<<endl;
    cout<<"Programa Seleciionado" << Programa<<endl;

    if(IDMaquina == 0x00)
    {
        QMessageBox::information(this,"Selección No Válida","Por favor seleccione una máquina y un programa");
    }
    else
    {
        Comando.resize(2);
        Comando[0]=IDMaquina;

        emit ActualizarConfiguracionSec(Comando);
    }
  //  NumMaquinas = ui->BoxSelMaq->maxCount();
  //  NumProgramas = ui->BoxSelProg->maxCount();

   // unsigned char IDMaquina = ((unsigned char) Maquina);

    printf("Hola %x",IDMaquina);

    cout<<"Hola"<<endl;


}

void MainWindow::on_BtnGuardar_2_clicked()
{

    if((ui->ComboCalefaccion1->currentIndex() == 0 && (ui->ComboTempEntrada1->currentIndex()!=0||ui->ComboTempSalida1->currentIndex() != 0))
            ||(ui->ComboCalefaccion2->currentIndex() == 0 && (ui->ComboTempEntrada2->currentIndex()!=0||ui->ComboTempSalida2->currentIndex() != 0))
            ||(ui->ComboCalefaccion3->currentIndex() == 0 && (ui->ComboTempEntrada3->currentIndex()!=0||ui->ComboTempSalida3->currentIndex() != 0)))
    {
        QMessageBox::information(this,"Selección No Válida","Por favor revise si la calefacción está desactivada y se han seleccionado tempereaturas");

    }
    else
    {
        Secadora->set_CmdNumProgram(0x01);
        Secadora->set_CmdTiempoSecado((unsigned char) ui->ComboTiempoSecado1->currentIndex()+1);
        Secadora->set_CmdCalefaccion((unsigned char) ui->ComboCalefaccion1->currentIndex());
        if(ui->ComboTempSalida1->currentIndex()==0) Secadora->set_CmdTempSalida(0x00);
        else Secadora->set_CmdTempSalida((unsigned char)ui->ComboTempSalida1->currentIndex()+34);
        if(ui->ComboTempEntrada1->currentIndex()==0)Secadora->set_CmdTempEntrada(0x00);
        else Secadora->set_CmdTempEntrada((unsigned char)ui->ComboTempEntrada1->currentIndex()+39);
        Secadora->set_CmdAccionMecanica((unsigned char)ui->ComboAccionMecSec1->currentIndex()+1);
        Secadora->set_CmdVelRotacion((unsigned char)ui->ComboVelRotacion1->currentIndex()+1);
        Secadora->set_CmdTiempoEnfriamiento((unsigned char) ui->ComboTiempoEnfriamiento1->currentIndex());
        Secadora->SendCmd(Secadora->CmdEditProgramSec);
        Sleep(100);

        Secadora->set_CmdNumProgram(0x02);
        Secadora->set_CmdTiempoSecado((unsigned char) ui->ComboTiempoSecado2->currentIndex()+1);
        Secadora->set_CmdCalefaccion((unsigned char) ui->ComboCalefaccion2->currentIndex());
        if(ui->ComboTempSalida2->currentIndex()==0) Secadora->set_CmdTempSalida(0x00);
        else Secadora->set_CmdTempSalida((unsigned char)ui->ComboTempSalida2->currentIndex()+34);
        if(ui->ComboTempEntrada2->currentIndex()==0)Secadora->set_CmdTempEntrada(0x00);
        else Secadora->set_CmdTempEntrada((unsigned char)ui->ComboTempEntrada2->currentIndex()+39);
        Secadora->set_CmdAccionMecanica((unsigned char)ui->ComboAccionMecSec2->currentIndex()+1);
        Secadora->set_CmdVelRotacion((unsigned char)ui->ComboVelRotacion2->currentIndex()+1);
        Secadora->set_CmdTiempoEnfriamiento((unsigned char) ui->ComboTiempoEnfriamiento2->currentIndex());
        Secadora->SendCmd(Secadora->CmdEditProgramSec);
        Sleep(100);

        Secadora->set_CmdNumProgram(0x03);
        Secadora->set_CmdTiempoSecado((unsigned char) ui->ComboTiempoSecado3->currentIndex()+1);
        Secadora->set_CmdCalefaccion((unsigned char) ui->ComboCalefaccion3->currentIndex());
        if(ui->ComboTempSalida3->currentIndex()==0) Secadora->set_CmdTempSalida(0x00);
        else Secadora->set_CmdTempSalida((unsigned char)ui->ComboTempSalida3->currentIndex()+34);
        if(ui->ComboTempEntrada3->currentIndex()==0)Secadora->set_CmdTempEntrada(0x00);
        else Secadora->set_CmdTempEntrada((unsigned char)ui->ComboTempEntrada3->currentIndex()+39);
        Secadora->set_CmdAccionMecanica((unsigned char)ui->ComboAccionMecSec3->currentIndex()+1);
        Secadora->set_CmdVelRotacion((unsigned char)ui->ComboVelRotacion3->currentIndex()+1);
        Secadora->set_CmdTiempoEnfriamiento((unsigned char) ui->ComboTiempoEnfriamiento3->currentIndex());
        Secadora->SendCmd(Secadora->CmdEditProgramSec);
        Sleep(100);
    }


}

void MainWindow::on_GestionTarjetas_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(32);
}
