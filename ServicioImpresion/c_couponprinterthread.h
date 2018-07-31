#ifndef C_COUPONPRINTERTHREAD_H
#define C_COUPONPRINTERTHREAD_H


#include <QtCore>
#include <QDebug>
#include <ServicioImpresion/c_couponprinter.h>
//#include <01_home.h>
#include <string>

class c_CouponPrinterThread: public QThread
{
    Q_OBJECT
public:

    bool ActiveThread = false;


    explicit c_CouponPrinterThread(QObject *parent =0);
    void run();

signals:

    void EventoImpresora(int evento);

private slots:

    void onPrinterFunction(string Auxfunction);


private:

    c_CouponPrinter Impresora;
    SSP_COMMAND commandStructure;
};

#endif // C_COUPONPRINTERTHREAD_H




