#include "mynetwoorkscanner.h"

#include <QEventLoop>
#include <QTimer>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkInterface>

MyNetwoorkScanner::MyNetwoorkScanner(QObject *parent) : QObject(parent)
{
    m_udpSocket = new QUdpSocket(this);
    if(!m_udpSocket->bind(udpPort, QUdpSocket::ShareAddress))
        qDebug() << "m_udpSocket : " + m_udpSocket->errorString() ;
    else
        qDebug() << "UDP 127.0.0.1:" +QString::number(udpPort)+" LISTENING." ;

    connect(m_udpSocket, SIGNAL(readyRead()), this, SLOT(readyReadUDP()));

}

void MyNetwoorkScanner::startScanning(int timeoutMS )
{
    QJsonObject recordObject;
            recordObject.insert("ip_of_sender", QJsonValue::fromVariant(localIP()));
    recordObject.insert("type", QJsonValue::fromVariant("request"));
    recordObject.insert("command", QJsonValue::fromVariant("scan"));
    QJsonDocument doc(recordObject);
    qDebug() << doc.toJson();
    sendUDP(doc.toJson());

    QEventLoop loop;
    QTimer getTimer;
    QTimer::connect(&getTimer,SIGNAL(timeout()),&loop, SLOT(quit()));

    getTimer.start(timeoutMS); // 10000 milliSeconds wait period for get() method to work properly
    loop.exec();




}

void MyNetwoorkScanner::sendUDP(QString msg)
{
    qDebug() << "msg: " << msg  ;
    QByteArray datagram = msg.toUtf8() ;
    m_udpSocket->writeDatagram(datagram.data(), datagram.size(),
                               //QHostAddress::Broadcast, udpPort);
                               QHostAddress("255.255.255.255"), udpPort);
}

void MyNetwoorkScanner::readyReadUDP()
{
    while (m_udpSocket->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(m_udpSocket->pendingDatagramSize());
        m_udpSocket->readDatagram(datagram.data(), datagram.size());

        QString data = datagram;
        if(enable_debug_udp)
            qDebug() << "readyReadUDP: " << data ;

        proccessData(data) ;

    }
}

void MyNetwoorkScanner::proccessData(QString data)
{
    QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());
    if(doc.isObject() == false) {
        qDebug() << "It is not a JSON object";
        return ;
    }
    //get the jsonObject
    QJsonObject jObject = doc.object();
    QJsonValue command = jObject.value("command");

    if( jObject.value("type").toString() == "request" && jObject.value("command").toString() == "scan")
    {
        if(jObject.value("ip_of_sender").toString() ==localIP()) return ;

        QJsonObject recordObject;
        recordObject.insert("type", QJsonValue::fromVariant("response"));
        recordObject.insert("ip_of_sender", QJsonValue::fromVariant(localIP()));
        recordObject.insert("command", QJsonValue::fromVariant("scan"));


        recordObject.insert("ip", QJsonValue::fromVariant(localIP()));
        QJsonDocument doc(recordObject);
        qDebug() << doc.toJson();
        sendUDP(doc.toJson());
    }

    if( jObject.value("type").toString() == "response" && jObject.value("command").toString() == "scan")
    {

        QJsonValue ip = jObject.value("ip");
        qDebug() << "ip: " << ip  << localIP();

        if(ip != localIP())
        remoteIPlist( remoteIPlist() << ip.toString() );


    }




    //this part of code if you don't want standard format like JSON or XML then you can use your own format
    //    if(data.contains("<angle>"))
    //    {
    //                    data.replace("<angle>","");
    //                    angle(data.toInt());
    //    }
    //    else if(data.contains("<distance_CM>"))
    //    {
    //                    data.replace("<distance_CM>","");
    //                    distance_CM(data.toInt());
    //    }
    //    else if(data.contains("<rightToLeft>"))
    //    {
    //                    data.replace("<rightToLeft>","");
    //                    if(data == "1")
    //                        rightToLeft(true);
    //                    else
    //                        rightToLeft(false);
    //    }
}

QString MyNetwoorkScanner::localIP()
{
    QList<QNetworkInterface> allInterfaces = QNetworkInterface::allInterfaces();
    QNetworkInterface eth;
        QString localIP ;
    foreach(eth, allInterfaces) {
        QList<QNetworkAddressEntry> allEntries = eth.addressEntries();
        QNetworkAddressEntry entry;
        foreach (entry, allEntries) {
            if(entry.ip().toString().contains("192.168."))
                localIP = entry.ip().toString() ;
        }
    }
    return localIP;
}
