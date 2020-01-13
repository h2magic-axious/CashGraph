#ifndef GCASHTABLE_H
#define GCASHTABLE_H

#include <QTableWidget>
#include <QAbstractItemView>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <QFont>
#include <QObject>

class GCashTable
{
    //Q_OBJECT
public:
    QTableWidget *cashTableWidget;
    QString headers[6] = {QString("Id"), QString("日期"),QString("投入"),QString("净值"),QString("份额"),QString("手续费")};
    int tableHSize;
    int tableVSize;
    int itemHSize;
    int itemVSize;

    QFont font;

    int recordLength = 1;
    int rowNumber = 20;
    GCashTable(QWidget *parent);

    void initTableWidget();
    void addNewRecord(QString date, int inv, double worth, double share, double fee);
    void addNRow(int n);
};

#endif // GCASHTABLE_H
