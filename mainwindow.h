#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QSize>
#include <QObject>

#include "gcashtable.h"
#include "newrecord.h"

class MainWindow : public  QWidget{
    Q_OBJECT
    QSize windowSize = QSize(800,600);

    GCashTable *cashTable;
    NewRecord *newRecord;
public:
    MainWindow();
    ~MainWindow() = default;
};


#endif // MAINWINDOW_H
