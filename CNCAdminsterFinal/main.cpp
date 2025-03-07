#include "mainwindow.h"
#include "loginwindow.h"
#include "mytcpsocket.h"
#include "parameterwidget.h"
#include <QApplication>
#include "choosewindow.h"
#include <QDateTime>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QDateTime currentDateTime = QDateTime::currentDateTime();
    QDateTime nextWeek = currentDateTime.addDays(7); // 当前日期时间加7天
    qDebug() << nextWeek ;
    qDebug() << nextWeek.toString() ;

    MainWindow w;
    LoginWindow lw ;
    ChooseWindow c ;
    MyTcpSocket s ;
    ParameterWidget p ;



    QObject::connect(&lw, &LoginWindow::successLogin, &c, &ChooseWindow::show) ;
    QObject::connect(&lw, &LoginWindow::startInitLists, &p, &ParameterWidget::initAllLists) ;
    QObject::connect(&lw, &LoginWindow::sendAccount, &s, &MyTcpSocket::sendMessages) ;
    QObject::connect(&lw, &LoginWindow::sendNewAccount, &s, &MyTcpSocket::sendMessages) ;
    //QObject::connect(&lw, &LoginWindow::startInitUserDatas, &w, &MainWindow::initUserDatas) ;

    QObject::connect(&w, &MainWindow::mainWindowClose, &c, &ChooseWindow::show) ;
    QObject::connect(&w, &MainWindow::sendGetUserDatas, &s, &MyTcpSocket::sendMessages) ;
    QObject::connect(&w, &MainWindow::deleteUserAccount, &s, &MyTcpSocket::sendMessages) ;
    QObject::connect(&w, &MainWindow::improveUserAccount, &s, &MyTcpSocket::sendMessages) ;
    QObject::connect(&w, &MainWindow::accessUserAccount, &s, &MyTcpSocket::sendMessages) ;
    QObject::connect(&w, &MainWindow::reduceUserAccount, &s, &MyTcpSocket::sendMessages) ;
    QObject::connect(&w, &MainWindow::reduceAdUserAccount, &s, &MyTcpSocket::sendMessages) ;

    QObject::connect(&c, &ChooseWindow::chooseWindowClose, &s, &MyTcpSocket::close) ;
    QObject::connect(&c, &ChooseWindow::setAd, &w, &MainWindow::show) ;
    QObject::connect(&c, &ChooseWindow::setAd, &w, &MainWindow::initUserDatas) ;
    QObject::connect(&c, &ChooseWindow::setP, &p, &ParameterWidget::show) ;
    QObject::connect(&c, &ChooseWindow::failToConnect, &p, &ParameterWidget::tcpDisconnect) ;
    QObject::connect(&c, &ChooseWindow::failToConnect, &w, &MainWindow::tcpDisconnect) ;
    QObject::connect(&c, &ChooseWindow::reLogin, &lw, &LoginWindow::show) ;
    QObject::connect(&c, &ChooseWindow::sendUpdatePassnum, &s, &MyTcpSocket::sendMessages) ;

    QObject::connect(&s, &MyTcpSocket::getParameter, &p, &ParameterWidget::readDataFromJsonFile) ;
    QObject::connect(&s, &MyTcpSocket::getAccountData, &lw, &LoginWindow::checkPassword) ;
    QObject::connect(&s, &MyTcpSocket::successConnect, &lw, &LoginWindow::tcpConnect) ;
    QObject::connect(&s, &MyTcpSocket::cannotConnect, &lw, &LoginWindow::tcpDisconnect) ;
    QObject::connect(&s, &MyTcpSocket::successConnect, &c, &ChooseWindow::tcpConnect) ;
    QObject::connect(&s, &MyTcpSocket::cannotConnect, &c, &ChooseWindow::tcpDisconnect) ;
    QObject::connect(&s, &MyTcpSocket::getReplyNew, &lw, &LoginWindow::brigeReplyNew) ;
    QObject::connect(&s, &MyTcpSocket::getUserDatas, &w, &MainWindow::getUserDatas) ;
    QObject::connect(&s, &MyTcpSocket::getPassnum, &c, &ChooseWindow::haveUpdatePassnum) ;

    QObject::connect(&p, &ParameterWidget::sendListsGet, &s, &MyTcpSocket::sendMessages) ;
    QObject::connect(&p, &ParameterWidget::parameterWidgetClose, &c, &ChooseWindow::show) ;
    QObject::connect(&p, &ParameterWidget::sendWrite, &s, &MyTcpSocket::writeSize) ;

    /*
    void getMessage(QString message) ;
    void getAccountData(QString accountData) ;
    void successConnect() ;
    void cannotConnect() ;
    void getReplyNew(QString) ;
    void getParameter(QString) ;
    */


    s.startConnect();

    lw.show();

    return a.exec();
}
