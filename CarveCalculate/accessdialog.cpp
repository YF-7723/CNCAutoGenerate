#include "accessdialog.h"
#include "ui_accessdialog.h"
#include <QMessageBox>
AccessDialog::AccessDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AccessDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("校验码");
}

AccessDialog::~AccessDialog()
{
    delete ui;
}

void AccessDialog::on_pushButton_clicked()
{
    if (ui->lineEdit->text().isEmpty()) {
        QMessageBox::information(this, "提示","请填写校验码") ;
        return ;
    }
    accessNumber = ui->lineEdit->text() ;
    if (accessNumber == "DF-16A185930") {
        QMessageBox::information(this, "提示", "超级管理员验证成功\n开启本地模式") ;
        emit successAccess() ;
        this->close() ;
    }
    else {
        QMessageBox::information(this, "提示", "校验出错，请检查网络连接") ;
    }
}

