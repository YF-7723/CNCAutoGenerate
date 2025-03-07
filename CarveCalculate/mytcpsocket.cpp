#include "mytcpsocket.h"

MyTcpSocket::MyTcpSocket(QObject *parent)
    : QTcpSocket{parent}
{
    connect(this, &MyTcpSocket::readyRead, this, &MyTcpSocket::readData) ;
    timer.setInterval(10000);

    connect(&timer,&QTimer::timeout,this,[=](){
        QString msg = "NULL" ;
        if (account != "") {
            msg = msg + " " + account ;
        }
        if(this->write(msg.toUtf8())<0)//8288242
        {
            this->connectToHost(ip,port);
            if(this->waitForConnected(1000))
            {
                qDebug() << "success connect" ;
                emit successConnect() ;
            }
            else
            {
                account = "" ;
                emit cannotConnect() ;
            }
        }
    });
}

void MyTcpSocket::initAccount(QString msg) {
    account = msg ;
}

void MyTcpSocket::sendMessages(QString messages) {
    qDebug() << "sendMessages" << messages;
    qDebug() << this->write(messages.toUtf8()) ;
}

void MyTcpSocket::readData() {
    QString message = this->readAll() ;
    qDebug() << "receive data" << message ;

    if (haveReceivedParameter == true) {
        parameterBuff.append(message) ;
        if (parameterBuff.length() >= parameterLength) {
            haveReceivedParameter = false ;
            emit getParameter(parameterBuff) ;
            parameterBuff.clear() ;
        }
        return ;
    }

    QStringList messages ;
    messages.append(message.mid(0, message.indexOf(' '))) ;
    //qDebug() << "1111" ;
    messages.append(message.mid(message.indexOf(' ') + 1)) ;
    qDebug () << "receive type" << messages[0] ;
    if (messages[0] == "accountdata1") {
        emit getAccountData(messages[1]);
        return ;
    }
    if (messages[0] == "accountnew1") {
        emit getReplyNew(messages[1]) ;
        return ;
    }
    if (messages[0] == "NULL") {
        account = "" ;
        emit cannotConnect() ;
        return ;
    }
    if (messages[0] == "parameterget") {
        haveReceivedParameter = true ;
        int maxSize ;
        int dataSize = (messages[1].mid(1, QString(messages[1][0]).toInt())).toInt() ;
        maxSize = dataSize + QString(messages[1][0]).toInt() + 1 ;
        qDebug () << "getMaxSize Parameter" << maxSize ;
        parameterLength = dataSize ;
        parameterBuff = messages[1].mid(QString(messages[1][0]).toInt() + 1);
       // emit getParameter(messages[1]) ;
        return ;
    }
}

void MyTcpSocket::startConnect() {
    this->connectToHost(ip, port);

    if (this->waitForConnected(3000)) {
        qDebug() << "success connect" ;
        emit successConnect();
        timer.start() ;
    }
    else {
        emit cannotConnect();
        timer.start();
    }
}
