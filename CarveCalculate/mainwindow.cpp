#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMimeData>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , excel("Excel.Application")
{
    ui->setupUi(this);
    this->setAcceptDrops(true);

    this->setWindowTitle("螺栓球程序生成") ;
   // this->setStyleSheet("QMainWindow {border-radius: 10px;}");
   // ui->pushButton_3->setEnabled(false);
   // ui->pushButton_4->setEnabled(false);

    ui->pushButton_2->setEnabled(false) ;

    fileTips = false ;
    setTips = true ;
    excel.setProperty("Visible", false);// 不显示窗体
    excel.setProperty("DisplayAlerts", false);



    p = new ParameterWidget() ;

    initModel() ;
    initConnect() ;
    //initParameter() ;
    ////qDebug() << 1 ;
    emit startSignals() ; //set test
    ////qDebug() << xianLists ;

}

void MainWindow::initHoleLianLists() {
    emit sendHoleLianLists("parameterget lian") ;
}

void MainWindow::setHoleLianLists(QString datas) {

    qDebug() << "success get list" ;
    QJsonDocument doc = QJsonDocument::fromJson(datas.toUtf8());
    QJsonObject json = doc.object();
    //qDebug() << "json" << json.empty() ;

    lianLists = p->jsonArrayToList(json["lianLists"].toArray());
    holeLists = p->jsonArrayToList(json["holeLists"].toArray());
    xianLists = p->jsonArrayToList(json["xianLists"].toArray());
    daoLists = p->jsonArrayToList(json["daoLists"].toArray());

    millingCutterD = xianLists[1][0].toString() ;
    //millingCutterN = xianLists[1][1].toInt() ;
    millingCutterF = xianLists[1][13].toInt() ;
    millingCutterP = xianLists[1][14].toString() ;

    //chamferCutterN = daoLists[1][0].toInt() ;
    qDebug() << "daoLists" << daoLists ;
    chamferCutterS = daoLists[1][1].toInt() ;
    chamferCutterF = daoLists[1][2].toInt() ;
    chamferCutterP = daoLists[1][3].toString() ;

    LianDongJvLi_Big150 = lianLists[1][1].toDouble() ;
    LianDongJvLi_Small150 = lianLists[0][1].toDouble() ;
    y_Big150 = lianLists[2][1].toInt() ;
    y_Small150 = lianLists[3][1].toInt() ;



    for (int temCol = 2; temCol <= 12; temCol++) {

        millingCutterS.insert(xianLists[0][temCol].toString(), xianLists[1][temCol].toString()) ;

        startNumbers.insert(xianLists[0][temCol].toInt(), xianLists[2][temCol].toDouble()) ;
        endNumbers.insert(xianLists[0][temCol].toInt(), -(xianLists[3][temCol].toDouble())) ;
        //qDebug () << "here" ;

    }


    for (int row = 0; row < 16; row++) {

        //drillTypes.insert(holeLists[row][0].toString(), holeLists[row][1].toInt()) ;//空类型  钻头号

        holeX.insert(holeLists[row][0].toString(), holeLists[row][8].toString().toInt()) ;//空类型  钻头号

        superF.insert(holeLists[row][0].toString(), holeLists[row][9].toInt()) ;//空类型  钻头号

        //drillS.insert(holeListsLocal[row][1].toInt(), holeLists[row][2].toDouble()) ;

        //drillF.insert(holeListsLocal[row][1].toInt(), holeLists[row][3].toDouble()) ;

        //drillF2.insert(holeListsLocal[row][1].toInt(), holeLists[row][5].toDouble()) ;

        //drillP.insert(holeListsLocal[row][1].toString(), holeLists[row][7].toString()) ;

        //screwTypes.insert(holeLists[row][0].toString(), holeLists[row][10].toInt()) ;

        //screwS.insert(holeListsLocal[row][2].toInt(), holeLists[row][11].toDouble()) ;

        //screwF.insert(holeListsLocal[row][2].toInt(), holeLists[row][12].toDouble()) ;

        //screwP.insert(holeListsLocal[row][2].toString(), holeLists[row][14].toString()) ;

        drillDepth.insert(holeLists[row][0].toString(), holeLists[row][4].toDouble()) ;

        drillDepth2.insert(holeLists[row][0].toString(), holeLists[row][6].toDouble()) ;

        screwDepth.insert(holeLists[row][0].toString(), holeLists[row][13].toDouble()) ;

        RS.insert(holeLists[row][0].toString(), holeLists[row][15].toDouble()) ;

    }
    QList<QString> holeTypesTemp ;
    for (int row = 0; row < 16; row++) {
        holeTypesTemp.append(holeLists[row][0].toString());
    }
    qDebug () << "success get list all" ;
    p->replaceHoleType(holeTypesTemp);
    initParameter() ;
}

void MainWindow::initParameter() {

    ////qDebug() << 2 ;
    xianListsLocal = p->xianLists ;
    daoListsLocal = p->daoLists ;
    holeListsLocal = p->holeLists ;

    millingCutterN = xianListsLocal[1][0].toInt() ;
    chamferCutterN = daoListsLocal[1][0].toInt() ;

    for (int row = 0; row < 16; row++) {
        drillTypes.insert(holeLists[row][0].toString(), holeListsLocal[row][1].toInt()) ;//空类型  钻头号
        screwTypes.insert(holeLists[row][0].toString(), holeListsLocal[row][2].toInt()) ;
    }


    for (int row = 0; row < 16; row++) {

        //drillTypes.insert(holeLists[row][0].toString(), holeLists[row][1].toInt()) ;//空类型  钻头号

        //holeX.insert(holeLists[row][0].toString(), holeLists[row][8].toString().toInt()) ;//空类型  钻头号

        //superF.insert(holeLists[row][0].toString(), holeLists[row][9].toInt()) ;//空类型  钻头号

        drillS.insert(holeListsLocal[row][1].toInt(), holeLists[row][2].toDouble()) ;

        drillF.insert(holeListsLocal[row][1].toInt(), holeLists[row][3].toDouble()) ;

        drillF2.insert(holeListsLocal[row][1].toInt(), holeLists[row][5].toDouble()) ;

        drillP.insert(holeListsLocal[row][1].toString(), holeLists[row][7].toString()) ;

        //screwTypes.insert(holeLists[row][0].toString(), holeLists[row][10].toInt()) ;

        screwS.insert(holeListsLocal[row][2].toInt(), holeLists[row][11].toDouble()) ;

        screwF.insert(holeListsLocal[row][2].toInt(), holeLists[row][12].toDouble()) ;

        screwP.insert(holeListsLocal[row][2].toString(), holeLists[row][14].toString()) ;

        //drillDepth.insert(holeLists[row][0].toString(), holeLists[row][4].toDouble()) ;

        //drillDepth2.insert(holeLists[row][0].toString(), holeLists[row][6].toDouble()) ;

        //screwDepth.insert(holeLists[row][0].toString(), holeLists[row][13].toDouble()) ;

       // RS.insert(holeLists[row][0].toString(), holeLists[row][15].toDouble()) ;

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
        emit reLogin() ;
    }
    isTcpConnect = false ;
}

void MainWindow::dragEnterEvent(QDragEnterEvent *ev) {
    if(ev->mimeData()->hasUrls())
    {
        ev->accept();//接收拖动进入事件
    }
}

void MainWindow::dropEvent(QDropEvent *ev) {
    if(ev->mimeData()->hasUrls())
    {
        QList<QUrl> urls = ev->mimeData()->urls();

        //单个文件路径
        QString fileName = urls.at(urls.size()-1).toLocalFile();
        ////qDebug()<<fileName;

        //多个文件路径
        for(int i=0; i<urls.size(); i++)
        {
            //qDebug()<<urls.at(i).toLocalFile();
        }

        if (urls.size() > 1) {
            QMessageBox::information(this, "提示", "检测到读取多个文件，以最后文件为准") ;
        }

        if (fileName.contains(".xls", Qt::CaseInsensitive) == true) {
            //qDebug() << "this is excel" ;
            excelPath = fileName ;
            fileTips = true ;
            QMessageBox::information(this, "提示", "已读取到文件\n(默认读取最后拖入文件)\n" + fileName) ;
        } else {
            //qDebug() << "oops! not excel" ;
            QMessageBox::information(this, "提示", "不正确的文件格式") ;
        }
    }
}

void MainWindow::initConnect() {
    QObject::connect(p, &ParameterWidget::haveSaved, this, &MainWindow::initParameter) ;
    QObject::connect(this, &MainWindow::startSignals, p, &ParameterWidget::getSignals) ;
    QObject::connect(p, &ParameterWidget::haveClosed, this, &MainWindow::initButton) ;
}

MainWindow::~MainWindow()
{
    //p->close() ;
    delete p ;
    delete ui;

    //delete excel ;
}
void MainWindow::initButton() {

    ui->pushButton->setEnabled(true) ;
    ui->pushButton_3->setEnabled(true) ;
    ui->pushButton_4->setEnabled(true) ;
    //ui->pushButton_2->setEnabled(true);

}


void MainWindow::initInfor(const QString& txtName, const QString& diameter, const QString& txtCount ) {
    txtTitle = txtName ;
    txtNumber = txtCount ;
    dia = diameter ;
    dia.remove(0, 1) ;
    sphericalRadius = dia.toInt()/2 ;
}



void MainWindow::openExcel(const QString &excelPath) {

   // //qDebug() << 1 ;
    bool isMingGuangZhiYe = true ;
    QAxObject* workbooks = excel.querySubObject("WorkBooks");
    QAxObject* workbook = workbooks->querySubObject("Open(const QString&)", (excelPath));

    QAxObject* worksheet = workbook->querySubObject("WorkSheets(int)", 1);
    QAxObject* worksheet2 = workbook->querySubObject("WorkSheets(int)", 2);
    //QAxObject* usedrange = worksheet->querySubObject("UsedRange"); // sheet范围
    //qDebug() << "name2" << worksheet2->dynamicCall("Name").toString() ;
    if (worksheet2->dynamicCall("Name").toString() == "加工表") {
        isMingGuangZhiYe = false ;
        worksheet = worksheet2 ;
    }
    //qDebug() << "name" << worksheet->dynamicCall("Name").toString() ;
    //int intRowStart = usedrange->property("Row").toInt(); // 起始行数   为1
    //int intColStart = usedrange->property("Column").toInt();  // 起始列数 为1

    excelData = readAllData(worksheet) ;
    //qDebug() << 0 ;
    dataToList(excelData, myDatas) ;
    //qDebug() << 1 ;



    int intRow = myDatas.size(); // 行数
    //qDebug() << "col" << intCol ;
    int excelCount = (intRow + 1)/7 ;
    //QStringList title ;
    //title << "A" << "B" << "C" << "D" << "E" << "F" << "G" << "H" << "I" << "J" << "K" << "L" << "M" << "N" << "O";

    QString txtName ;
    QString diameter ;
    QString txtCount ;
    QString depth ;
    //qDebug() << myDatas[0].size() ;
    for (int i = 1; i <= excelCount; i++) {

        for (int row = 0; row < 6; row++) {
            for (int col = 0; col < myDatas[0].size(); col ++) {

                int nowRow = row + (i - 1) * 7 ;

                //QAxObject* cellX = worksheet->querySubObject("Range(QVariant, QVariant)", X);
                //获取单元格
                QString cellTxt = myDatas[nowRow][col].toString() ;

                if (row == 1 && isMingGuangZhiYe == true) {
                    if (col == 0)
                        txtName =  cellTxt;
                    if (col == 1)
                        diameter = cellTxt ;
                    if (col == 3)
                        txtCount = cellTxt ;
                    if (col == 4)
                        depth = cellTxt ;
                    //qDebug() <<" "<<diameter ;
                }

                if (row == 1 && isMingGuangZhiYe == false) {
                    if (col == 0)
                        txtName =  cellTxt;
                    if (col == 1)
                        diameter = cellTxt ;
                    if (col == 2)
                        txtCount = cellTxt ;
                    if (col == 3)
                        depth = cellTxt ;
                    //qDebug() <<" "<<diameter ;
                }

                if (row == 3 && !cellTxt.isEmpty()) {
                    if (cellTxt == "/" || cellTxt == "S20") {
                        sum++ ;
                        //qDebug() <<  "check M20" << " " << sum << " " << cellTxt;
                        cellTxt = "M20" ;
                        //qDebug() << "check if true" << cellTxt ;
                    }
                    holeTypeList << cellTxt ; // "/" == M20
                    //qDebug() << holeTypeList[holeTypeList.count() - 1] ;
                }


                if (row == 4 && !cellTxt.isEmpty()) {
                    ////qDebug() << dmsToDeg(cellTxt) ;
                    angles firstangle ;

                    QString tempHoletype = myDatas[nowRow - 1][col].toString() ;
                    if (tempHoletype == "/" || tempHoletype == "S20") {
                        tempHoletype = "M20" ;
                    }
                    QString tempAngleA = myDatas[nowRow + 1][col].toString() ;

                    firstangle.angleB = dmsToDeg(cellTxt) ;
                    firstangle.angleA = dmsToDeg(tempAngleA) ;
                    firstangle.holeType = tempHoletype ;

                    angleB.insert(tempHoletype, dmsToDeg(cellTxt)) ;
                    myAngles << firstangle ;
                }

                if (row == 5 && !cellTxt.isEmpty()) {
                    QString tempHoletype = myDatas[nowRow - 2][col].toString() ;
                    angleA.insert(tempHoletype,dmsToDeg(cellTxt)) ;
                }
            }
        }
        //qDebug() << "success aaaaaa" ;
        holeNum = holeTypeList.count() ;
        if (isMingGuangZhiYe == true) {
            millingDepth = depth.remove(0, 3).toDouble() ;
        }
        if (isMingGuangZhiYe == false) {
            QString tempDepth = "";
            for (int item = depth.length() - 1; item >= 0; item --) {
                //qDebug() << (int)depth[item].toLatin1() ;
                if (depth[item] == '.' || ((int)depth[item].toLatin1() >= 48 && (int)depth[item].toLatin1()<= 57)) {
                    tempDepth.push_front(depth[item]) ;
                    //qDebug() << "success in" << depth[item];
                }
            }
            //qDebug() << "tempDepth" << tempDepth ;
            millingDepth = tempDepth.toDouble() ;
            txtCount =  txtCount.removeLast() ;
        }

        //qDebug() <<"millingDepth"<< millingDepth ;
        //qDebug() << "txtname" << txtName ;

        initInfor(txtName, diameter, txtCount) ;
        initOutput() ;
        saveToTxt() ;

        clearData() ;

    }
    workbook->dynamicCall("Close (Boolean)", false);
    initRestart() ;
    QMessageBox::information(this, "提示", "输出已经完成" );
    //this->close() ;
}

void MainWindow::clearData() {
    angleA.clear() ;
    angleB.clear() ;
    holeTypeList.clear() ;
    myAngles.clear() ;
    totalString.clear() ;
}

void MainWindow::initRestart() {
    //qDebug() << "Restart" ;
    ui->pushButton_2->setEnabled(false) ;
}

QString MainWindow::dmsToDeg(QString dmsStr)
{
    // 将度分秒字符串按照空格分割，得到度、分、秒三个部分
    QString ddmsStr = "";
    for (int i = 0; i < dmsStr.length(); i++) {
        if (dmsStr[i] != ' ') {
            ddmsStr.append(dmsStr[i]) ;
        }
    }
    QStringList dmsList = ddmsStr.split("°");
    // 将度、分、秒转换为 double 类型
    double deg = dmsList[0].toDouble();
    //qDebug() << "the last number" << dmsList[1] ;
    if (!dmsList[1].isEmpty() && dmsList[1][dmsList[1].length() - 1] == '\'') {
        dmsList[1].removeLast();
        qDebug() << "the last number" << dmsList[1] ;
    }
    double min = dmsList[1].toDouble();
    double result = 0;
    // 将度、分、秒转换为度的小数形式
    if (ddmsStr[0] == '-') {
        result = -(0 - deg + (min/60)) ;
    }
    else {
        result = deg + (min / 60) ;
    }


    return QString::number(result);
}

void MainWindow::initModel() {

    model_1 = "%\n"
            "O1234;\n"
            "M44;\n"
            "G90 G80 G40 G49;\n"
            "G53 G90 G00 X0;\n"
            "G53 G90 G00 Z0;\n"
            "N1;\n"
            "T# M06;\n"
            "M#;\n"
            "T#;\n"
            "M03 S900;\n" ;

    model_2 ="M11;\n"
            "G54 G90 G00 X# A# B#;\n"
            "G43 Z# H01 M10;\n"
            "M120;\n"
            "G01 Z# F5000;\n"
            "X# F600;\n"
            "Z# F5000;\n"
            "M121;\n";

    model_3 = "M05;\n"
            "G53 G90 G00 X0;\n"
            "G53 G90 G00 Z0 M11;\n" ;

    model_4 =  "N#;\n"
            "T# M06;\n"
            "M#;\n"
            "T#;\n"
            "M03 S#;\n"
            "M08;\n"
            "G54 G90 G00 X0;\n"
            "G53 Z#;\n"
            "G53 Y2;\n"
            "G43 H#;\n"
            "M152;\n" ;

    model_5 = "M11;\n"
            "G54 G90 G00 A# B#;\n"
            "M10;\n"
            "M156 X1 F20;\n"
            "#5542=-#511+#300X+#5543+#510;\n"
            "G54 G90 G01 Z# F5000;\n"
            "Z# F#;\n"
            "Y# F#;\n"
            "M159;\n"
            "G01 Z# F5000;\n"
            "M157;\n"
            "G04 X0.1;\n"
            "G91 G01 Y15 F2000;\n";

    model_6 = "M09;\n"
            "M05;\n"
            "M153;\n"
            "G53 G90 G00 Y0 Z0 M11;\n" ;

    model_7 = "N#;\n"
            "T# M06;\n"
            "M#;\n"
            "T#;\n"
            "M03 S200;\n"
            "M08;\n"
            "M11;\n"
            "G54 G90 G00 X0 A# B#;\n"
            "G43 Z# H#;\n"
            "G98 G81 A# B# Z# R# F100;\n" ;

    model_8 = "G98 G81 A# B# Z# R# F100;\n" ;

    model_9 = "G80;\n"
            "M09;\n"
            "M05;\n"
            "G53 G90 G00 Z0 M11;\n" ;

    model_10 = "N#;\n"
            "T# M06;\n"
            "M#;\n"
            "T#;\n"
            "M08;\n" ;

    model_11 = "M11;\n"
            "G54 G90 G00 X0 A# B#;\n"
            "M10;\n"
            "G43 Z# H#;\n"
            "M29 S#;\n"
            "G98 G84 Z# R# F# RS#;\n"
            "G80;\n" ;

    model_12 = "M09;\n"
            "M05;\n"
            "G53 G90 G00 Z0 M11;\n" ;

    model_13 = "M09;\n"
            "M05;\n"
            "G53 G90 G00 Z0 X0 M11;\n"
            "G53 G90 G00 A90;\n"
            "M10;\n"
            "M30;\n"
            "%\n" ;
    //qDebug() << model_1 ;
}


void MainWindow::saveData() {
    //qDebug() << "success" ;
    //d.close() ;

}

QVariant MainWindow::readAllData(QAxObject* &sheet) {
    QVariant var;
    if (sheet != NULL && ! sheet->isNull())
    {
        QAxObject *usedRange = sheet->querySubObject("UsedRange");
        if(NULL == usedRange || usedRange->isNull())
        {
            return var;
        }
        var = usedRange->dynamicCall("Value");
        delete usedRange;
    }
    return var;
}

void MainWindow::dataToList(QVariant &excelData2, QList<QList<QVariant>> &myDatas2) {

    QVariantList varRows = excelData2.toList();
    if(varRows.isEmpty())
    {
        return;
    }
    const int rowCount = varRows.size();
    QVariantList rowData;
    for(int i=0;i<rowCount;++i)
    {
        rowData = varRows[i].toList();
        myDatas2.push_back(rowData);
    }

}

void MainWindow::on_pushButton_clicked()
{
    ui->pushButton->setEnabled(false) ;
    ui->pushButton_3->setEnabled(false) ;
    ui->pushButton_4->setEnabled(false) ;
    ui->pushButton_4->setEnabled(false);
    //initConnect() ;
    p->show() ;
    //emit startSignals() ;
    //qDebug() << "1" ;
}

void MainWindow::on_pushButton_3_clicked()
{
    excelPath = QFileDialog::getOpenFileName(this, "open", "../", "*.xlsx *.xls") ;
    if (excelPath.isEmpty()) {
        QMessageBox::information(this, "警告", "未选择任何文件") ;
        return ;
    }
    fileTips = true ;
}

void MainWindow::saveToTxt() {
   // QString savePath = QCoreApplication::applicationDirPath();
    if (fileTypes.contains(dia)) {
        QString fileType = dia ;
        QString paddedNum = txtTitle.mid(1).rightJustified(4, '0');
        QFile file(path+"/" + fileType + "/O" + paddedNum/*+ "0" + QString::number(curNum)*/ + ".PRG");

        // 打开文件，以便将数据写入文件中
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            //qDebug() << 1 ;
            QTextStream out(&file);
            out << totalString;
            file.close();
        }
        totalString.clear() ;
    }
    else {
        QString fileType = dia ;
        fileTypes << fileType ;
        QDir myFolder(path+"/"+fileType) ;
        if (!myFolder.exists()) {
            myFolder.mkdir(path+"/"+fileType) ;
        }

        QString paddedNum = txtTitle.mid(1).rightJustified(4, '0');
        QFile file(path+"/" + fileType + "/O" + paddedNum/*+ "0" + QString::number(curNum)*/ + ".PRG");

        // 打开文件，以便将数据写入文件中
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            //qDebug() << 1 ;
            QTextStream out(&file);
            out << totalString;
            file.close();
        }
        totalString.clear() ;
    }

}

QString MainWindow::getDouble(double reDouble) {
    return QString::number(QString::asprintf("%.3f", reDouble).toDouble(), 'f', QLocale::FloatingPointShortest) ;
}

bool compare(const angles &infoA,const angles &infoB) {
    return infoA.holeType > infoB.holeType ;
}

void MainWindow::initOutput() {


        QStringList tTypes ;
        //tTypes << QString::number(millingCutterN)  ;

        QString temModel_1 = model_1 ;
        QString title = txtTitle.mid(1) ;
        QString paddedNum = title.rightJustified(4, '0');
        temModel_1.replace("O1234", "O" + paddedNum) ;
        temModel_1.replace("T# M06", "T" + QString::number(millingCutterN) + " M06") ;
        temModel_1.replace("M#", millingCutterP) ;
        temModel_1.replace("S900", "S" + QString::number(millingCutterF)) ;
        totalString +=  temModel_1;

        for (int i = 0; i < holeNum; i++) {
        double x1 = sqrt(sphericalRadius*sphericalRadius - (sphericalRadius - millingDepth)*(sphericalRadius - millingDepth)) + (100/2) ;
            double x2 = x1 - (sqrt(sphericalRadius*sphericalRadius - (sphericalRadius - millingDepth)*(sphericalRadius - millingDepth)))*2 - 10 ;
            double z1 = sphericalRadius + 10 ;
            double z2 = sphericalRadius - millingDepth ;
            //int x2 = 30 - sqrt(sphericalRadius*sphericalRadius -
              //                 (sphericalRadius - millingDepth)*(sphericalRadius - millingDepth)) ;
            double z3 = z1 ;
            QString temModel = model_2 ;
            temModel.replace("A#", "A"+QString::number(QString::asprintf("%.3f", myAngles[i].angleA.toDouble()).toDouble(), 'f', QLocale::FloatingPointShortest)) ;
            temModel.replace("B#", "B"+QString::number(QString::asprintf("%.3f", myAngles[i].angleB.toDouble()).toDouble(), 'f', QLocale::FloatingPointShortest)) ;
            temModel.replace("G00 X#", "G00 X"+getDouble(x1 + startNumbers[dia.toInt()])) ;
            temModel.replace("G43 Z#", "G43 Z"+QString::number(z1)) ;
            temModel.replace("G01 Z#", "G01 Z"+QString::number(z2)) ;
            temModel.replace("X# F600", QString("X%1 F%2").arg(getDouble(x2 + endNumbers[dia.toInt()])).arg(millingCutterS.value(QString::number(sphericalRadius*2)))) ;
            temModel.replace("Z# F5000", QString("Z%1 F5000").arg(QString::number(z3))) ;
            totalString += temModel ;
        }

        totalString += model_3 ;
        std::sort(holeTypeList.begin(), holeTypeList.end(), std::greater<QString>()) ;
        //qDebug() << holeTypeList << "here true" ;
        std::sort(myAngles.begin(), myAngles.end(), compare) ;
        //Debug() << myAngles << "Angels here" ;
        int sum = 1 ;
        for (int i = 0; i < holeTypeList.count(); i++) {
            if (i == 0) {
                sum ++ ;
                tTypes << QString::number(drillTypes.value(holeTypeList[i])) ;
                QString temModel_4 = model_4 ;
                temModel_4.replace("N#", "N"+QString::number(sum)) ;
                if (sphericalRadius > 75) {
                temModel_4.replace("Z#",
                                   "Z" + QString::number
                                    (0 - 50 - sphericalRadius + LianDongJvLi_Big150)) ;
                }
                else {
                temModel_4.replace("Z#",
                                   "Z" + QString::number
                                    (0 - 50 - sphericalRadius + LianDongJvLi_Small150)) ;
                }
                temModel_4.replace("S#", "S" + QString::number(drillS.value(drillTypes.value(holeTypeList[i])))) ;
                temModel_4.replace("T# M06", "T" + QString::number(drillTypes.value(holeTypeList[i])) + " M06") ;
                temModel_4.replace("M#", drillP.value(QString::number(drillTypes.value(holeTypeList[i])))) ;
                temModel_4.replace("H#","H" + QString::number(drillTypes.value(holeTypeList[i]))) ;
                totalString += temModel_4 ;
            } else {
                if (holeTypeList[i] != holeTypeList[i - 1]) {
                    sum ++ ;
                    tTypes << QString::number(drillTypes.value(holeTypeList[i])) ;
                    QString temModel_4 = model_4 ;
                    temModel_4.replace("N#", "N" + QString::number(sum)) ;
                    if (sphericalRadius > 75) {
                        temModel_4.replace("Z#",
                                           "Z" + QString::number
                                            (0 - 50 - sphericalRadius + LianDongJvLi_Big150)) ;
                    }
                    else {
                        temModel_4.replace("Z#",
                                           "Z" + QString::number
                                            (0 - 50 - sphericalRadius + LianDongJvLi_Small150)) ;
                    }
                    temModel_4.replace("S#", "S" + QString::number(drillS.value(drillTypes.value(holeTypeList[i])))) ;
                    temModel_4.replace("T# M06", "T" + QString::number(drillTypes.value(holeTypeList[i])) + " M06") ;
                    temModel_4.replace("M#", drillP.value(QString::number(drillTypes.value(holeTypeList[i])))) ;
                    temModel_4.replace("H#","H" + QString::number(drillTypes.value(holeTypeList[i]))) ;
                    totalString += temModel_4 ;
                }
            }
            //qDebug() << holeTypeList[i] << "now here";

            QString temModel_5 = model_5 ;
            //G54 G90 G01 Z# F5000
            //G91 G01 Y15 F2000
            if (sphericalRadius > 75) {
                temModel_5.replace("G91 G01 Y15 F2000", QString("G91 G01 Y%1 F2000").arg(QString::number(y_Big150))) ;
            }else {
                temModel_5.replace("G91 G01 Y15 F2000", QString("G91 G01 Y%1 F2000").arg(QString::number(y_Small150))) ;
            }
            temModel_5.replace("A#", "A" + QString::number(QString::asprintf("%.3f", myAngles[i].angleA.toDouble()).toDouble(), 'f', QLocale::FloatingPointShortest)) ;
            temModel_5.replace("B#", "B" + QString::number(QString::asprintf("%.3f", myAngles[i].angleB.toDouble()).toDouble(), 'f', QLocale::FloatingPointShortest)) ;
            temModel_5.replace("F20;", QString("F%1;").arg(QString::number(superF[holeTypeList[i]]))) ;
            temModel_5.replace("X1", "X" + QString::number(holeX.value(holeTypeList[i]))) ;
            temModel_5.replace("Y# F#", QString("Y%1 F%2").arg(QString::number(sphericalRadius - drillDepth2.value(holeTypeList[i]) - millingDepth)).arg(QString::number(drillF2.value(drillTypes.value(holeTypeList[i])))) );
            temModel_5.replace("Z# F#", QString("Y%1 F%2").arg(QString::number(sphericalRadius - drillDepth.value(holeTypeList[i]) - millingDepth)).arg(QString::number(drillF.value(drillTypes.value(holeTypeList[i])))) );
            temModel_5.replace("G54 G90 G01 Z# F5000", QString("G54 G90 G01 Y%1 F5000")
                               .arg(QString::number(sphericalRadius - millingDepth + 2))) ;
            temModel_5.replace("G01 Z# F5000", QString("G01 Y%1 F5000")
                               .arg(QString::number(sphericalRadius+10))) ;
            //QString strNew = QString("%1").arg(str.toInt(), 4, 10, QLatin1Char('0'));
            temModel_5.replace("#5542=-#511+#300X+#5543+#510", QString("#5542=-#511+#300%1+#5543+#510").arg(QString("%1").arg(drillTypes.value(holeTypeList[i]), 2, 10, QLatin1Char('0')))) ;

            totalString += temModel_5 ;

            if (i == holeTypeList.count() - 1) {
                QString temModel_6 = model_6 ;
                totalString += temModel_6 ;
            } else {
                if (holeTypeList[i] != holeTypeList[i + 1]) {
                    QString temModel_6 = model_6 ;
                    totalString += temModel_6 ;
                }
            }
        }

        sum ++ ;
        tTypes << QString::number(chamferCutterN) ;
        QString temModel_7 = model_7 ;
        temModel_7.replace("T# M06", "T" + QString::number(chamferCutterN) + " M06") ;
        temModel_7.replace("S200", "S" + QString::number(chamferCutterS)) ;
        temModel_7.replace("N#", "N"+QString::number(sum)) ;
        temModel_7.replace("G43 Z#", "G43 Z" + QString::number(sphericalRadius + 10)) ;
        temModel_7.replace("H#", "H" + QString::number(chamferCutterN)) ;
        temModel_7.replace("M#", chamferCutterP) ;
        temModel_7.replace("X0 A#", "X0 A"+QString::number(QString::asprintf("%.3f", myAngles[0].angleA.toDouble()).toDouble(), 'f', QLocale::FloatingPointShortest)) ;
        temModel_7.replace("B#;", "B"+QString::number(QString::asprintf("%.3f", myAngles[0].angleB.toDouble()).toDouble(), 'f', QLocale::FloatingPointShortest)+";") ;
        QString holeNum2 = holeTypeList[0] ;
        holeNum2.remove(0, 1) ;
        temModel_7.replace("G98 G81 A# B# Z# R# F100",
                           QString("G98 G81 A%1 B%2 Z%3 R%4 F100")
                           .arg(QString::number(QString::asprintf("%.3f", myAngles[0].angleA.toDouble()).toDouble(), 'f', QLocale::FloatingPointShortest))
                           .arg(QString::number(QString::asprintf("%.3f", myAngles[0].angleB.toDouble()).toDouble(), 'f', QLocale::FloatingPointShortest))
                           .arg(QString::number(sphericalRadius -  millingDepth - holeNum2.toInt()/2 - 2))
                           //.arg(QString::number(sphericalRadius - (holeNum2.toInt() - screwF.value(screwTypes.value(holeTypeList[0])))/2 + 4))
                           .arg(QString::number(sphericalRadius -  millingDepth - holeNum2.toInt()/2 + 6))
                            ) ;
        temModel_7.replace("F100", "F" + QString::number(chamferCutterF)) ;
        totalString += temModel_7 ;

        for (int i = 1; i < holeTypeList.count(); i++) {
            QString temModel_8 = model_8 ;
            //G54 G90 G01 Z# F5000
            QString holeNum2 = holeTypeList[i] ;
            holeNum2.remove(0, 1) ;
            temModel_8.replace("G98 G81 A# B# Z# R# F100",
                                       QString("G98 G81 A%1 B%2 Z%3 R%4 F100")
                                       .arg(QString::number(QString::asprintf("%.3f", myAngles[i].angleA.toDouble()).toDouble(), 'f', QLocale::FloatingPointShortest))
                                       .arg(QString::number(QString::asprintf("%.3f", myAngles[i].angleB.toDouble()).toDouble(), 'f', QLocale::FloatingPointShortest))
                                       .arg(QString::number(sphericalRadius -  millingDepth - holeNum2.toInt()/2 - 2))
                                       //.arg(QString::number(sphericalRadius - (holeNum2.toInt() - screwF.value(screwTypes.value(holeTypeList[0])))/2 + 4))
                                       .arg(QString::number(sphericalRadius -  millingDepth - holeNum2.toInt()/2 + 6))
                                       ) ;
                    temModel_8.replace("F100", "F" + QString::number(chamferCutterF)) ;
            totalString += temModel_8 ;
        }

        QString temModel_9 = model_9 ;
        totalString += temModel_9 ;

        for (int i = 0; i < holeTypeList.count(); i++) {
            if (i == 0) {
                sum ++ ;
                tTypes << QString::number(screwTypes.value(holeTypeList[i])) ;
                QString temModel_10 = model_10 ;
                temModel_10.replace("N#", "N"+QString::number(sum)) ;
                temModel_10.replace("T# M06", "T" + QString::number(screwTypes.value(holeTypeList[i])) + " M06") ;
                temModel_10.replace("M#", screwP.value(QString::number(screwTypes.value(holeTypeList[i])))) ;
                totalString += temModel_10 ;
            } else {
                if (holeTypeList[i] != holeTypeList[i - 1]) {
                    sum ++ ;
                    tTypes << QString::number(screwTypes.value(holeTypeList[i])) ;
                    QString temModel_10 = model_10 ;
                    temModel_10.replace("N#", "N"+QString::number(sum)) ;
                    temModel_10.replace("T# M06", "T" + QString::number(screwTypes.value(holeTypeList[i])) + " M06") ;
                    temModel_10.replace("M#", screwP.value(QString::number(screwTypes.value(holeTypeList[i])))) ;
                    totalString += temModel_10 ;
                }
            }

            QString temModel_11 = model_11 ;
            //G54 G90 G01 Z# F5000
            temModel_11.replace("A#", "A"+QString::number(QString::asprintf("%.3f", myAngles[i].angleA.toDouble()).toDouble(), 'f', QLocale::FloatingPointShortest)) ;
            temModel_11.replace("B#", "B"+QString::number(QString::asprintf("%.3f", myAngles[i].angleB.toDouble()).toDouble(), 'f', QLocale::FloatingPointShortest)) ;

            temModel_11.replace("G43 Z#", QString("G43 Z%1")
                               .arg(QString::number(sphericalRadius+10))) ;
            temModel_11.replace("H#", "H" + QString::number(screwTypes.value(holeTypeList[i]))) ;
            temModel_11.replace("M29 S#", "M29 S" + QString::number(screwS.value(screwTypes.value(holeTypeList[i]))));
            temModel_11.replace("G98 G84 Z# R# F# RS#", QString("G98 G84 Z%1 R%2 F%3 RS%4")
                                .arg(QString::number(sphericalRadius - millingDepth - screwDepth.value(holeTypeList[i])))
                                .arg(QString::number(sphericalRadius - millingDepth + 2))
                                .arg(QString::number(screwF.value(screwTypes.value(holeTypeList[i]))))
                                .arg(QString::number(RS.value(holeTypeList[i])))
                                /*.arg(QString::number(screwS.value(screwTypes.value(holeTypeList[i]))*2))*/) ;
            if (holeTypeList[i] == "M20") {
                //qDebug() << "CHeck F" << screwF.value(screwTypes.value(holeTypeList[i]));
            }
            totalString += temModel_11 ;

            if (i == holeTypeList.count() - 1) {
                QString temModel_12 = model_12 ;
                totalString += temModel_12 ;
            } else {
                if (holeTypeList[i] != holeTypeList[i + 1]) {
                    QString temModel_12 = model_12 ;
                    totalString += temModel_12 ;
                }
            }
        }
        totalString += model_13 ;

        tTypes << QString::number(millingCutterN)  ;

        //tTypes << QString::number(millingCutterN)  ;
        int index = 0 ;
        int k = 0 ;// que shao T
        while ((index = totalString.indexOf("T#", index)) != -1) {
            totalString.replace(index, QString("T#").length(), "T" + tTypes[k]) ;
            index += tTypes[k].length() + 1 ;
            k++ ;
        }

}

void MainWindow::on_pushButton_4_clicked()
{
    if (fileTips != true || setTips != true) {

            QMessageBox::information(this, "警告", "参数设置或待处理文件未导入") ;
            return ;

    }
    path = QFileDialog::getExistingDirectory(this, "Select Directory",
                QDir::homePath(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

            // 如果目标文件夹路径为空，则返回
    if (path.isEmpty())
         return;

    //QMessageBox::information(this, "提示", "程序输出已解锁") ;

    ui->pushButton_2->setEnabled(true);

}


void MainWindow::on_pushButton_2_clicked()
{
    if (fileTips != true || setTips != true) {
        QMessageBox::information(this, "警告", "参数设置或待处理文件未导入") ;
        return ;
    }

    openExcel(excelPath) ;
}

