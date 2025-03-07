#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <QTableWidget>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("螺栓球管理系统");

    //connect(ui->tableWidget, &QTableWidget::cellDoubleClicked, this, &MainWindow::haveClicked) ;

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::haveClicked(int row, int col) {
    qDebug() << "row" << row << "col" << col;
    int result ;
    if (col == 4) {
        result = QMessageBox::information(this, "提示", "是否关闭权限授权", "是", "否", 0, 1) ;
        qDebug() << result ;
        if (result == 0) {
            QMessageBox::information(this, "提示", "授权已关闭") ;
             ui->tableWidget->item(row, col)->setText("无授权");
            emit deleteUserAccount("deleteuseraccount " + ui->tableWidget->item(row, col - 4)->text()) ;
        }

    }
    if (col == 3) {
        result = QMessageBox::information(this, "提示", "提升或降低权限等级", "提升", "降低", 0, 1) ;
        if (result == 0) {
             QMessageBox::information(this, "提示", "权限提升成功") ;
             ui->tableWidget->item(row, col)->setText("2");
        }
        if (result == 1) {
             QMessageBox::information(this, "提示", "权限已降低") ;
             ui->tableWidget->item(row, col)->setText("1");
        }
    }
}

void MainWindow::tcpConnect() {
    qDebug() << "MainWindow: connect to tcp" ;
    if (isTcpConnect == false && !this->isHidden())
        QMessageBox::information(this, "提示", "已连接到服务器") ;
    isTcpConnect = true ;
}

void MainWindow::tcpDisconnect() {
    qDebug() << "MainWindow: cannot connect to tcp" ;
    if (!this->isHidden()){
        QMessageBox::information(this, "提示", "未连接到服务器\n请打开网络或联系管理员") ;
        this->hide();
        //emit reLogin() ;
    }
    isTcpConnect = false ;
}

void MainWindow::closeEvent(QCloseEvent *event) {
    this->hide();
    event->ignore();
    emit mainWindowClose();
}

void MainWindow::getUserDatas(QString datas) {
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setShowGrid(false);
    ui->tableWidget->setWindowFlags(Qt::FramelessWindowHint) ;
    if (datas.isEmpty()) {
        qDebug() << "userdata empty" ;
        QMessageBox::information(this, "提示", "未检测到用户信息") ;
        return ;
    }
    QStringList msg = datas.split("|") ;
    ui->tableWidget->setRowCount(msg.size() - 1);
    QStringList curUser = msg[0].split("~") ;
    ui->tableWidget->setColumnCount(curUser.size() + 1);

    int row = 0 ;
    for (auto &i:msg) {
        if (i.isEmpty()) {
             continue ;
        }
        ui->tableWidget->setRowHeight(row, 50);
        curUser = i.split("~") ;
        int col = 0 ;
        qDebug() << "curuser count " << curUser.size() << curUser;
        for (;col <= 4; col ++) {
            if (col == 3) {
                if (curUser[col] == "0") {
                    ui->tableWidget->setItem(row, col, new QTableWidgetItem("未审核(已关闭)"));
                    oldUserLevel.push_back(0);
                }
                if (curUser[col] == "1") {
                    ui->tableWidget->setItem(row, col, new QTableWidgetItem("初级用户"));
                    oldUserLevel.push_back(1);
                }
                if (curUser[col] == "2") {
                    oldUserLevel.push_back(2);
                    ui->tableWidget->setItem(row, col, new QTableWidgetItem("高级用户"));
                }
            }
            else {
                ui->tableWidget->setItem(row, col, new QTableWidgetItem(curUser[col]));
            }
            QTableWidgetItem *item = ui->tableWidget->item(row, col) ;
            if (item)
                item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        }
        for (;col <= 6; col ++) {
            if (col == 5) {
                //qDebug() << "here" ;
                QString str = "提升权限" ;
                QString str2 = "降低权限" ;
                QPushButton *btnImprove = new QPushButton() ;
                QPushButton *btnReduce = new QPushButton() ;

                btnImprove->setText(str);
                btnReduce->setText(str2);

                btnImprove->setFixedSize(50, 40);
                btnReduce->setFixedSize(50, 40);

                btnImprove->setStyleSheet("QPushButton{color:white;background-color:rgb(51,204,255);font-family:黑体;border-radius: 15px;}"
                                        "QPushButton:pressed{background-color:rgb(51,129,172)}");
                btnReduce->setStyleSheet("QPushButton{color:white;background-color:rgb(51,204,255);font-family:黑体;border-radius: 15px;}"
                                        "QPushButton:pressed{background-color:rgb(51,129,172)}");

                connect(btnImprove, &QPushButton::clicked, this, &MainWindow::improveLevel) ;
                connect(btnReduce, &QPushButton::clicked, this, &MainWindow::reduceLevel) ;

                QHBoxLayout *vLayout = new QHBoxLayout();
                QWidget *Widget_btn = new QWidget;
                vLayout->addWidget(btnImprove);
                vLayout->addSpacing(10);
                vLayout->addWidget(btnReduce);
                Widget_btn->setLayout(vLayout);
                Widget_btn->setStyleSheet("QWidget{ border: 0px }");
                ui->tableWidget->setCellWidget(row, col, Widget_btn);

                //qDebug() << "here over" ;
            }
            if (col == 6) {
                //qDebug() << "here" ;
                QString str = "确认修改" ;
                QString str2 = "删除用户" ;
                QPushButton *btnImprove = new QPushButton() ;
                QPushButton *btnReduce = new QPushButton() ;

                btnImprove->setText(str);
                btnReduce->setText(str2);

                btnImprove->setFixedSize(50, 40);
                btnReduce->setFixedSize(50, 40);

                btnImprove->setStyleSheet("QPushButton{color:white;background-color:rgb(51,204,255);font-family:黑体;border-radius: 15px;}"
                                          "QPushButton:pressed{background-color:rgb(51,129,172)}");
                btnReduce->setStyleSheet("QPushButton{color:white;background-color:rgb(51,204,255);font-family:黑体;border-radius: 15px;}"
                                         "QPushButton:pressed{background-color:rgb(51,129,172)}");

                connect(btnImprove, &QPushButton::clicked, this, &MainWindow::updateLevel) ;
                connect(btnReduce, &QPushButton::clicked, this, &MainWindow::deleteUser) ;

                QHBoxLayout *vLayout = new QHBoxLayout();
                QWidget *Widget_btn = new QWidget;
                vLayout->addWidget(btnImprove);
                vLayout->addSpacing(10);
                vLayout->addWidget(btnReduce);
                Widget_btn->setLayout(vLayout);
                Widget_btn->setStyleSheet("QWidget{ border: 0px }");
                ui->tableWidget->setCellWidget(row, col, Widget_btn);

            }
        }
        row++ ;
    }
}

void MainWindow::improveLevel() {
    qDebug() << "improve" ;

    QPushButton *pushButtonTemp = dynamic_cast<QPushButton*>(this->sender());
    if(NULL == pushButtonTemp)
    {
        return;
    }


    QModelIndex index = ui->tableWidget->indexAt
                        (ui->tableWidget->mapFromGlobal(pushButtonTemp->mapToGlobal(QPoint(0, 0))));

    int row = index.row() ;
    int col = index.column() ;

    //qDebug() << row << col ;

    QString nowLevel = ui->tableWidget->item(row, 3)->text() ;

    if (nowLevel == "未审核(已关闭)") {

        ui->tableWidget->item(row, 3)->setText("初级用户");
    }
    if (nowLevel == "初级用户") {
        if (oldUserLevel[row] == 1 || oldUserLevel[row] == 2)
            ui->tableWidget->item(row, 3)->setText("高级用户");
        else {
            QMessageBox::information(this, "提示", "每次修改仅可提升一级权限") ;
        }
    }

}

void MainWindow::reduceLevel() {
    qDebug() << "reduce" ;

    QPushButton *pushButtonTemp = dynamic_cast<QPushButton*>(this->sender());
    if(NULL == pushButtonTemp)
    {
        return;
    }


    QModelIndex index = ui->tableWidget->indexAt
                        (ui->tableWidget->mapFromGlobal(pushButtonTemp->mapToGlobal(QPoint(0, 0))));

    int row = index.row() ;
    int col = index.column() ;

    //qDebug() << row << col ;

    QString nowLevel = ui->tableWidget->item(row, 3)->text() ;

    if (nowLevel == "高级用户") {
        ui->tableWidget->item(row, 3)->setText("初级用户");
    }
    if (nowLevel == "初级用户") {
        if (oldUserLevel[row] == 1 || oldUserLevel[row] == 0)
            ui->tableWidget->item(row, 3)->setText("未审核(已关闭)");
        else {
            QMessageBox::information(this, "提示", "每次修改仅可降低一级权限") ;
        }
    }

}

void MainWindow::deleteUser() {
    qDebug() << "delete user" ;

    QPushButton *pushButtonTemp = dynamic_cast<QPushButton*>(this->sender());
    if(NULL == pushButtonTemp)
    {
        return;
    }


    QModelIndex index = ui->tableWidget->indexAt
                        (ui->tableWidget->mapFromGlobal(pushButtonTemp->mapToGlobal(QPoint(0, 0))));

    int row = index.row() ;
    int col = index.column() ;

    //qDebug() << row << col ;
    oldUserLevel.removeAt(row) ;
    QString nowName = ui->tableWidget->item(row, 0)->text() ;

    auto result = QMessageBox::information(this, "提示", "是否删除用户" + nowName, "是", "否", 0, 1) ;
    //qDebug() << result ;
    if (result == 0) {
        QMessageBox::information(this, "提示", "用户已删除") ;
        //ui->tableWidget->item(row, col)->setText("无授权");
        emit deleteUserAccount("deleteuseraccount " + ui->tableWidget->item(row, 0)->text()) ;
        ui->tableWidget->removeRow(row);
    }

}

void MainWindow::updateLevel() {
    qDebug() << "updatelevel" << oldUserLevel;

    QPushButton *pushButtonTemp = dynamic_cast<QPushButton*>(this->sender());
    if(NULL == pushButtonTemp)
    {
        return;
    }


    QModelIndex index = ui->tableWidget->indexAt
                        (ui->tableWidget->mapFromGlobal(pushButtonTemp->mapToGlobal(QPoint(0, 0))));

    int row = index.row() ;
    int col = index.column() ;

    //qDebug() << row << col ;

    QString nowName = ui->tableWidget->item(row, col - 6)->text() ;
    QString nowLevel = ui->tableWidget->item(row, col - 3)->text() ;
    //qDebug() << nowName ;

    if (nowLevel == "未审核(已关闭)") {
        if (oldUserLevel[row] == 0) {
            QMessageBox::information(this, "提示", "未变更权限级别") ;
            return ;
        }
        if (oldUserLevel[row] == 1) {
            emit reduceUserAccount("reduceaccount " + nowName);
            oldUserLevel[row] = 0 ;
            return ;
        }
    }
    if (nowLevel == "初级用户") {
        if (oldUserLevel[row] == 0) {
            emit accessUserAccount("accessaccount " + nowName);
            oldUserLevel[row] = 1 ;
            return ;
        }
        if (oldUserLevel[row] == 1) {
            QMessageBox::information(this, "提示", "未变更权限级别") ;
            return ;
        }
        if (oldUserLevel[row] == 2) {
            emit reduceAdUserAccount("reduceadaccount " + nowName);
            oldUserLevel[row] = 1 ;
            return ;
        }
    }
    if (nowLevel == "高级用户") {
        if (oldUserLevel[row] == 1) {
            emit improveUserAccount("improveaccount " + nowName);
            oldUserLevel[row] = 2 ;
            return ;
        }
        if (oldUserLevel[row] == 2) {
            QMessageBox::information(this, "提示", "未变更权限级别") ;
            return ;
        }
    }
}

void MainWindow::initUserDatas() {
    emit sendGetUserDatas("userdatas get");
}

