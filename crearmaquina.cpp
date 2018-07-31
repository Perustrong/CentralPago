#include "crearmaquina.h"
#include "ui_crearmaquina.h"

CrearMaquina::CrearMaquina(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CrearMaquina)
{
    ui->setupUi(this);
}

CrearMaquina::~CrearMaquina()
{
    delete ui;
}

void CrearMaquina::on_btnCerrarCrear_clicked()
{
    string Action;
    Action.append("3");
    Action = Action + (char)0xb8;
    Action.append("1");
    Action = Action + (char)0xb8 + '0';
    emit CrearMaquinaAction(Action);
}

void CrearMaquina::on_btnAnadirCrear_clicked()
{
    string CadenaEnvio;
    string IDComando = {'2'};
    string PasoCadena;
    string Identificador = ui->ValorNuevoID->text().toStdString();
    string NombreMaquina = ui->NombreNuevaMaq->text().toStdString();
    string strSizeMensaje;
    stringstream AuxSize;

    cout << "Identificador "<< Identificador<<endl;
    cout << "NombreMaquina "<< NombreMaquina<<endl;
    PasoCadena = (char)0xb8;

    int SizeMensaje = IDComando.size() + Identificador.size()+ NombreMaquina.size();
    SizeMensaje = SizeMensaje + 3;

    if(SizeMensaje < 8)
    {
        SizeMensaje = SizeMensaje + 1;
    }
    else
    {
        SizeMensaje = SizeMensaje + 2;
    }
     cout << "SizeMensaje" << SizeMensaje<<endl;
    AuxSize << SizeMensaje;
    strSizeMensaje = AuxSize.str();

    cout <<"strSizeMensaje " <<strSizeMensaje<<endl;

    CadenaEnvio.append(strSizeMensaje);
    CadenaEnvio.append(PasoCadena);
    CadenaEnvio.append(IDComando);
    CadenaEnvio.append(PasoCadena);
    CadenaEnvio.append(Identificador);
    CadenaEnvio.append(PasoCadena);
    CadenaEnvio.append(NombreMaquina);

  /*  for (int i = 0; i<sizeof(CadenaEnvio);i++)
    {
        printf("Comando %x",CadenaEnvio[i]);
        cout << "Comando decimal " << CadenaEnvio[i]<<endl;
    }*/

    emit CrearMaquinaAction(CadenaEnvio);

}
