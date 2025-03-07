#ifndef PARAMETERWIDGET_H
#define PARAMETERWIDGET_H

#include <QWidget>
#include <QMessageBox>
#include <QDir>
#include <QFile>
#include <QTableWidget>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QCloseEvent>
#include <QCryptographicHash>
namespace Ui {
class ParameterWidget;
}

class ParameterWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ParameterWidget(QWidget *parent = nullptr);
    ~ParameterWidget();

    void initAllTable() ;
    void changeWindowSize(int index) ;
    void isChange() ;

    void initAllLists() ;
    void initXianLists() ;
    void initDaoLists() ;
    void initLianLists() ;
    void initHoleLists() ;

    void setCellEditable(QTableWidget* &table, int row, int col, QList<QList<QVariant>> &lists) ;
    void setCellReadOnly(QTableWidget* &table, int row, int col, QList<QList<QVariant>> &lists) ;

    void fillTableWidget(QTableWidget* &table, const QList<QList<QVariant>> &data) ;

    QList<QList<QVariant>> readTableWidget(QTableWidget* &table, QList<QList<QVariant>> &lists) ;

    QJsonArray listToJsonArray(const QList<QList<QVariant>> &list) ;
    QList<QList<QVariant>> jsonArrayToList(const QJsonArray &jsonArray) ;
    void writeDataToJsonFile() ;
    void readDataFromJsonFile(QString data) ;

    virtual void closeEvent(QCloseEvent *event) override {
        event->ignore();
    }

    QList<QList <QVariant>> xianLists ;
    QList<QList <QVariant>> daoLists ;
    QList<QList <QVariant>> lianLists ;
    QList<QList <QVariant>> holeLists ;

    void tcpDisconnect() ;

    void setTableWidgetReadOnly(QTableWidget* &table) ;
    void setTableWidgetEditable(QTableWidget* &table, QList<QList<QVariant>> &lists) ;
signals:
    //void haveSaved() ;
    void haveClosed() ;
    void sendListsGet(QString) ;
    void parameterWidgetClose() ;
    void sendWrite(QByteArray, int) ;
public slots:
    //void getSignals() ;
    void reInitTable() ;
private:
    Ui::ParameterWidget *ui;

    QList<QList <QVariant>> xianLists2 ;
    QList<QList <QVariant>> daoLists2 ;
    QList<QList <QVariant>> lianLists2 ;
    QList<QList <QVariant>> holeLists2 ;

    QList<QList <QVariant>> xianLists3 ;
    QList<QList <QVariant>> daoLists3 ;
    QList<QList <QVariant>> lianLists3 ;
    QList<QList <QVariant>> holeLists3 ;

    QList<QList <QVariant>> xianListsTemp ;
    QList<QList <QVariant>> daoListsTemp ;
    QList<QList <QVariant>> lianListsTemp ;
    QList<QList <QVariant>> holeListsTemp ;

    //QString filePath = "";
    bool isChangedAnything = false ;

protected:

private slots:

    //void on_pushButton_clicked();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
};

#endif // PARAMETERWIDGET_H
