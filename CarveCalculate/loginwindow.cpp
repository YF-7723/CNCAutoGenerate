#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <QMessageBox>
#include <QDir>
#include <QFile>
LoginWindow::LoginWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("登录");
    ui->lineEdit_2->setEchoMode(QLineEdit::Password);

    setAccount() ;

    r = new RegisterWindow() ;
    //r->setWindowFlags(Qt::Widget | Qt::FramelessWindowHint);

    connect(r, &RegisterWindow::sendNewAccount, this, &LoginWindow::brigeNewAccount) ;
    connect(this, &LoginWindow::sendReplyNew, r, &RegisterWindow::getReplyNew) ;
   // QMessageBox::information(this, "警告", "无法检测到服务器，请检查网络连接") ;
}

void LoginWindow::setAccount() {
    QFile file(filePath);

    if (file.exists()) {
        //qDebug() << "The file exists.";
        if (file.open(QIODevice::ReadOnly)) {
            ui->lineEdit->setText(file.readAll());
        }
    }
}

void LoginWindow::brigeNewAccount(QString messages) {
    emit sendNewAccount(messages);
}

void LoginWindow::brigeReplyNew(QString messages) {
    emit sendReplyNew(messages);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_pushButton_clicked()
{
    r->show();
}


void LoginWindow::on_pushButton_2_clicked()
{

    if (ui->lineEdit->text().isEmpty() || ui->lineEdit_2->text().isEmpty()) {
        QMessageBox::information(this, "提示", "账号或密码为空") ;
        return ;
    }

    account = ui->lineEdit->text() ;
    password = ui->lineEdit_2->text() ;

    if (account == "DF-16A" && password == "185930") {
        QMessageBox::information(this, "提示", "离线登录模式") ;
        emit successLogin() ;
        this->close() ;
    }

    if(isTcpConnect == false){
        QMessageBox::information(this, "提示", "未连接到服务器") ;
        return ;
    }

    if (isTcpConnect == true) {
        QString messages = "accountdata1 " ;
        emit sendAccount(messages + account) ;
    }
    return ;
}

void LoginWindow::checkPassword(QString tempPassword) {
    qDebug () << "tempPwd" << tempPassword ;
    if (tempPassword == password) {
        QMessageBox::information(this, "提示", "欢迎使用！") ;

        QFile file(filePath);
        QDir dir;
        if (!dir.exists(filePath)) {
            dir.mkpath(QFileInfo(filePath).path());
        }
        if (file.open(QIODevice::WriteOnly)) {
            file.write(account.toUtf8());
            file.close();
        }

        emit successLogin() ;
        emit startInitLists() ;
        emit initAccount(account) ;
        this->hide() ;
    } else {
        QMessageBox::information(this, "提示", "账号或密码错误\n或联系管理员审核资格") ;
        return ;
    }
}

void LoginWindow::tcpConnect() {
    qDebug() << "网络连接成功" ;
    if (isTcpConnect == false && !this->isHidden())
        QMessageBox::information(this, "提示", "已连接到服务器") ;
    isTcpConnect = true ;
    r->isTcpConnect = true ;
}

void LoginWindow::tcpDisconnect() {
    qDebug() << "未连接到服务器" ;
    if (!this->isHidden())
        QMessageBox::information(this, "提示", "未连接到服务器\n请打开网络或联系管理员") ;
    isTcpConnect = false ;
    r->isTcpConnect = false ;
}
