#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QPushButton>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    void tcpConnect() ;
    void tcpDisconnect() ;

    void getUserDatas(QString datas) ;
    void initUserDatas() ;

    void haveClicked(int row, int col) ;

    void improveLevel() ;
    void reduceLevel() ;

    void updateLevel() ;
    void deleteUser() ;

    ~MainWindow();

signals:
    void mainWindowClose() ;
    void sendGetUserDatas(QString) ;
    void deleteUserAccount(QString) ;

    void accessUserAccount(QString) ;
    void improveUserAccount(QString) ;
    void reduceUserAccount(QString) ;
    void reduceAdUserAccount(QString) ;
protected:

    void closeEvent(QCloseEvent *event) override ;
private:
    Ui::MainWindow *ui;

    bool isTcpConnect = false ;
    QList<int> oldUserLevel ;
};
#endif // MAINWINDOW_H
