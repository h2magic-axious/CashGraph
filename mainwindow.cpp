#include "mainwindow.h"

MainWindow::MainWindow()
{
    resize(windowSize);
    setMaximumSize(windowSize);
    setMinimumSize(windowSize);

    tableHSize = 400;
    tableVSize = 600;
    itemHSize = tableHSize / 6;
    itemVSize = tableVSize / 20;
    font.setPixelSize(11);

    cashTableWidget = new QTableWidget(this);
    cashTableWidget->setGeometry(0,0,800,600);
    cashTableWidget->setRowCount(20);
    cashTableWidget->setColumnCount(6);
    cashTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    cashTableWidget->setSelectionMode(QAbstractItemView::NoSelection);
    cashTableWidget->horizontalHeader()->setVisible(false);
    cashTableWidget->horizontalHeader()->setDefaultSectionSize(tableHSize);
    cashTableWidget->horizontalHeader()->setHighlightSections(false);
    cashTableWidget->verticalHeader()->setVisible(false);
    cashTableWidget->verticalHeader()->setDefaultSectionSize(tableVSize);
    cashTableWidget->verticalHeader()->setHighlightSections(false);
    addNRow(20);

    for(int c = 0; c < 6; c++)
    {
        cashTableWidget->setColumnWidth(c, itemHSize);
        cashTableWidget->item(0,c)->setText(headers[c]);
    }

    int labelHSize = 58;
    int labelVSize = 16;
    int labelHDist = 80;

    int lineEditV = 50;
    int lineHSize = 65;
    int lineVSize = 20;

    QLabel *labelDate = new QLabel(this);
    labelDate->setGeometry(startX,startY, labelHSize, labelVSize);
    labelDate->setText(QString("日期"));
    dateEdit = new QLineEdit(this);
    dateEdit->setGeometry(startX,lineEditV,lineHSize, lineVSize);
    dateEdit->setValidator(new QIntValidator);

    QLabel *labelInvestment = new QLabel(this);
    labelInvestment->setGeometry(startX+labelHDist, startY, labelHSize,labelVSize);
    labelInvestment->setText(QString("投入"));
    investmentEdit = new QLineEdit(this);
    investmentEdit->setGeometry(startX+labelHDist,lineEditV,lineHSize, lineVSize);
    investmentEdit->setValidator(new QIntValidator);

    QLabel *labelWorth = new QLabel(this);
    labelWorth->setGeometry(startX+labelHDist*2, startY,labelHSize, labelVSize);
    labelWorth->setText(QString("净值"));
    worthEdit = new QLineEdit(this);
    worthEdit->setGeometry(startX+labelHDist*2, lineEditV, lineHSize, lineVSize);
    worthEdit->setValidator(new QDoubleValidator);

    QLabel *labelShare = new QLabel(this);
    labelShare->setGeometry(startX+labelHDist*3, startY,labelHSize,labelVSize);
    labelShare->setText(QString("份额"));
    shareEdit = new QLineEdit(this);
    shareEdit->setGeometry(startX+labelHDist*3, lineEditV, lineHSize, lineVSize);
    shareEdit->setValidator(new QDoubleValidator);

    QLabel *labelFee = new QLabel(this);
    labelFee->setGeometry(startX+labelHDist*4, startY, labelHSize, labelVSize);
    labelFee->setText(QString("手续费"));
    feeEdit = new QLineEdit(this);
    feeEdit->setGeometry(startX+labelHDist*4,lineEditV, lineHSize, lineVSize);
    feeEdit->setValidator(new QDoubleValidator);

    addRecordButton = new QPushButton(this);
    addRecordButton->setGeometry(startX,startY+50,90,30);
    addRecordButton->setText(QString("新建记录"));

    clearButton = new QPushButton(this);
    clearButton->setGeometry(startX + 290, startY+50, 90,30);
    clearButton->setText(QString("清空"));

    dateEdit->setText(QDate::currentDate().toString("yyyyMMdd"));

    connect(addRecordButton, &QPushButton::clicked, this, &MainWindow::getAddRecordInput);
    connect(clearButton, &QPushButton::clicked, this, &MainWindow::clearLineEdit);
}

void MainWindow::addNewRecord(QString date, int inv, double worth, double share, double fee)
{
    recordLength++;
    if(recordLength < rowNumber)
        addNRow(20);

    cashTableWidget->item(recordLength, 0)->setText(date);
    cashTableWidget->item(recordLength, 1)->setText(QString::number(inv,10));
    cashTableWidget->item(recordLength, 2)->setText(QString::number(worth, 10,4));
    cashTableWidget->item(recordLength, 3)->setText(QString::number(share,10,2));
    cashTableWidget->item(recordLength, 4)->setText(QString::number(fee,10,2));
    update();

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
                cashTableWidget->setRowHeight(r, itemVSize);
            }

        }
}

void MainWindow::getAddRecordInput()
{
    date = dateEdit->text();
    investment = investmentEdit->text().toInt();
    worth = worthEdit->text().toDouble();
    share = shareEdit->text().toDouble();
    fee = feeEdit->text().toDouble();

    //emit sendRecord(date, investment, worth, share, fee);
    clearLineEdit();
}

void MainWindow::clearLineEdit()
{
    dateEdit->setText(QDate::currentDate().toString("yyyyMMdd"));
    investmentEdit->setText("");
    worthEdit->setText("");
    shareEdit->setText("");
    feeEdit->setText("");
}
