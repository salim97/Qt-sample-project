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
        this->ui->listWidget->clear();
        this->ui->listWidget->addItems(value);
    });
    myNetworkClient =new MyNetworkClient(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_scan_network_clicked()
{
    myNetwoorkScanner->startScanning();
}


void MainWindow::on_pushButton_goto_page_1_clicked()
{
myNetworkClient->sendData("page1");
}


void MainWindow::on_pushButton_goto_page_2_clicked()
{
myNetworkClient->sendData("page2");
}


void MainWindow::on_pushButton_send_image_clicked()
{

}



void MainWindow::on_listWidget_clicked(const QModelIndex &index)
{
    qDebug() << Q_FUNC_INFO << index.data().toString();
    myNetworkClient->connectToServer(index.data().toString(),9853 );

}
