#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QSpacerItem>

#include <QVideoWidget>
#include <QMediaPlayer>

#include <QUrl>
#include <QNetworkRequest>

#include <QKeyEvent>

#include <QRegExpValidator>
#include <QRegularExpression>

#include <QMessageBox>

#include <QSettings>

#include "videowidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QHBoxLayout * layout0;
    QVBoxLayout * layout1;
    QVBoxLayout * layout2;
    QSpacerItem * spacer0;

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
    bool is_connected = false;

    QString ipRange = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";
    QRegExp ipRegex = QRegExp("^" + ipRange + "\\." + ipRange + "\\." + ipRange + "\\." + ipRange + "$");
    QRegularExpression ipRegex1 = QRegularExpression("^" + ipRange + "\\." + ipRange + "\\." + ipRange + "\\." + ipRange + "$");


    QSettings m_settings;

public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void writeSettings();
    void readSettings();

protected:
    void keyPressEvent(QKeyEvent *);

private slots:
    void slotConnectDisconnect ();

};

#endif // MAINWINDOW_H
