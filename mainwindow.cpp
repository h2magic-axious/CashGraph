#include "mainwindow.h"

MainWindow::MainWindow()
{

    resize(windowSize);
    setMaximumSize(windowSize);
    setMinimumSize(windowSize);

    cashTable = new GCashTable(this);
    cashTable->initTableWidget();

    newRecord = new NewRecord(this);

    //connect(newRecord, &NewRecord::sendRecord, cashTable, &GCashTable::addNewRecord);
}
