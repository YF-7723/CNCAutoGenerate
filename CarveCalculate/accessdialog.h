#ifndef ACCESSDIALOG_H
#define ACCESSDIALOG_H

#include <QDialog>

namespace Ui {
class AccessDialog;
}

class AccessDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AccessDialog(QWidget *parent = nullptr);
    ~AccessDialog();

private slots:
    void on_pushButton_clicked();

signals:
    void successAccess() ;

private:
    Ui::AccessDialog *ui;
    QString accessNumber ;
};

#endif // ACCESSDIALOG_H
