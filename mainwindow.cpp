#include "mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) , m_settings("outSmart", "LiveWatcher")
{

    ip_address_edit = new QLineEdit;
    login_edit = new QLineEdit;

    password_edit = new QLineEdit;
    password_edit->setEchoMode(QLineEdit::Password);


    label0 = new QLabel;
    label0->setText("IP address:");

    label1 = new QLabel;
    label1->setText("Login:");

    label2 = new QLabel;
    label2->setText("Password:");

    button1 = new QPushButton;
    button1->setText("Connect");

    connect(button1, SIGNAL(clicked()), SLOT(slotConnectDisconnect()) );

    videoWidget = new VideoWidget;
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

    spacer0 = new QSpacerItem(30, 40, QSizePolicy::Minimum, QSizePolicy::Maximum);
    layout1->addSpacerItem(spacer0);

    layout1->addWidget(button1);

    layout2 = new QVBoxLayout;
    layout2->addWidget(videoWidget);

    layout0 = new QHBoxLayout;
    layout0->addLayout(layout2);
    layout0->addLayout(layout1);

    layout0->setAlignment(layout1, Qt::AlignTop) ;

    QWidget * window = new QWidget();
    window->setLayout(layout0);
    setCentralWidget(window);



    QRegExpValidator *ipValidator = new QRegExpValidator(ipRegex, this);

    ip_address_edit->setValidator(ipValidator);

    readSettings();

}

MainWindow::~MainWindow()
{
    writeSettings();
}

void MainWindow::slotConnectDisconnect()
{

    if (!is_connected) {




        QString login = login_edit->text() ;
        QString password = password_edit->text() ;
        QString ip_address = ip_address_edit->text() ;


        if (!ipRegex1.match(ip_address).hasMatch() ) {

            QMessageBox::critical(this, "Error", "Wrong format for IP address");
            return;
        }

        url0 = QUrl("rtsp://" + ip_address + ":554/ISAPI/Streaming/Channels/102");

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

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_F11) {

        if (videoWidget != nullptr) {
            videoWidget->setFullScreen(true);
        }
    }
}


void MainWindow::writeSettings() {

    m_settings.beginGroup("/Settings");
    m_settings.setValue("/ip_address", ip_address_edit->text() ) ;
    m_settings.setValue("/login", login_edit->text() );
    m_settings.setValue("/password", password_edit->text() );
    m_settings.endGroup();

}

void MainWindow::readSettings() {

    m_settings.beginGroup("/Settings");
    ip_address_edit->setText(m_settings.value("/ip_address", "").toString() );
    login_edit->setText(m_settings.value("/login", "admin").toString() );
    password_edit->setText(m_settings.value("/password", "Freedom!00##").toString() );
    m_settings.endGroup();

}
