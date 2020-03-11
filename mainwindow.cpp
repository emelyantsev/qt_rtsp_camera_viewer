#include "mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), m_settings("outSmart", "LiveWatcher") {

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

    videoWidget = new VideoWidget(this);
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

    layout1->setContentsMargins(10, 10, 10, 10);

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



    QAction* pactShowHide = new QAction("&Show/Hide Application Window", this);

    connect(pactShowHide, SIGNAL(triggered()),
            this,         SLOT(slotShowHide())
           );


    QAction* pactQuit = new QAction("&Quit", this);
    connect(pactQuit, SIGNAL(triggered()), qApp, SLOT(quit()));

    m_ptrayIconMenu = new QMenu(this);
    m_ptrayIconMenu->addAction(pactShowHide);
    m_ptrayIconMenu->addAction(pactQuit);

    m_ptrayIcon = new QSystemTrayIcon(this);
    m_ptrayIcon->setContextMenu(m_ptrayIconMenu);
    m_ptrayIcon->setToolTip("LiveWatcher");
    m_ptrayIcon->setIcon(QPixmap(":/images/logo.png"));

    m_ptrayIcon->show();




    createMenus();




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
    else if (event->key() == Qt::Key_Escape) {

        //hide();
        qApp->quit();
    }

    videoWidget->setStyleSheet("border: 3px solid red");
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

void MainWindow::slotShowHide()
{
    setVisible(!isVisible());
}

void MainWindow::closeEvent(QCloseEvent * event)
{

    setVisible(false);
    event->ignore();
}

void MainWindow::showAbout() {

    QMessageBox::about(this, "About", "aleks.twin@gmail.com");

}

void MainWindow::createMenus()
{

    QAction *quit = new QAction("&Quit", this);
    QMenu *file;

    file = menuBar()->addMenu(tr("&File"));
    file->addAction(quit);

    connect(quit, &QAction::triggered, qApp, QApplication::quit);


    QMenu *settingsMenu;
    settingsMenu = menuBar()->addMenu(tr("&Settings"));

    QAction * colorSettingsAct = new QAction(tr("&Color settings"), this);

    colorSettingsAct->setStatusTip(tr("Show color settings"));
    connect(colorSettingsAct, &QAction::triggered, this, &MainWindow::showColorDialog);

    settingsMenu->addAction(colorSettingsAct);


    QMenu *helpMenu;
    helpMenu = menuBar()->addMenu(tr("&Help"));


    QAction * hotKeysAct = new QAction(tr("&Hot keys"), this);


    connect(hotKeysAct, &QAction::triggered, this, &MainWindow::showHotKeys);

    helpMenu->addAction(hotKeysAct);

    helpMenu->addSeparator();

    QAction * aboutAct = new QAction(tr("&About"), this);

    aboutAct->setStatusTip(tr("Create a new file"));
    connect(aboutAct, &QAction::triggered, this, &MainWindow::showAbout);

    helpMenu->addAction(aboutAct);

}


void MainWindow::showColorDialog() {

    if (!m_colorDialog) {

        QSlider *brightnessSlider = new QSlider(Qt::Horizontal);

        brightnessSlider->setRange(-100, 100);
        brightnessSlider->setValue(videoWidget->brightness());

        connect(brightnessSlider, &QSlider::sliderMoved, videoWidget, &QVideoWidget::setBrightness);
        connect(videoWidget, &QVideoWidget::brightnessChanged, brightnessSlider, &QSlider::setValue);

        QSlider *contrastSlider = new QSlider(Qt::Horizontal);
        contrastSlider->setRange(-100, 100);
        contrastSlider->setValue(videoWidget->contrast());
        connect(contrastSlider, &QSlider::sliderMoved, videoWidget, &QVideoWidget::setContrast);
        connect(videoWidget, &QVideoWidget::contrastChanged, contrastSlider, &QSlider::setValue);

        QSlider *hueSlider = new QSlider(Qt::Horizontal);
        hueSlider->setRange(-100, 100);
        hueSlider->setValue(videoWidget->hue());
        connect(hueSlider, &QSlider::sliderMoved, videoWidget, &QVideoWidget::setHue);
        connect(videoWidget, &QVideoWidget::hueChanged, hueSlider, &QSlider::setValue);

        QSlider *saturationSlider = new QSlider(Qt::Horizontal);
        saturationSlider->setRange(-100, 100);
        saturationSlider->setValue(videoWidget->saturation());
        connect(saturationSlider, &QSlider::sliderMoved, videoWidget, &QVideoWidget::setSaturation);
        connect(videoWidget, &QVideoWidget::saturationChanged, saturationSlider, &QSlider::setValue);

        QFormLayout *layout = new QFormLayout;
        layout->addRow(tr("Brightness"), brightnessSlider);
        layout->addRow(tr("Contrast"), contrastSlider);
        layout->addRow(tr("Hue"), hueSlider);
        layout->addRow(tr("Saturation"), saturationSlider);

        QPushButton *button = new QPushButton(tr("Close"));
        layout->addRow(button);

        m_colorDialog = new QDialog(this, Qt::WindowSystemMenuHint | Qt::WindowTitleHint);
        m_colorDialog->setWindowTitle(tr("Color Options"));
        m_colorDialog->setLayout(layout);

        connect(button, &QPushButton::clicked, m_colorDialog, &QDialog::close);
    }

    m_colorDialog->show();
}

void MainWindow::showHotKeys() {

    QLabel * q_label = new QLabel();

    q_label->setStyleSheet(styleSheet() );

    q_label->setText("F11 - full screeen\nEcsape - exit full screen\n");

    q_label->setContentsMargins(10,10,10,10);

    q_label->setWindowTitle("Hot keys");
    q_label->setFixedSize(240, 60);

    q_label->show();
}
