#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include "registerwindow.h"

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

    void tcpConnect() ;
    void tcpDisconnect() ;
    void checkPassword(QString tempPassword) ;

    bool isTcpConnect = false ;

    void brigeNewAccount(QString messages) ;
    void brigeReplyNew(QString messages) ;
    void setAccount() ;

    RegisterWindow *r ;
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

signals:
    void successLogin();
    void sendAccount(QString) ;
    void sendNewAccount(QString) ;
    void sendReplyNew(QString) ;
    void startInitLists() ;
    void startInitUserDatas() ;
private:
    Ui::LoginWindow *ui;


    QString account ;
    QString password ;

    QString filePath = "D:\\CarveCalculate\\Logs\\accountad.txt" ;
};

#endif // LOGINWINDOW_H
