#include "choosewindow.h"
#include "ui_choosewindow.h"
#include <QMessageBox>
ChooseWindow::ChooseWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChooseWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("螺栓球管理系统");
}

ChooseWindow::~ChooseWindow()
{
    delete ui;
}

void ChooseWindow::tcpConnect() {
    qDebug() << "MainWindow: connect to tcp" ;
    if (isTcpConnect == false && !this->isHidden())
        QMessageBox::information(this, "提示", "已连接到服务器") ;
    isTcpConnect = true ;
}

void ChooseWindow::tcpDisconnect() {
    qDebug() << "MainWindow: cannot connect to tcp" ;
    if (!this->isHidden()){
        QMessageBox::information(this, "提示", "未连接到服务器\n请打开网络或联系管理员") ;
        this->hide();
        emit reLogin() ;
    }
    emit failToConnect() ;
    isTcpConnect = false ;
}

void ChooseWindow::on_pushButton_2_clicked()
{
    emit setAd() ;
    this->hide() ;
}


void ChooseWindow::on_pushButton_clicked()
{
    emit setP() ;
    this->hide() ;
}


/*void ChooseWindow::on_pushButton_3_clicked()
{
    emit sendUpdatePassnum("updatepassnum a") ;
}*/

void ChooseWindow::haveUpdatePassnum(QString passnum) {
    QMessageBox::information(this, "提示", "校验码是\n" + passnum) ;
}

