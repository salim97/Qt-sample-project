#include "mynetworkserver.h"
#include "mynetworkserver.h"

MyNetworkServer::MyNetworkServer(QObject *parent) : QObject(parent)
{
currentPageIndex(1);
}

void MyNetworkServer::initializeServer(int port) {

    myserver = new QTcpServer(this) ;
    mysocket = nullptr ;
    myserver->listen(QHostAddress::Any, port);

    connect(myserver, &QTcpServer::newConnection,  [this](){
        qDebug() << "FUNC QTcpServer::newConnection" ;
        mysocket = myserver->nextPendingConnection() ;
        connect(mysocket, &QTcpSocket::readyRead,  [this](){
            QTextStream T(mysocket) ;
            QString texto = T.readAll() ;
qDebug() << texto ;
            if(texto == "page1") currentPageIndex(0);
            if(texto == "page2") currentPageIndex(1);
        });


    });
}


void MyNetworkServer::sendData(QString msg)
{
    QTextStream t(mysocket) ;
    t << msg  ;
        mysocket->flush() ;
}

