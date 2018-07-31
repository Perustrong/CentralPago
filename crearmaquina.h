#ifndef CREARMAQUINA_H
#define CREARMAQUINA_H

#include <QDialog>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

namespace Ui {
class CrearMaquina;
}

class CrearMaquina : public QDialog
{
    Q_OBJECT

public:
    explicit CrearMaquina(QWidget *parent = 0);
    ~CrearMaquina();


private slots:
    void on_btnCerrarCrear_clicked();

    void on_btnAnadirCrear_clicked();

signals:
    //String comunicación con el principal- estructura : byte 1 tamaño del mensaje incluyendo al byte de tamaño; resto mensaje
    //Códigos correspondiente solo a los datos : 1 -Cerrar Ventana  ; Tamaño Mensaje + 0XB8 + 2 -Añadir máquina + 0xB8 + Identificador + 0xB8 + Nombre asignado
    void CrearMaquinaAction(string Action);

private:
    Ui::CrearMaquina *ui;
};

#endif // CREARMAQUINA_H
