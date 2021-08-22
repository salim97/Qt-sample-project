#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    myNetwoorkScanner = new MyNetwoorkScanner(this);
//    connect(myNetwoorkScanner, SIGNAL(remoteIPlistChanged()), this, SLOT(updateListIP()));
    connect(myNetwoorkScanner, &MyNetwoorkScanner::remoteIPlistChanged,  [this](QStringList value){
        qDebug() << "remoteIPlistChanged " << value ;
    });

    myNetworkServer = new MyNetworkServer(this);
    myNetworkServer->initializeServer(9853);

    connect(myNetworkServer, &MyNetworkServer::currentPageIndexChanged,  [this](int value){
        qDebug() << "currentPageIndexChanged " << value ;
        this->ui->stackedWidget->setCurrentIndex(value) ;
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}

