#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H

#include <QWidget>

namespace Ui {
class RegisterWindow;
}

class RegisterWindow : public QWidget
{
    Q_OBJECT

public:
    explicit RegisterWindow(QWidget *parent = nullptr);
    ~RegisterWindow();

    void getReplyNew(QString messages) ;
    bool isTcpConnect = false ;
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

signals:
    void sendNewAccount(QString) ;
private:
    Ui::RegisterWindow *ui;

    QString account ;
    QString password ;
    QString name ;
    QString company ;
    QString number ;
    QString passNum ;
};

#endif // REGISTERWINDOW_H
