#include "mainwindow.h"

MainWindow::MainWindow()
{
    resize(windowSize);
    setMaximumSize(windowSize);
    setMinimumSize(windowSize);

    font.setPixelSize(11);
    dbPath = QString("./db.sqlite3");

    cashTableWidget = new QTableWidget(this);
    cashTableWidget->setGeometry(0,0,800,600);
    cashTableWidget->setRowCount(20);
    cashTableWidget->setColumnCount(6);
    cashTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    cashTableWidget->setSelectionMode(QAbstractItemView::NoSelection);
    cashTableWidget->horizontalHeader()->setVisible(false);
    cashTableWidget->horizontalHeader()->setDefaultSectionSize(400);
    cashTableWidget->horizontalHeader()->setHighlightSections(false);
    cashTableWidget->verticalHeader()->setVisible(false);
    cashTableWidget->verticalHeader()->setDefaultSectionSize(600);
    cashTableWidget->verticalHeader()->setHighlightSections(false);
    addNRow(20);

    for(int c = 0; c < 6; c++)
    {
        cashTableWidget->setColumnWidth(c, 400 / 6);
        cashTableWidget->item(0,c)->setText(headers[c]);
    }

    installLabel(400, 30, QString("日期"));
    installLabel(480, 30, QString("投入"));
    installLabel(560, 30, QString("净值"));
    installLabel(640, 30, QString("份额"));
    installLabel(720, 30, QString("手续费"));
    installLabel(400, 150, QString("ID"));
    installLabel(400, 180, QString("日期"));
    installLabel(480, 180, QString("投入"));
    installLabel(560, 180, QString("份额"));
    installLabel(640, 180, QString("净值"));
    installLabel(720, 180, QString("手续费"));
    installLabel(400, 300, QString("计算投资"));
    installLabel(620, 300, QString("计算结果"));
    installLabel(400, 330, QString("基数"));
    installLabel(480, 330, QString("收益率"));
    installLabel(560, 330, QString("因数杠杆"));
    installLabel(640, 330, QString("指数杠杆"));
    installLabel(400, 400, QString("导入/导出"));
    installLabel(400, 430, QString("路径"));


    dateEdit = installLineEdit(400,50, new QIntValidator);
    investmentEdit = installLineEdit(480, 50, new QIntValidator);
    worthEdit = installLineEdit(560, 50);
    shareEdit = installLineEdit(640, 50);
    feeEdit = installLineEdit(720, 50);
    identEdit = installLineEdit(430, 150, new QIntValidator);
    updateDateEdit = installLineEdit(400, 200, new QIntValidator);
    updateInvestmentEdit = installLineEdit(480, 200, new QIntValidator);
    updateWorthEdit = installLineEdit(560, 200);
    updateShareEdit = installLineEdit(640, 200);
    updateFeeEdit = installLineEdit(720,200);
    computeResultEdit = installLineEdit(700,300);
    baseInvestmentEdit = installLineEdit(400, 350, new QIntValidator);
    rateEdit = installLineEdit(480, 350);
    multEdit = installLineEdit(560, 350);
    powerEdit = installLineEdit(640, 350);

    multEdit->setText(QString::number(1,10));
    powerEdit->setText(QString::number(1,10));

    pathEdit = new QLineEdit(this);
    pathEdit->setGeometry(450, 430, 320, 20);
    pathEdit->setText(dbPath);

    addRecordButton = installButton(400, 80, QString("新建记录"));
    clearButton = installButton(520, 80, QString("清空"));
    searchButton = installButton(500, 145, QString("查询"));
    deleteButton = installButton(400, 220, QString("删除"));
    updateButton = installButton(520, 220, QString("更改"));
    updateClearButton = installButton(640, 220, QString("清空"));
    computeButton = installButton(500, 295, QString("开始计算"));
    importButton = installButton(400, 450, QString("导入数据"));
    exportButton = installButton(650, 450, QString("导出数据"));

    dateEdit->setText(QDate::currentDate().toString("yyyyMMdd"));

    initComputer();

    connect(addRecordButton, &QPushButton::clicked, this, &MainWindow::getAddRecordInput);
    connect(clearButton, &QPushButton::clicked, this, &MainWindow::clearAddRecordInput);
    connect(computeButton, &QPushButton::clicked, this, &MainWindow::computeInvestment);
}

void MainWindow::printAllRecord()
{
    for(int c = 0; c < 6; c++){
        cashTableWidget->item(0,c)->setText(headers[c]);
    }
    for(int i = 0; i < records.length(); i++)
        printARecord(i+1, records[i]);
}

void MainWindow::printARecord(int rowId, Record r)
{
    cashTableWidget->item(rowId, 0)->setText(QString::number(r.id,10));
    cashTableWidget->item(rowId, 1)->setText(QString::number(r.date,10));
    cashTableWidget->item(rowId, 2)->setText(QString::number(r.investment, 10));
    cashTableWidget->item(rowId, 3)->setText(QString::number(r.worth,10,4));
    cashTableWidget->item(rowId, 4)->setText(QString::number(r.share,10,2));
    cashTableWidget->item(rowId, 5)->setText(QString::number(r.fee,10,2));
}

void MainWindow::addNewRecord(Record r)
{
    recordNumber++;
    if(recordNumber < rowNumber)
        addNRow(20);

    printARecord(recordNumber, r);
}

void MainWindow::addNRow(int n)
{
    for(int r = 0;r < n; r++)
    {
        for(int c = 0; c < 6; c++)
        {
            QTableWidgetItem *item = new QTableWidgetItem;
            item->setFont(font);
            item->setTextAlignment(Qt::AlignCenter);
            item->setText("");
            cashTableWidget->setItem(r,c,item);
            cashTableWidget->setRowHeight(r, 30);
        }
    }
    rowNumber += n;
}

Record MainWindow::getAddRecordInput()
{
    Record r;
    r.id = recordNumber + 1;
    r.date = dateEdit->text().toInt();
    r.investment = investmentEdit->text().toInt();
    r.worth = worthEdit->text().toDouble();
    r.fee = feeEdit->text().toDouble();

    clearAddRecordInput();
    return r;
}


void MainWindow::clearAddRecordInput()
{
    dateEdit->setText(QDate::currentDate().toString("yyyyMMdd"));
    investmentEdit->setText("");
    worthEdit->setText("");
    shareEdit->setText("");
    feeEdit->setText("");
}

void MainWindow::installLabel(int x, int y, QString test)
{
    QLabel *tempLabel = new QLabel(this);
    tempLabel->setGeometry(x, y, labelHSize, labelVSize);
    tempLabel->setText(test);
}

QLineEdit *MainWindow::installLineEdit(int x, int y, QValidator *validator, int width, int height)
{
    QLineEdit *tempEdit = new QLineEdit(this);
    tempEdit->setGeometry(x,y,width, height);
    tempEdit->setValidator(validator);
    return tempEdit;
}

QPushButton *MainWindow::installButton(int x, int y, QString text)
{
    QPushButton *tempButton = new QPushButton(this);
    tempButton->setGeometry(x, y, buttonHSize, buttonVSize);
    tempButton->setText(text);
    return tempButton;
}

void MainWindow::computeInvestment()
{
    double baseInv = baseInvestmentEdit->text().toDouble();
    double rate = rateEdit->text().toDouble();
    double _mult = multEdit->text().toDouble();
    double _power = powerEdit->text().toDouble();

    double res = sumInvestment * (1 + rate);
    res = sumInvestment + baseInv - res;
    res = pow(_mult * res, _power);

    computeResultEdit->setText(QString::number(res, 10, 2));
}

void MainWindow::initComputer()
{
    baseInvestmentEdit->setText(QString::number(0,10));
    rateEdit->setText(QString::number(0,0));
    multEdit->setText(QString::number(1,10));
    powerEdit->setText(QString::number(1,10));
}
