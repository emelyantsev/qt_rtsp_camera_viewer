#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;

    w.setWindowTitle("LiveWatcher");
    //w.setStyleSheet("background-color:blue;");

    w.show();

    QApplication::setQuitOnLastWindowClosed(false);

    return a.exec();
}
