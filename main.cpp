#include "ckeypressconsumer.h"
#include "mainwindow.h"
#include <QApplication>
#include <QTime>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    CKeyPressConsumer *keyPressEater = new CKeyPressConsumer(&w,&a);
    a.installEventFilter(keyPressEater);
    w.setWindowTitle("Monsters vs. Heroes");
    QTime thetime = QTime::currentTime();
    qsrand((uint)thetime.msec());
    w.show();

    return a.exec();
}
