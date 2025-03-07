#include "parameterwidget.h"
#include "ui_parameterwidget.h"

ParameterWidget::ParameterWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ParameterWidget)
{
    ui->setupUi(this);
    this->setWindowTitle("参数设置") ;
    QObject::connect(ui->tabWidget, &QTabWidget::currentChanged, this, &ParameterWidget::changeWindowSize) ;
    QObject::connect(&l, &LoginDialog::successLogin, this, &ParameterWidget::reInitTable) ;
    initAllLists() ;
    getSignals() ;
}

void ParameterWidget::getSignals() {
    qDebug() << "success recieve mainwindow signals" ;
    //emit haveSaved() ;
}

void ParameterWidget::reInitTable() {
    setTableWidgetEditable(ui->xianTable, xianLists) ;
    setTableWidgetEditable(ui->daoTable, daoLists) ;
    //setTableWidgetEditable(ui->lianTable, lianLists) ;
    setTableWidgetEditable(ui->holeTable, holeLists) ;
}

bool ParameterWidget::checkDir() {


    QFile file(filePath);

    if (file.exists()) {
        qDebug() << "The file exists.";
        return true ;
    } else {
        qDebug() << "The file does not exist.";
        return false ;
    }

}

QJsonArray ParameterWidget::listToJsonArray(const QList<QList<QVariant>> &list)
{
    QJsonArray jsonArray;
    for (const auto &row : list) {
        QJsonArray jsonRow;
        for (const auto &item : row) {
            jsonRow.append(QJsonValue::fromVariant(item));
        }
        jsonArray.append(jsonRow);
    }
    return jsonArray;
}

QList<QList<QVariant>> ParameterWidget::jsonArrayToList(const QJsonArray &jsonArray)
{
    QList<QList<QVariant>> list;
    for (const auto &jsonRow : jsonArray) {
        QList<QVariant> row;

        for (const auto &jsonItem : jsonRow.toArray()) {
            row.append(jsonItem.toVariant());
        }
        list.append(row);
    }
    return list;
}

void ParameterWidget::setTableWidgetEditable(QTableWidget* &table, QList<QList<QVariant>> &lists)
{
    int rows = table->rowCount();
    int cols = table->columnCount();

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            QTableWidgetItem *item = table->item(row, col);
            if (item) {
                item->setFlags(item->flags() | Qt::ItemIsEditable);
                item->setText(lists[row][col].toString()) ;
            } else {
                // 如果单元格为空，创建一个新的可编辑单元格
                QTableWidgetItem *newItem = new QTableWidgetItem();
                newItem->setFlags(newItem->flags() | Qt::ItemIsEditable);
                newItem->setText(lists[row][col].toString()) ;
                table->setItem(row, col, newItem);
            }
        }
    }
}

void ParameterWidget::writeDataToJsonFile(const QString &filePath)
{
    QJsonObject json;
    json["xianLists"] = listToJsonArray(xianLists);
    json["daoLists"] = listToJsonArray(daoLists);
    //json["lianLists"] = listToJsonArray(lianLists);
    json["holeLists"] = listToJsonArray(holeLists);

    QJsonDocument doc(json);
    QFile file(filePath);

    QDir dir;
    if (!dir.exists(filePath)) {
        dir.mkpath(QFileInfo(filePath).path());
        //qDebug() << "creat file" ;
    }

    if (file.open(QIODevice::WriteOnly)) {
        //qDebug() << "all size:" << doc.toJson().size();
        file.write(encodedText(doc.toJson(), "yiran13"));
        //qDebug() << "encode size: "<<encodedText(doc.toJson(), "yiran13").size() ;
        //file.write(doc.toJson());
        file.close();
    }
}

void ParameterWidget::readDataFromJsonFile(const QString &filePath)
{
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly)) {
        //qDebug() << "read size" << file.readAll() << file.readAll().size() ;
        QByteArray data = decodedText(file.readAll(), "yiran13");
        //QByteArray data = file.readAll() ;
        //qDebug() << "data decode" << data << data.size() ;
        int len = data.size() ;
        int sum = 0 ;
        for (int i = len - 1; i >= 0; i --) {

            if (data[i] != '\x00') {
                data.remove(i+1, sum) ;
                break ;
            }
            sum++ ;
        }
        //qDebug() << sum ;
        file.close();
        //qDebug() << "data decode" << data.size() ;

        QJsonDocument doc = QJsonDocument::fromJson(data);
        QJsonObject json = doc.object();
        //qDebug() << "json" << json.empty() ;

        xianLists = jsonArrayToList(json["xianLists"].toArray());
        daoLists = jsonArrayToList(json["daoLists"].toArray());
        //lianLists = jsonArrayToList(json["lianLists"].toArray());
        holeLists = jsonArrayToList(json["holeLists"].toArray());
        qDebug() << doc ;
    }
}



void ParameterWidget::initAllLists() {
    if (checkDir() == false) {
        initXianLists() ;
        initDaoLists() ;
        //initLianLists() ;
        initHoleLists() ;
        //qDebug() << "initLists Success" ;
        initAllTable() ;
    } else {
        readDataFromJsonFile(filePath) ;
        //qDebug() << "read json success" ;
        //qDebug() << daoLists.size() ;
        initAllTable() ;
    }
    //emit void haveSaved() ;
    qDebug() << "initAllTableS over" ;
}

void ParameterWidget::fillTableWidget(QTableWidget* &table, const QList<QList<QVariant>> &data)
{
    //qDebug() << data.size() ;
    table->setRowCount(data.size());
    table->setColumnCount(data[0].size());

    for (int row = 0; row < data.size(); ++row) {
        for (int col = 0; col < data[row].size(); ++col) {
            table->setItem(row, col, new QTableWidgetItem(data[row][col].toString()));
        }
    }
}

void ParameterWidget::initXianLists() {
    xianLists = {
        {"铣刀号"},
        {1}
    };
}

void ParameterWidget::initDaoLists() {
    daoLists = {
        {"倒角刀号"},
        {2}
        };
}

void ParameterWidget::initLianLists() {
    lianLists = {
        {"建立联动距离<=150", 0},
        {"建立联动距离>150", 0},
        {"直径>150", 10},
        {"直径<=150", 15}
    };
}

void ParameterWidget::initHoleLists() {
    holeLists = {
        {"孔类型", "钻头号", "丝锥号"},
        {"", "", ""},
        {"", "", ""},
        {"M52", 21, 22},
        {"M48", 5, 6},
        {"M45", 13, 14},
        {"M42", 19, 20},
        {"M39", 17, 18},
        {"M36", 15, 16},
        {"M33", "", ""},
        {"M30", 11, 12},
        {"M27", 9, 10},
        {"M24", 7, 8},
        {"M22", "", ""},
        {"M20", 3, 4},
        {"M16", 23, 600}
    };
}

void ParameterWidget::initAllTable() {
    ui->tabWidget->setCurrentIndex(0) ;
    this->resize(QSize(406, 605)) ;

    fillTableWidget(ui->xianTable, xianLists) ;
    fillTableWidget(ui->daoTable, daoLists) ;
    //fillTableWidget(ui->lianTable, lianLists) ;
    fillTableWidget(ui->holeTable, holeLists) ;

    //setTableWidgetReadOnly(ui->xianTable) ;
    //setTableWidgetReadOnly(ui->daoTable) ;
    //setTableWidgetReadOnly(ui->lianTable) ;
    //setTableWidgetReadOnly(ui->holeTable) ;

    /*setCellEditable(ui->xianTable, 1, 1, xianLists) ;
    setCellEditable(ui->xianTable, 0, 0, xianLists) ;
    setCellEditable(ui->xianTable, 0, 1, xianLists) ;
    setCellEditable(ui->xianTable, 2, 0, xianLists) ;
    setCellEditable(ui->xianTable, 2, 1, xianLists) ;
    setCellEditable(ui->xianTable, 3, 1, xianLists) ;
    setCellEditable(ui->xianTable, 0, 14, xianLists) ;
    setCellEditable(ui->xianTable, 0, 13, xianLists) ;

    setCellEditable(ui->daoTable, 1, 0, daoLists) ;
    setCellEditable(ui->daoTable, 0, 0, daoLists) ;
    setCellEditable(ui->daoTable, 0, 1, daoLists) ;
    setCellEditable(ui->daoTable, 0, 2, daoLists) ;
    setCellEditable(ui->daoTable, 0, 3, daoLists) ;

    setCellEditable(ui->lianTable, 0, 0, lianLists) ;
    setCellEditable(ui->lianTable, 1, 0, lianLists) ;
    setCellEditable(ui->lianTable, 2, 0, lianLists) ;
    setCellEditable(ui->lianTable, 3, 0, lianLists) ;*/
/*
    for(int row = 1; row < holeLists.size(); row ++) {
        setCellEditable(ui->holeTable, row, 1, holeLists) ;
        setCellEditable(ui->holeTable, row, 10, holeLists) ;
        setCellEditable(ui->holeTable, row, 0, holeLists) ;
    }*/
    for(int row = 1; row < holeLists.size(); row ++) {
        setCellReadOnly(ui->holeTable, row, 0, holeLists) ;
    }
    /*for(int col = 0; col < holeLists[0].size(); col ++) {
        setCellEditable(ui->holeTable, 0, col, holeLists) ;
    }*/
}

void ParameterWidget::replaceHoleType(QList<QString> holeTypes) {
    int rows = ui->holeTable->rowCount() - 1 ;
    for (int row = 0; row < rows; ++row) {
        ui->holeTable->item(row, 0)->setText(holeTypes[row]);
    }
}

void ParameterWidget::setCellEditable(QTableWidget* &table, int row, int col, QList<QList<QVariant>> &lists)
{
    QTableWidgetItem *item = table->item(row, col);
    if (item) {
        item->setFlags(item->flags() | Qt::ItemIsEditable);
        item->setText(lists[row][col].toString()) ;
    } else {
        // 如果单元格为空，创建一个新的可编辑单元格
        QTableWidgetItem *newItem = new QTableWidgetItem();
        newItem->setFlags(newItem->flags() | Qt::ItemIsEditable);
        newItem->setText(lists[row][col].toString()) ;
        table->setItem(row, col, newItem);
    }
}

void ParameterWidget::setCellReadOnly(QTableWidget* &table, int row, int col, QList<QList<QVariant>> &lists)
{
    QTableWidgetItem *item = table->item(row, col);
    if (item) {
        item->setFlags(item->flags() & ~Qt::ItemIsEditable);

    } else {
        // 如果单元格为空，创建一个新的可编辑单元格
        QTableWidgetItem *newItem = new QTableWidgetItem();
        newItem->setFlags(newItem->flags() & ~Qt::ItemIsEditable);

        table->setItem(row, col, newItem);
    }
}


void ParameterWidget::setTableWidgetReadOnly(QTableWidget* &table)
{
    int rows = table->rowCount();
    int cols = table->columnCount();

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            QTableWidgetItem *item = table->item(row, col);
            if (item) {
                item->setFlags(item->flags() & ~Qt::ItemIsEditable);
                //item->setText("*") ;
            }
        }
    }
}
void ParameterWidget::changeWindowSize(int index) {
    qDebug () << "Now index:    " <<  index ;
    if (index == 0) {
        this->resize(QSize(406, 605)) ;//QSize(1570, 270)
    }
    if (index == 1) {
        this->resize(QSize(406, 605)) ;//QSize(485, 190)
    }
    if (index == 2) {
        this->resize(QSize(406, 605)) ;//QSize(475, 140)
    }
    if (index == 3) {
        this->resize(QSize(406, 605)) ;
    }
}


ParameterWidget::~ParameterWidget()
{
    delete ui;
}

QList<QList<QVariant>> ParameterWidget::readTableWidget(QTableWidget* &table, QList<QList<QVariant>> &lists)
{
    QList<QList<QVariant>> data;
    int rows = table->rowCount();
    int cols = table->columnCount();

    for (int row = 0; row < rows; ++row) {
        QList<QVariant> rowData;
        for (int col = 0; col < cols; ++col) {
            QTableWidgetItem *item = table->item(row, col);
            if (item) {
                if (item->text() == "*") {
                    rowData.append(lists[row][col]);
                }
                else {
                    rowData.append(item->text());
                }
            } else {
                rowData.append(QVariant());
            }
        }
        data.append(rowData);
    }
    return data;
}

bool ParameterWidget::compareLists() {

    for (int row = 0; row < xianLists.size(); ++row) {
        for (int col = 0; col < xianLists[row].size(); ++col) {
            if (xianLists[row][col] != xianLists2[row][col]) {
                return false ;
            }
        }
    }

    for (int row = 0; row < daoLists.size(); ++row) {
        for (int col = 0; col < daoLists[row].size(); ++col) {
            if (daoLists[row][col] != daoLists2[row][col]) {
                return false ;
            }
        }
    }

    for (int row = 0; row < lianLists.size(); ++row) {
        for (int col = 0; col < lianLists[row].size(); ++col) {
            if (lianLists[row][col] != lianLists2[row][col]) {
                return false ;
            }
        }
    }

    for (int row = 0; row < holeLists.size(); ++row) {
        for (int col = 0; col < holeLists[row].size(); ++col) {
            if (holeLists[row][col] != holeLists2[row][col]) {
                return false ;
            }
        }
    }

    return true ;
}


void ParameterWidget::closeEvent(QCloseEvent* event) {
    QVariant result = QMessageBox::question(this, "提示", "是否保存更改信息？", QMessageBox::Yes|QMessageBox::No) ;
    if(result == QMessageBox::Yes)
    {
        qDebug() << "Save close Start" ;

        xianLists2 = readTableWidget(ui->xianTable, xianLists) ;
        daoLists2 = readTableWidget(ui->daoTable, daoLists) ;
        //lianLists2 = readTableWidget(ui->lianTable, lianLists) ;
        holeLists2 = readTableWidget(ui->holeTable, holeLists) ;

        xianLists = xianLists2 ;
        daoLists = daoLists2 ;
        //lianLists = lianLists2 ;
        holeLists = holeLists2 ;

        //qDebug() << lianLists ;
        qDebug() << "have close changed" ;

        xianLists2.clear() ;
        daoLists2.clear() ;
        //lianLists2.clear() ;
        holeLists2.clear() ;

        writeDataToJsonFile(filePath) ;
        qDebug() << "save Success" ;

        emit haveSaved() ;
        emit haveClosed() ;
        event->accept();//默认情况下接收关闭信号，关闭窗体
    }
    else
    {
        qDebug() << "delet" ;
        emit haveClosed() ;
        event->accept();
    }

}


/*void ParameterWidget::on_pushButton_clicked()
{
    l.show() ;
}*/

QByteArray ParameterWidget::encodedText(QByteArray data, QString key)
{
    //密钥长度AES_128,加密方式ECB,填充方式ZERO
    QAESEncryption encryption(QAESEncryption::AES_256, QAESEncryption::ECB,                 QAESEncryption::ZERO);

    //使用QCryptographicHash对密钥进行加密
    QByteArray hashKey = QCryptographicHash::hash(key.toUtf8(), QCryptographicHash::Sha256);
    qDebug() << "hashKey: " << hashKey << hashKey.size() ;
    //对源数据加密
    qDebug() << "Data1" << data.size() ;
    QByteArray encodedText = encryption.encode(data, hashKey);
    qDebug() << "Data2 " << encodedText.size() ;
    //QByteArray转QString (toBase64()不能去掉)
   // QString encodeTextStr = QString::fromLatin1(encodedText.toBase64());
    //qDebug()<< "encodedText:"<< encodeTextStr;

    return encodedText;
}

//使用AES对数据进行解密
QByteArray ParameterWidget::decodedText(QByteArray data, QString key)
{
    //密钥长度AES_128,加密方式ECB,填充方式ZERO
    QAESEncryption encryption(QAESEncryption::AES_256, QAESEncryption::ECB,     QAESEncryption::ZERO);

    //使用QCryptographicHash对密钥进行加密
    QByteArray hashKey = QCryptographicHash::hash(key.toUtf8(), QCryptographicHash::Sha256);
    qDebug() << "hashKey" << hashKey ;
    //解密
    qDebug() << "data before decode" << data.size() ;
    QByteArray decodedText = encryption.decode(data, hashKey);
    qDebug() << "decode size" << decodedText.size() ;
    //QDebug()
    //QByteArray转QString
    //QString decodedTextStr = QString::fromLatin1(decodedText);
    //qDebug()<<"decodedText:"<< decodedTextStr;

    return decodedText;
}
