#ifndef CHOOSEWINDOW_H
#define CHOOSEWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
namespace Ui {
class ChooseWindow;
}

class ChooseWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChooseWindow(QWidget *parent = nullptr);
    ~ChooseWindow();

    void tcpConnect() ;
    void tcpDisconnect() ;

    void haveUpdatePassnum(QString) ;
signals:
    void setAd() ;
    void setP() ;
    void chooseWindowClose() ;
    void failToConnect() ;
    void reLogin() ;
    void sendUpdatePassnum(QString) ;
protected:
    void closeEvent(QCloseEvent *event) override {
        emit chooseWindowClose();
        event->accept() ;
    }
private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    //void on_pushButton_3_clicked();

private:
    Ui::ChooseWindow *ui;

    bool isTcpConnect = false ;
};

#endif // CHOOSEWINDOW_H
