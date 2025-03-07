#include "registerwindow.h"
#include "ui_registerwindow.h"
#include <QMessageBox>

RegisterWindow::RegisterWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegisterWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("注册");
    ui->lineEdit_2->setEchoMode(QLineEdit::Password);
    ui->lineEdit_3->setEchoMode(QLineEdit::Password);

}

RegisterWindow::~RegisterWindow()
{
    delete ui;
}

void RegisterWindow::on_pushButton_clicked()
{
    if (ui->lineEdit->text().isEmpty() || ui->lineEdit_2->text().isEmpty() ||
        ui->lineEdit_3->text().isEmpty() || ui->lineEdit_7->text().isEmpty() ) {
        QMessageBox::information(this, "提示", "请填写完整信息") ;
        return ;
    }

    if (ui->lineEdit_2->text() != ui->lineEdit_3->text()) {
        QMessageBox::information(this, "提示", "输入密码请保持一致") ;
        return ;
    }

    account = ui->lineEdit->text() ;
    password = ui->lineEdit_2->text() ;
    passNum = ui->lineEdit_7->text() ;

    QString messages = "accountnew2 " + account + " " + password + " " + passNum ;

    if (this->isTcpConnect == false) {
        QMessageBox::information(this, "提示", "注册信息已缓存，请检查网络连接，无法上传服务器") ;
        return ;
    }else {
        emit sendNewAccount(messages) ;
    }
}

void RegisterWindow::getReplyNew(QString messages) {
    if (messages == "account repeat") {
        QMessageBox::information(this, "提示", "该账户已注册") ;
    }
    if (messages == "register success!") {
        QMessageBox::information(this, "提示", "注册成功！") ;
        this->hide();
    }
    if (messages == "not correct passnum") {
        QMessageBox::information(this, "提示", "校验码错误") ;
    }

}


void RegisterWindow::on_pushButton_2_clicked()
{
    if (ui->pushButton_2->text() == "显示密码") {
        ui->pushButton_2->setText("隐藏密码");
        ui->lineEdit_2->setEchoMode(QLineEdit::Normal);
        ui->lineEdit_3->setEchoMode(QLineEdit::Normal);
        return ;
    }
    if (ui->pushButton_2->text() == "隐藏密码") {
        ui->pushButton_2->setText("显示密码");
        ui->lineEdit_2->setEchoMode(QLineEdit::Password);
        ui->lineEdit_3->setEchoMode(QLineEdit::Password);
        return ;
    }
}

