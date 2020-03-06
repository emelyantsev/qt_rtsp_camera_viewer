#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    //w.resize(900, 700);

    w.setWindowTitle("LiveWatcher");

    w.show();

    return a.exec();
}
