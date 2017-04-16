#include "keypressconsumer.h"
#include "mainwindow.h"
#include <QApplication>
#include <QTime>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    KeyPressConsumer *keyPressEater = new KeyPressConsumer(&w,&a);
    a.installEventFilter(keyPressEater);
    w.setWindowTitle("SpriteWalker");
    QTime thetime = QTime::currentTime();
    qsrand((uint)thetime.msec());
    w.show();

    return a.exec();
}
