#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <mynetwoorkscanner.h>
#include <mynetworkserver.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    MyNetwoorkScanner *myNetwoorkScanner;
    MyNetworkServer *myNetworkServer;
};
#endif // MAINWINDOW_H
