#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <mynetwoorkscanner.h>
#include <mynetworkclient.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_scan_network_clicked();

    void on_pushButton_goto_page_1_clicked();

    void on_pushButton_goto_page_2_clicked();

    void on_pushButton_send_image_clicked();

    void on_listWidget_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    MyNetwoorkScanner *myNetwoorkScanner;
    MyNetworkClient *myNetworkClient;
};
#endif // MAINWINDOW_H
