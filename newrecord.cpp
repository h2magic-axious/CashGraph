#include "newrecord.h"

NewRecord::NewRecord(QWidget *parent)
{
    int labelHSize = 58;
    int labelVSize = 16;
    int labelHDist = 80;

    int lineEditV = 50;
    int lineHSize = 65;
    int lineVSize = 20;

    QLabel *labelDate = new QLabel(parent);
    labelDate->setGeometry(startX,startY, labelHSize, labelVSize);
    labelDate->setText(QString("日期"));
    dateEdit = new QLineEdit(parent);
    dateEdit->setGeometry(startX,lineEditV,lineHSize, lineVSize);
    dateEdit->setValidator(new QIntValidator);

    QLabel *labelInvestment = new QLabel(parent);
    labelInvestment->setGeometry(startX+labelHDist, startY, labelHSize,labelVSize);
    labelInvestment->setText(QString("投入"));
    investmentEdit = new QLineEdit(parent);
    investmentEdit->setGeometry(startX+labelHDist,lineEditV,lineHSize, lineVSize);
    investmentEdit->setValidator(new QIntValidator);

    QLabel *labelWorth = new QLabel(parent);
    labelWorth->setGeometry(startX+labelHDist*2, startY,labelHSize, labelVSize);
    labelWorth->setText(QString("净值"));
    worthEdit = new QLineEdit(parent);
    worthEdit->setGeometry(startX+labelHDist*2, lineEditV, lineHSize, lineVSize);
    worthEdit->setValidator(new QDoubleValidator);

    QLabel *labelShare = new QLabel(parent);
    labelShare->setGeometry(startX+labelHDist*3, startY,labelHSize,labelVSize);
    labelShare->setText(QString("份额"));
    shareEdit = new QLineEdit(parent);
    shareEdit->setGeometry(startX+labelHDist*3, lineEditV, lineHSize, lineVSize);
    shareEdit->setValidator(new QDoubleValidator);

    QLabel *labelFee = new QLabel(parent);
    labelFee->setGeometry(startX+labelHDist*4, startY, labelHSize, labelVSize);
    labelFee->setText(QString("手续费"));
    feeEdit = new QLineEdit(parent);
    feeEdit->setGeometry(startX+labelHDist*4,lineEditV, lineHSize, lineVSize);
    feeEdit->setValidator(new QDoubleValidator);

    addNewRecord = new QPushButton(parent);
    addNewRecord->setGeometry(startX,startY+50,90,30);
    addNewRecord->setText(QString("新建记录"));

    clearButton = new QPushButton(parent);
    clearButton->setGeometry(startX + 290, startY+50, 90,30);
    clearButton->setText(QString("清空"));

    dateEdit->setText(QDate::currentDate().toString("yyyyMMdd"));

    connect(addNewRecord, &QPushButton::clicked, this, &NewRecord::getInput);
    connect(clearButton, &QPushButton::clicked, this, &NewRecord::clearLineEdit);
}

void NewRecord::getInput()
{
    date = dateEdit->text();
    investment = investmentEdit->text().toInt();
    worth = worthEdit->text().toDouble();
    share = shareEdit->text().toDouble();
    fee = feeEdit->text().toDouble();

    //emit sendRecord(date, investment, worth, share, fee);
    clearLineEdit();
}

void NewRecord::clearLineEdit()
{
    dateEdit->setText(QDate::currentDate().toString("yyyyMMdd"));
    investmentEdit->setText("");
    worthEdit->setText("");
    shareEdit->setText("");
    feeEdit->setText("");
}
