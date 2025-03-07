#ifndef MYTCPSOCKET_H
#define MYTCPSOCKET_H

#include <QTcpSocket>
#include <QObject>
#include <QTimer>
class MyTcpSocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit MyTcpSocket(QObject *parent = nullptr);
    bool isConnect() ;
    void startConnect() ;
    void sendMessages(QString messages) ;

    void initAccount(QString) ;
signals:
    void getMessage(QString message) ;
    void getAccountData(QString accountData) ;
    void successConnect() ;
    void cannotConnect() ;
    void getReplyNew(QString) ;
    void getParameter(QString) ;
private:
    void readData() ;
    QString ip = "47.100.139.128";
    int port = 8080;
    QTimer timer ;
    QTimer timer2 ;
    bool haveReceivedParameter = false;
    QString parameterBuff ;
    QString account = "";
    int parameterLength ;

};

#endif // MYTCPSOCKET_H

/*
export PATH=/home/yiran/Qt5.14.2/5.14.2/gcc_64/bin:$PATH
export LIB_PATH=/home/yiran/Qt5.14.2/5.14.2/gcc_64/lib:$LIB_PATH
export PLUGIN_PATH=/home/yiran/Qt5.14.2/5.14.2/gcc_64/plugins:$PLUGIN_PATH
export QML2_PATH=/home/yiran/Qt5.14.2/5.14.2/gcc_64/qml:$QML2_PATH
*/
