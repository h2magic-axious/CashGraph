#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QSize>
#include <QObject>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QDate>

class MainWindow : public  QWidget{
    Q_OBJECT
    QSize windowSize = QSize(800,600);

    QTableWidget *cashTableWidget;
    QString headers[6] = {QString("Id"), QString("日期"),QString("投入"),QString("净值"),QString("份额"),QString("手续费")};
    int tableHSize;
    int tableVSize;
    int itemHSize;
    int itemVSize;

    QFont font;

    int recordLength = 1;
    int rowNumber = 20;

    void addNewRecord(QString date, int inv, double worth, double share, double fee);
    void addNRow(int n);


    int newHSize;
    int newVSize;
    int startX = 400;
    int startY = 30;

    QLineEdit *dateEdit;
    QString date;

    QLineEdit *investmentEdit;
    int investment;

    QLineEdit *worthEdit;
    double worth;

    QLineEdit *shareEdit;
    double share;

    QLineEdit *feeEdit;
    double fee;

    QPushButton *addRecordButton;
    QPushButton *clearButton;

    void getAddRecordInput();
    void clearLineEdit();

signals:
    void sendRecord(QString date, int inv, double worth, double share, double fee);

public:
    MainWindow();
    ~MainWindow() = default;
};


#endif // MAINWINDOW_H
