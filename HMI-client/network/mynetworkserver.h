#ifndef MYNETWORKSERVER_H
#define MYNETWORKSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class MyNetworkServer : public QObject
{
    Q_OBJECT
public:
    explicit MyNetworkServer(QObject *parent = nullptr);

    void initializeServer(int port);
    void sendData(QString msg);
signals:

private slots:
    void readRead();
private:
        QTcpServer *myserver;
        QTcpSocket *mysocket ;
};

#endif // MYNETWORKSERVER_H
