#include "parameterwidget.h"
#include "ui_parameterwidget.h"

ParameterWidget::ParameterWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ParameterWidget)
{
    ui->setupUi(this);
    this->setWindowTitle("参数设置") ;
    QObject::connect(ui->tabWidget, &QTabWidget::currentChanged, this, &ParameterWidget::changeWindowSize) ;
    //initAllLists() ;
}

void ParameterWidget::tcpDisconnect() {
    if (!this->isHidden()){
        QMessageBox::information(this, "提示", "未连接到服务器\n请打开网络或联系管理员") ;
        this->hide();
        //emit reLogin() ;
    }
}

void ParameterWidget::reInitTable() {
    setTableWidgetEditable(ui->xianTable, xianLists) ;
    setTableWidgetEditable(ui->daoTable, daoLists) ;
    //setTableWidgetEditable(ui->lianTable, lianLists) ;
    setTableWidgetEditable(ui->holeTable, holeLists) ;
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

void ParameterWidget::writeDataToJsonFile()
{
    xianLists2 = readTableWidget(ui->xianTable, xianLists) ;
    daoLists2 = readTableWidget(ui->daoTable, daoLists) ;
    lianLists2 = readTableWidget(ui->lianTable, lianLists) ;
    holeLists2 = readTableWidget(ui->holeTable, holeLists) ;

    xianLists = xianLists2 ;
    daoLists = daoLists2 ;
    lianLists = lianLists2 ;
    holeLists = holeLists2 ;

    qDebug() << "holelists ssssss" << holeLists[10] ;

    QJsonObject json;
    json["xianLists"] = listToJsonArray(xianLists);
    json["daoLists"] = listToJsonArray(daoLists);
    json["lianLists"] = listToJsonArray(lianLists);
    json["holeLists"] = listToJsonArray(holeLists);
    QJsonDocument doc(json);

    qDebug() << "have save data" ;

    QString curData = doc.toJson() ;
    QString dataSize = QString::number(curData.length());
    QString reData = QString::number(dataSize.length()) + dataSize + curData ;

    QString msg =  reData ;
    QString totalMsg = "parameterset " + msg ;
    bool firstMsg = true ;
    int len = totalMsg.length() ;
    qDebug () << "len" << len ;
    while (len >= 400) {
        QString tempMsg ;
        if (firstMsg == false)
            tempMsg = totalMsg.mid(0, 400) ;
        else {
            tempMsg = totalMsg.mid(0, 400) ;
            firstMsg = false ;
        }
        //qDebug () << "tempMsg" << tempMsg ;
        emit sendWrite(tempMsg.toUtf8(), tempMsg.toUtf8().size()) ;
        qDebug () << "tempMsg" << tempMsg.size() << "\n" ;
        len -= 400 ;
        totalMsg = totalMsg.mid(400) ;
    }
    //qDebug () << "len" ;
    //totalMsg = totalMsg ;
    emit sendWrite(totalMsg.toUtf8(), totalMsg.toUtf8().size()) ;
}

void ParameterWidget::readDataFromJsonFile(QString data)
{
    QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());
    QJsonObject json = doc.object();
    //qDebug() << "json" << json.empty() ;

    xianLists = jsonArrayToList(json["xianLists"].toArray());
    daoLists = jsonArrayToList(json["daoLists"].toArray());
    lianLists = jsonArrayToList(json["lianLists"].toArray());
    holeLists = jsonArrayToList(json["holeLists"].toArray());

    initAllTable();
}



void ParameterWidget::initAllLists() {
    emit sendListsGet("parameterget lian") ;
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

void ParameterWidget::initAllTable() {
    ui->tabWidget->setCurrentIndex(0) ;
    this->resize(QSize(1000, 605)) ;

    fillTableWidget(ui->xianTable, xianLists) ;
    fillTableWidget(ui->daoTable, daoLists) ;
    fillTableWidget(ui->lianTable, lianLists) ;
    fillTableWidget(ui->holeTable, holeLists) ;

    setCellReadOnly(ui->xianTable, 1, 1, xianLists) ;
    setCellReadOnly(ui->daoTable, 1, 0, daoLists) ;
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
        setCellReadOnly(ui->holeTable, row, 1, holeLists) ;
        setCellReadOnly(ui->holeTable, row, 10, holeLists) ;
    }
    /*for(int col = 0; col < holeLists[0].size(); col ++) {
        setCellEditable(ui->holeTable, 0, col, holeLists) ;
    }*/
    ui->holeTable->setColumnHidden(1, true);
    ui->holeTable->setColumnHidden(10, true);
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

void ParameterWidget::on_pushButton_clicked()
{
    writeDataToJsonFile();
    QMessageBox::information(this, "提示", "参数设置已上传") ;
}


void ParameterWidget::on_pushButton_2_clicked()
{
    emit parameterWidgetClose() ;
    initAllTable();
    this->hide() ;
}

