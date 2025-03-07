#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include "parameterwidget.h"
//#include "datawidget.h"
#include <QList>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QPainter>
#include <QAxObject>		// .pro需要添加： QT += axcontainer
#include <QTextStream>
#include <QCoreApplication>
#include <QDir>
#include <algorithm>
#include <QVariant>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct angles {
    QString holeType ;
    QString angleA ;
    QString angleB ;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QString totalString ;

    void initInfor(const QString& txtName, const QString& diameter, const QString& txtCount ) ;
    void initOutput() ;
    void stageOne() ;
    void saveToTxt() ;
    //bool compare(const angles &infoA,const angles &infoB) ;
    void initModel() ;
    void openExcel(const QString &excelPath) ;
    void initRestart() ;
    QString getDouble(double reDouble) ;
    QString dmsToDeg(QString dms) ;
    QVariant readAllData(QAxObject* &sheet) ;
    void dataToList(QVariant &excelData, QList<QList<QVariant>> &myDatas) ;
    void clearData() ;

    void initButton() ;
    void initConnect() ;

    void tcpConnect() ;
    void tcpDisconnect() ;

    void initHoleLianLists() ;


    void setHoleLianLists(QString datas) ;
    ParameterWidget *p ;
public slots:
    void initParameter() ;

signals:
    void startSignals() ;
    void reLogin() ;
    void sendHoleLianLists(QString) ;
    void closeSocket() ;

protected:
    void dragEnterEvent(QDragEnterEvent *ev) override;
    void dropEvent(QDropEvent *ev) override;

    void closeEvent(QCloseEvent *event) override {
        // 在这里执行你的操作
        qDebug() << "MainWindow is about to close.";
        emit closeSocket() ;
        // 如果你想阻止窗口关闭，取消事件
        // event->ignore();

        // 如果你想让窗口关闭，接受事件
        QMainWindow::closeEvent(event);
    }


private slots:


    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void saveData() ;



    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;

    QList<QComboBox *> holeTypes ;
    QList<angles> myAngles ;
    //QList<int> preBallDiameter ;
    //QList<int> preHoleType ;
    QAxObject*      m_pExcel;
    QAxObject*      m_pWorksheets;
    QAxObject*      m_pWorkbook;
    QString         m_strPath;
    QAxObject excel;
    QAxObject excelT ;
    QString excelPath ;
    QVariant excelData ;
    QList<QList<QVariant>> myDatas ;

    QList<QList<QVariant>> xianLists;
    QList<QList<QVariant>> daoLists;
    QList<QList<QVariant>> lianLists;
    QList<QList<QVariant>> holeLists;

    QList<QList<QVariant>> xianListsLocal;
    QList<QList<QVariant>> daoListsLocal;
    QList<QList<QVariant>> lianListsLocal;
    QList<QList<QVariant>> holeListsLocal;
    bool setTips ;
    bool fileTips ;
    int holeNum ;
    double millingDepth ;
    int sphericalRadius ;

    //QString superF ;

    QMap<QString, QString> angleA ;
    QMap<QString, QString> angleB ;
    QStringList holeTypeList ;

    QString txtTitle ;
    QString dia ;
    QString txtNumber ;
    QStringList fileTypes ;
    QString model_1 ;
    QString model_2 ;
    QString model_3 ;
    QString model_4 ;
    QString model_5 ;
    QString model_6 ;
    QString model_7 ;
    QString model_8 ;
    QString model_9 ;
    QString model_10 ;
    QString model_11 ;
    QString model_12 ;
    QString model_13 ;

    QMap<QString, int> drillTypes ;
    QMap<QString, int> screwTypes ;
    QMap<QString, int> holeX ;
    QMap<QString, int> superF ;
    QMap<QString, double> drillDepth ;
    QMap<QString, double> drillDepth2 ;
    QMap<QString, double> screwDepth ;
    QMap<QString, QString> drillP ;
    QMap<QString, QString> screwP ;
    QMap<int, double> drillS ;
    QMap<int, double> drillF ;
    QMap<int, double> drillF2 ;
    QMap<int, double> screwS ;
    QMap<int, double> screwF ;
    QMap<QString, double> RS ;

    QString millingCutterD ;
    int millingCutterN ;
    QMap<QString, QString> millingCutterS ;
    QMap<int, double> startNumbers ;
    QMap<int, double> endNumbers ;
    int millingCutterF ;
    QString millingCutterP ;
    QString chamferCutterP ;
    int chamferCutterN ;
    int chamferCutterS ;
    int chamferCutterF ;
    double LianDongJvLi_Big150 ;
    double LianDongJvLi_Small150 ;
    int y_Big150 ;
    int y_Small150 ;
    int sum = 0;
    QString path ;

    bool isTcpConnect = false ;

};
#endif // MAINWINDOW_H
