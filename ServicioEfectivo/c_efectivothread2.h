#ifndef C_EFECTIVOTHREAD2_H
#define C_EFECTIVOTHREAD2_H




#include <QtCore>
#include <QDebug>
#include "ServicioEfectivo/billetesnv9.h"
//#include "01_home.h"
#include "ServicioEfectivo/c_lecturabilletethread.h"
#include <ServicioEfectivo/c_LogFileEfectivo.h>

class c_LecturaBilleteThread;

class c_EfectivoThread2 : public QThread
{
    Q_OBJECT
public:
    explicit c_EfectivoThread2(QObject *parent = 0);
    void Stop();
    void run();
    BilletesNV9 SistemaBilletes;

    c_LecturaBilleteThread *BillReadThread;

signals:

    void LecturaBillete(float number);

public slots:

    void onReadBill(float number);

private:

    bool Run = true;
    c_LogFileEfectivo LogEfectivo;
    bool LogActivo = false;



};

#endif // C_EFECTIVOTHREAD2_H
