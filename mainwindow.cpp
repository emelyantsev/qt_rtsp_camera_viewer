#include "mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    ip_address_edit = new QLineEdit;
    login_edit = new QLineEdit;

    password_edit = new QLineEdit;
    password_edit->setEchoMode(QLineEdit::Password);

    label0 = new QLabel;
    label0->setText("IP address");

    label1 = new QLabel;
    label1->setText("Login");

    label2 = new QLabel;
    label2->setText("Password");

    button1 = new QPushButton;
    button1->setText("Connect");

    connect(button1, SIGNAL(clicked()), SLOT(slotConnectDisconnect()) );

    videoWidget = new QVideoWidget;
    videoWidget->setMinimumSize(704, 576);

    player0 = new QMediaPlayer;
    player0->setVideoOutput(videoWidget);


    layout1 = new QVBoxLayout;
    layout1->addWidget(label0);
    layout1->addWidget(ip_address_edit);
    layout1->addWidget(label1);
    layout1->addWidget(login_edit);
    layout1->addWidget(label2);
    layout1->addWidget(password_edit);
    layout1->addWidget(button1);

    layout2 = new QVBoxLayout;
    layout2->addWidget(videoWidget);

    layout0 = new QHBoxLayout;
    layout0->addLayout(layout2);
    layout0->addLayout(layout1);


    QWidget * window = new QWidget();
    window->setLayout(layout0);
    setCentralWidget(window);

}

MainWindow::~MainWindow()
{

}

void MainWindow::slotConnectDisconnect()
{

    if (!is_connected) {


        QString login = login_edit->text() ;
        QString password = password_edit->text() ;
        QString ip_address = ip_address_edit->text() ;

        url0 = QUrl("rtsp://" + ip_address + ":554/ISAPI/Streaming/Channels/102");

        //qDebug() << url0.toString() ;
        //exit(0);

        url0.setUserName(login);
        url0.setPassword(password);

        requestRtsp0 = QNetworkRequest(url0);

        player0->setMedia(requestRtsp0);
        player0->play();

        is_connected = true;

        button1->setText("Disconnect");

    }
    else {

        player0->stop();
        button1->setText("Connect");
        is_connected = false;
    }

}
