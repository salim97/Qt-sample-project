#ifndef MYNETWORKCLIENT_H
#define MYNETWORKCLIENT_H

#include <QObject>
#include <QTcpSocket>

class MyNetworkClient : public QObject
{
    Q_OBJECT
public:
    explicit MyNetworkClient(QObject *parent = nullptr);

    void sendData(QString msg);
    void connectToServer(QString ip, quint16 port);
signals:

private slots:
    void readRead();
private:
    QTcpSocket *mysocket;
};

#endif // MYNETWORKCLIENT_H
