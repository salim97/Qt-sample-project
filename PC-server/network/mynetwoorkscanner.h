#ifndef MYNETWOORKSCANNER_H
#define MYNETWOORKSCANNER_H

#include <QObject>
#include <QUdpSocket>
#include "mypropertyhelper.h"

#define enable_debug_udp true

class MyNetwoorkScanner : public QObject
{
    Q_OBJECT
public:
    explicit MyNetwoorkScanner(QObject *parent = nullptr);

    AUTO_PROPERTY(QStringList, remoteIPlist)

public:
        void startScanning(int timeoutMS = 1000);
    QString localIP();
public slots:
        void sendUDP(QString msg);
private slots:
    void readyReadUDP();
    void proccessData(QString data);
private:
    int udpPort = 5551 ;
    QUdpSocket *m_udpSocket = nullptr;


};

#endif // MYNETWOORKSCANNER_H
