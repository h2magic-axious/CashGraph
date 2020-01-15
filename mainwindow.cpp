#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->configFilePathLineEdit->setText(configFilePath);
    initConfig();
    font.setPixelSize(11);

    QString dbFilePath = setting->value("DATA_BASE_FILE", "没有找到配置文件").toString();
    server = new Server(dbFilePath);

    setTCOrder();

    ui->newDateEdit->setValidator(OnlyInt);
    ui->newDateEdit->setText(dateToInteger(QDate::currentDate()));

    ui->newInvestmentEdit->setValidator(OnlyInt);
    ui->newWorthEdit->setValidator(OnlyDouble);
    ui->newShareEdit->setValidator(OnlyDouble);
    ui->newFeeEdit->setValidator(OnlyDouble);

    ui->updateIDEdit->setValidator(OnlyInt);
    ui->updateDateEdit->setValidator(OnlyInt);
    ui->updateInvestmentEdit->setValidator(OnlyInt);
    ui->updateWorthEdit->setValidator(OnlyDouble);
    ui->updateShareEdit->setValidator(OnlyDouble);
    ui->updateFeeEdit->setValidator(OnlyDouble);

    ui->computeBaseEdit->setValidator(OnlyInt);
    ui->computeRateEdit->setValidator(OnlyDouble);
    ui->computeMultEdit->setValidator(OnlyDouble);
    ui->computePowEdit->setValidator(OnlyDouble);

    for(int c = 0; c < 6; c++)
        ui->tableWidget->setColumnWidth(c, tableItemVSize[c]);

    ui->filePathEdit->setText(server->saveFilePath);

    server->searchAll(&recordList);

    printMessage("程序打开成功");

    addRow();

    displayAllRecord();
    on_updateSumButton_clicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addRow(int n)
{
    ui->tableWidget->setRowCount(rowNumber + n);

    for (int r = 0; r < n; r++) {
        ui->tableWidget->setRowHeight(r, tableHSize);
        for (int c = 0; c < 6; c++)
            ui->tableWidget->setItem(r + rowNumber, c, newItem());
    }
    rowNumber += n;
}

QTableWidgetItem *MainWindow::newItem()
{
    QTableWidgetItem *item = new QTableWidgetItem;
    item->setFont(font);
    item->setTextAlignment(Qt::AlignCenter);
    return item;
}

void MainWindow::initTableDisplay()
{
    ui->tableWidget->item(0,0)->setText(QString("ID"));
    ui->tableWidget->item(0,1)->setText(QString("日期"));
    ui->tableWidget->item(0,2)->setText(QString("投入"));
    ui->tableWidget->item(0,3)->setText(QString("净值"));
    ui->tableWidget->item(0,4)->setText(QString("份额"));
    ui->tableWidget->item(0,5)->setText(QString("手续费"));
}

void MainWindow::insertOneRecord(int row, Record record)
{
    ui->tableWidget->item(row, 0)->setText(record.stringId());
    ui->tableWidget->item(row, 1)->setText(record.stringDate());
    ui->tableWidget->item(row, 2)->setText(record.stringInv());
    ui->tableWidget->item(row, 3)->setText(record.stringWorth());
    ui->tableWidget->item(row, 4)->setText(record.stringShare());
    ui->tableWidget->item(row, 5)->setText(record.stringFee());
}

void MainWindow::clearTable()
{
    for(int r = 0; r < rowNumber; r++)
        for(int c = 0; c < 6; c++)
            ui->tableWidget->item(r, c)->setText(QString(""));
}

void MainWindow::displayAllRecord()
{
    recordList.clear();
    server->searchAll(&recordList);
    clearTable();
    initTableDisplay();
    int length = recordList.length();

    if(rowNumber < length)
        addRow(length - rowNumber + 20);

    for(int i = 0; i < length; i++)
        insertOneRecord(i + 1, recordList[i]);

    printMessage("表格更新完成");
    on_addClearButton_clicked();
}

QString MainWindow::dateToInteger(QDate date)
{
    return date.toString("yyyyMMdd");
}

QString MainWindow::getText(QLineEdit *lineEdit)
{
    QString temp = lineEdit->text();
    return temp;
}

void MainWindow::setTCOrder()
{
    QWidget::setTabOrder(ui->newDateEdit, ui->newInvestmentEdit);
    QWidget::setTabOrder(ui->newInvestmentEdit, ui->newWorthEdit);
    QWidget::setTabOrder(ui->newWorthEdit, ui->newShareEdit);
    QWidget::setTabOrder(ui->newShareEdit, ui->newFeeEdit);
    QWidget::setTabOrder(ui->newFeeEdit, ui->updateIDEdit);
    QWidget::setTabOrder(ui->updateIDEdit, ui->updateDateEdit);
    QWidget::setTabOrder(ui->updateDateEdit, ui->updateInvestmentEdit);
    QWidget::setTabOrder(ui->updateInvestmentEdit, ui->updateWorthEdit);
    QWidget::setTabOrder(ui->updateWorthEdit, ui->updateShareEdit);
    QWidget::setTabOrder(ui->updateShareEdit, ui->updateFeeEdit);
    QWidget::setTabOrder(ui->updateFeeEdit, ui->computeBaseEdit);
    QWidget::setTabOrder(ui->computeBaseEdit, ui->computeRateEdit);
    QWidget::setTabOrder(ui->computeRateEdit, ui->computeMultEdit);
    QWidget::setTabOrder(ui->computeMultEdit, ui->computePowEdit);
    QWidget::setTabOrder(ui->computePowEdit, ui->filePathEdit);
}

void MainWindow::initConfig()
{
    qDebug() << "In initConfig()";
    setting = new QSettings(configFilePath, QSettings::IniFormat);
    printMessage("配置文件已找到");
}

void MainWindow::printMessage(const QString& msg)
{

    ui->logBrowser->insertPlainText(msg + "\n\n");
    ui->logBrowser->moveCursor(QTextCursor::Start);
    ui->logBrowser->insertPlainText(QDateTime::currentDateTime().toString("[yyyy-MM-dd] hh:mm:ss") + '\n');
    ui->logBrowser->moveCursor(QTextCursor::Start);
}

void MainWindow::on_updateSumButton_clicked()
{
    int sumInvestment = 0;
    double sumShare = 0.0;
    double sumFee = 0.0;

    recordList.clear();
    server->searchAll(&recordList);

    for (int i = 0; i < recordList.length(); i++) {
        Record r = recordList[i];
        sumInvestment += r.investment;
        sumShare += r.share;
        sumFee += r.fee;
    }

    ui->sumInvestmentEdit->setText(QString::number(sumInvestment,10));
    ui->sumShareEdit->setText(QString::number(sumShare, 10, 4));
    ui->sumFeeEdit->setText(QString::number(sumFee, 10, 2));

    printMessage("统计完成");
}

void MainWindow::on_addNewRecordButton_clicked()
{
    int date = getText(ui->newDateEdit).toInt();
    int investment = getText(ui->newInvestmentEdit).toInt();
    double worth = getText(ui->newWorthEdit).toDouble();
    double share = getText(ui->newShareEdit).toDouble();
    double fee = getText(ui->newFeeEdit).toDouble();

    on_addClearButton_clicked();
    on_updateSumButton_clicked();

    server->insert(Record(date, investment, worth, share, fee));
    printMessage("添加记录 完成");
    displayAllRecord();
}

void MainWindow::on_addClearButton_clicked()
{
    ui->newDateEdit->setText(dateToInteger(QDate::currentDate()));
    ui->newInvestmentEdit->clear();
    ui->newWorthEdit->clear();
    ui->newShareEdit->clear();
    ui->newFeeEdit->clear();
}

void MainWindow::on_searchFromIDButton_clicked()
{
    int id = getText(ui->updateIDEdit).toInt();
    Record r;
    ui->updateIDEdit->clear();

    if(server->searchWithId(id, &r))
    {
        printMessage("查找成功");
        memorySearch = id;
        ui->updateInvestmentEdit->setText(r.stringInv());
        ui->updateWorthEdit->setText(r.stringWorth());
        ui->updateShareEdit->setText(r.stringShare());
        ui->updateFeeEdit->setText(r.stringFee());
        ui->updateDateEdit->setText(r.stringDate());
    }
    else
    {
        printMessage("查找失败");
        memorySearch = -1;
        on_updateClearButton_clicked();
    }
}

void MainWindow::on_updateClearButton_clicked()
{
    ui->updateIDEdit->clear();
    ui->updateDateEdit->clear();
    ui->updateInvestmentEdit->clear();
    ui->updateWorthEdit->clear();
    ui->updateShareEdit->clear();
    ui->updateFeeEdit->clear();
    memorySearch = -1;
}

void MainWindow::on_deleteRecordButton_clicked()
{
    if(memorySearch != -1)
    {
        server->deleteWithId(memorySearch);
        printMessage("记录已删除");
        displayAllRecord();
    }
    else
    {
        printMessage("未找到记录");
    }

    memorySearch = -1;
    on_updateClearButton_clicked();
}

void MainWindow::on_updateRecordButton_clicked()
{
    Record r;
    server->searchWithId(memorySearch, &r);

    r.date = getText(ui->updateDateEdit).toInt();
    r.investment = getText(ui->updateInvestmentEdit).toInt();
    r.worth = getText(ui->updateWorthEdit).toDouble();
    r.share = getText(ui->updateShareEdit).toDouble();
    r.fee = getText(ui->updateFeeEdit).toDouble();

    server->updateWithRecord(r);

    printMessage("更改成功");
    memorySearch = -1;

    on_updateClearButton_clicked();
    displayAllRecord();
}

void MainWindow::on_computeClearButton_clicked()
{
    ui->computeBaseEdit->clear();
    ui->computeRateEdit->clear();
    ui->computeMultEdit->setText("1");
    ui->computePowEdit->setText("1");
    ui->computeResultEdit->clear();
}

void MainWindow::on_computeButton_clicked()
{
    double baseInv = getText(ui->computeBaseEdit).toDouble();
    double rate = getText(ui->computeRateEdit).toDouble();
    double mult = getText(ui->computeMultEdit).toDouble();
    double power = getText(ui->computePowEdit).toDouble();

    double inv = getText(ui->sumInvestmentEdit).toDouble();
    double fee = getText(ui->sumFeeEdit).toDouble();

    double realRate = 1 - rate * (inv - fee) / baseInv;
    double result = baseInv * pow(mult * realRate, power);

    if(result <= 0)
        result = 0;

    ui->computeResultEdit->setText(QString::number(result,10,2));
}

void MainWindow::on_exportButton_clicked()
{
    server->setFilePath(ui->filePathEdit->text());
    printMessage("数据载入完成");
    displayAllRecord();
}

void MainWindow::on_exportButton_2_clicked()
{
    configFilePath = ui->configFilePathLineEdit->text();
    initConfig();
    QString dbFilePath = setting->value(DataKey).toString();
    ui->filePathEdit->setText(dbFilePath);
    printMessage("配置载入完成");
    on_exportButton_clicked();
}
