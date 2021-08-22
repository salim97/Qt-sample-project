#include "mynetworkclient.h"

MyNetworkClient::MyNetworkClient(QObject *parent) : QObject(parent)
{

}

void MyNetworkClient::connectToServer(QString ip, quint16 port)
{

    mysocket = new QTcpSocket(this) ;
mysocket->connectToHost(ip, port) ; // 3333  = port
// tu doit test la connecte wla la b mysocket.isopen()
// la maconectech alr delete mysocket ; mysocket = nullprt ;
// and connect if connected to server side

// or
    connect(mysocket, SIGNAL(readyRead()), this, SLOT(readRead()) );
}


void MyNetworkClient::readRead()
{
    QTextStream T(mysocket) ;
    auto texto = T.readAll() ;
}

void MyNetworkClient::sendData(QString msg)
{
    QTextStream t(mysocket) ;
    t << msg  ;
        mysocket->flush() ;
}

