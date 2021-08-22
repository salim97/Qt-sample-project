#include "mynetworkserver.h"
#include "mynetworkserver.h"

MyNetworkServer::MyNetworkServer(QObject *parent) : QObject(parent)
{

}

void MyNetworkServer::initializeServer(int port) {

    myserver = new QTcpServer(this) ;
    mysocket = nullptr ;
    myserver->listen(QHostAddress::Any, port);

    connect(myserver, &QTcpServer::newConnection,  [this](){
        qDebug() << "FUNC QTcpServer::newConnection" ;
        mysocket = myserver->nextPendingConnection() ;
        connect(mysocket, SIGNAL(readyRead()), this, SLOT(readyRead()) );
    });
}

void MyNetworkServer::readRead(){
    QTextStream T(mysocket) ;
    auto texto = T.readAll() ;
}

void MyNetworkServer::sendData(QString msg)
{
    QTextStream t(mysocket) ;
    t << msg  ;
        mysocket->flush() ;
}

