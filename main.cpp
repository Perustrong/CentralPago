#include "01_home.h"
#include <QApplication>
Q_DECLARE_METATYPE(string)


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

/*
   QMediaPlayer* player = new QMediaPlayer;
   QVideoWidget* vw = new QVideoWidget;
   player->setVideoOutput(vw);
   player->setMedia(QUrl::fromLocalFile("C:/Users/Genuix/Desktop/Videos_Nature/Oregon_Nights_4K.mp4"));
   vw->setGeometry(100,100,300,400);
   vw->show();
   player->play();

    qDebug () << player -> state();*/



    return a.exec();
}
