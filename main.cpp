#include "mainwindow.h"

#include <QApplication>

#include <QFile>
#include <QTextStream>
#include <QDebug>

int main(int argc, char *argv[])
{

    QFile f(":qdarkstyle/style.qss");
    f.open(QFile::ReadOnly | QFile::Text);
    QTextStream ts(&f);
    QString s = ts.readAll();
    f.close();


    QApplication a(argc, argv);

    MainWindow w;

    w.setWindowTitle("LiveWatcher");
    w.setStyleSheet(s);

    w.show();

    QApplication::setQuitOnLastWindowClosed(false);





    return a.exec();
}
