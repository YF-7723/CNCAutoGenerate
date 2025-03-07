#include "mainwindow.h"
//#include "parameterwidget.h"
#include "loginwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "mytcpsocket.h"
#include "registerwindow.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    LoginWindow lw ;
    MyTcpSocket s ;





    QObject::connect(&lw, &LoginWindow::successLogin, &w, &MainWindow::show) ;
    QObject::connect(&w, &MainWindow::reLogin, &lw, &LoginWindow::show) ;
    QObject::connect(&s, &MyTcpSocket::successConnect, &lw, &LoginWindow::tcpConnect) ;
    QObject::connect(&s, &MyTcpSocket::cannotConnect, &lw, &LoginWindow::tcpDisconnect) ;

    QObject::connect(&s, &MyTcpSocket::successConnect, &w, &MainWindow::tcpConnect) ;
    QObject::connect(&s, &MyTcpSocket::cannotConnect, &w, &MainWindow::tcpDisconnect) ;

    QObject::connect(&lw, &LoginWindow::sendAccount, &s, &MyTcpSocket::sendMessages) ;
    QObject::connect(&s, &MyTcpSocket::getAccountData, &lw, &LoginWindow::checkPassword) ;

    QObject::connect(&lw, &LoginWindow::sendNewAccount, &s, &MyTcpSocket::sendMessages) ;
    QObject::connect(&s, &MyTcpSocket::getReplyNew, &lw, &LoginWindow::brigeReplyNew) ;

    QObject::connect(&w, &MainWindow::sendHoleLianLists, &s, &MyTcpSocket::sendMessages) ;
    QObject::connect(&s, &MyTcpSocket::getParameter, &w, &MainWindow::setHoleLianLists) ;

    QObject::connect(&w, &MainWindow::closeSocket, &s, &MyTcpSocket::close) ;
    QObject::connect(&lw, &LoginWindow::startInitLists, &w, MainWindow::initHoleLianLists) ;

    QObject::connect(&lw, &LoginWindow::initAccount, &s, &MyTcpSocket::initAccount) ;
    s.startConnect();

    lw.show() ;
    //w.initHoleLianLists();
    //w.show();
    return a.exec();
}
