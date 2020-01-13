#include "gcashtable.h"

GCashTable::GCashTable(QWidget *parent)
{
    QTableWidget *cashTable = new QTableWidget(parent);
    tableHSize = 400;
    tableVSize = 600;
    itemHSize = tableHSize / 6;
    itemVSize = tableVSize / 20;

    cashTable->setGeometry(0,0,800,600);
    cashTable->setRowCount(20);
    cashTable->setColumnCount(6);
    cashTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    cashTable->setSelectionMode(QAbstractItemView::NoSelection);

    QHeaderView *h = cashTable->horizontalHeader();
    h->setVisible(false);
    h->setDefaultSectionSize(tableHSize);
    h->setHighlightSections(false);

    QHeaderView *v = cashTable->verticalHeader();
    v->setVisible(false);
    v->setDefaultSectionSize(tableVSize);
    v->setHighlightSections(false);

    font.setPixelSize(11);

    for(int c=0;c<6;c++)
        cashTable->setColumnWidth(c, itemHSize);

    cashTableWidget = cashTable;
    addNRow(20);
}

void GCashTable::initTableWidget()
{
    for(int c=0;c<6;c++){
        cashTableWidget->item(0,c)->setText(headers[c]);
    }
}

void GCashTable::addNewRecord(QString date, int inv, double worth, double share, double fee)
{
    recordLength++;
    if(recordLength < rowNumber)
        addNRow(20);
    cashTableWidget->item(recordLength, 0)->setText(date);
    cashTableWidget->item(recordLength, 1)->setText(QString::number(inv,10));
    cashTableWidget->item(recordLength, 2)->setText(QString::number(worth, 10,4));
    cashTableWidget->item(recordLength, 3)->setText(QString::number(share,10,2));
    cashTableWidget->item(recordLength, 4)->setText(QString::number(fee,10,2));

}

void GCashTable::addNRow(int n)
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
