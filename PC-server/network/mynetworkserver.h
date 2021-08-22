#ifndef MYNETWORKSERVER_H
#define MYNETWORKSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include "mypropertyhelper.h"

class MyNetworkServer : public QObject
{
    Q_OBJECT
public:
    explicit MyNetworkServer(QObject *parent = nullptr);

    AUTO_PROPERTY(int, currentPageIndex)
public:

    void initializeServer(int port);
    void sendData(QString msg);
signals:


private:
        QTcpServer *myserver;
        QTcpSocket *mysocket ;
};

#endif // MYNETWORKSERVER_H
