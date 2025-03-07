#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>
LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("高级权限") ;
    ui->lineEdit->setEchoMode(QLineEdit::Password) ;
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_pushButton_clicked()
{
    if (!ui->lineEdit->text().isEmpty()) {
        if (ui->lineEdit->text() == "DF-16A" || ui->lineEdit->text() == "185930") {
            QMessageBox::information(this, "提示", "登入成功!") ;
            emit successLogin() ;
            this->close() ;
        } else {
            QMessageBox::information(this, "提示", "密码错误") ;
        }
    } else {
        QMessageBox::information(this, "提示", "请填写权限码") ;
    }
}

