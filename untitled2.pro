#-------------------------------------------------
#
# Project created by QtCreator 2017-08-24T16:15:03
#
#-------------------------------------------------

QT       += core gui multimedia multimediawidgets
QT       -= core network sql
QT       += core
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled2
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

DEFINES -= _MBCS
DEFINES += UNICODE


# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
    01_home.cpp \
    ServicioDB/c_mysql.cpp \
    ServicioEfectivo/billetesnv9.cpp \
    ServicioEfectivo/c_efectivothread.cpp \
    ServicioEfectivo/c_efectivothread2.cpp \
    ServicioEfectivo/c_flags_nv9.cpp \
    ServicioEfectivo/c_lecturabilletethread.cpp \
    ServicioEfectivo/c_paramhilos_nv9.cpp \
    ServicioEfectivo/paylink.cpp \
    ServicioMaquinas/c_lecturamaquinas.cpp \
    ServicioMaquinas/c_maquinas.cpp \
    ServicioTarjetas/c_flags_K720.cpp \
    ServicioTarjetas/c_functionsk720.cpp \
    ServicioTarjetas/c_ParamHilos_K720.cpp \
    ServicioTarjetas/c_tarjetathread.cpp \
    ServicioImpresion/c_couponprinter.cpp \
    ServicioImpresion/c_couponprinterthread.cpp \
    crearmaquina.cpp \
    c_LogFile.cpp \
    ServicioDB/c_LogFileDB.cpp \
    ServicioEfectivo/c_LogFileEfectivo.cpp \
    ServicioImpresion/c_LogFileImpresion.cpp \
    ServicioTarjetas/c_LogFileTarjetas.cpp \
    ServicioMaquinas/c_LogFileMaquinas.cpp


#    c_comandos_nv9.cpp

HEADERS += \
    01_home.h \
    ServicioDB/c_mysql.h \
    ServicioEfectivo/Aesimhei.h \
    ServicioEfectivo/billetesnv9.h \
    ServicioEfectivo/c_efectivothread.h \
    ServicioEfectivo/c_efectivothread2.h \
    ServicioEfectivo/c_flags_nv9.h \
    ServicioEfectivo/c_lecturabilletethread.h \
    ServicioEfectivo/c_paramhilos_nv9.h \
    ServicioEfectivo/paylink.h \
    ServicioMaquinas/c_lecturamaquinas.h \
    ServicioMaquinas/c_maquinas.h \
    ServicioTarjetas/c_flags_K720.h \
    ServicioTarjetas/c_functionsk720.h \
    ServicioTarjetas/c_ParamHilos_K720.h \
    ServicioTarjetas/c_tarjetathread.h \
    ServicioTarjetas/K720_Dll.h \
    ServicioImpresion/c_couponprinter.h \
    ServicioImpresion/c_couponprinterthread.h \
    ServicioImpresion/Commands.h \
    ServicioImpresion/SSPInclude.h \
    crearmaquina.h \
    c_LogFile.h \
    ServicioDB/c_LogFileDB.h \
    ServicioEfectivo/c_LogFileEfectivo.h \
    ServicioImpresion/c_LogFileImpresion.h \
    ServicioTarjetas/c_LogFileTarjetas.h \
    ServicioMaquinas/c_LogFileMaquinas.h


#    c_comandos_nv9.h

FORMS += \
    01_home.ui \
    crearmaquina.ui

RESOURCES += \
    imagenes.qrc


QT += testlib
QT +=sql




LIBS +="C:/Users/Central de Pago/Desktop/Central de Pago/Interfaz usuario/AutoServicio1.2/debug/K720_Dll.dll"
LIBS +="C:/Users/Central de Pago/Desktop/Central de Pago/Interfaz usuario/AutoServicio1.2/debug/ITLSSPProc.dll"



win32: LIBS += -L$$PWD/./ServicioEfectivo/ -lAesimhei

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

DISTFILES += \
    Letra DIN PRO/DINPro.otf \
    Letra DIN PRO/DINPro-BlackItalic.otf
