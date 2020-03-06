#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QPushButton>
#include <QLineEdit>
#include <QLabel>

#include <QVideoWidget>
#include <QMediaPlayer>

#include <QUrl>
#include <QNetworkRequest>

#include <QKeyEvent>
#include "videowidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QHBoxLayout * layout0;
    QVBoxLayout * layout1;
    QVBoxLayout * layout2;

    QLabel * label0;
    QLabel * label1;
    QLabel * label2;

    QPushButton * button1;

    QLineEdit * ip_address_edit;
    QLineEdit * login_edit;
    QLineEdit * password_edit;

    VideoWidget * videoWidget;

    QMediaPlayer * player0;

    QUrl url0;
    QNetworkRequest requestRtsp0;
    bool is_connected;

public:

    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *);

private slots:
    void slotConnectDisconnect ();

};

#endif // MAINWINDOW_H
