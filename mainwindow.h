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

#include <QList>

class Record{
public:
    int id;
    int date;
    int investment;
    double worth;
    double share;
    double fee;
};

typedef QList<Record> RecordList;

class MainWindow : public  QWidget{
    Q_OBJECT
    QSize windowSize = QSize(800,600);

    QTableWidget *cashTableWidget;
    QString headers[6] = {QString("Id"), QString("日期"),QString("投入"),QString("净值"),QString("份额"),QString("手续费")};

    QFont font;
    RecordList records;

    int recordNumber = 0;
    int rowNumber = 20;

    int buttonHSize = 100;
    int buttonVSize = 30;

    int labelHSize = 60;
    int labelVSize = 16;

    QString dbPath;

    QLineEdit *dateEdit;
    QLineEdit *investmentEdit;
    QLineEdit *worthEdit;
    QLineEdit *shareEdit;
    QLineEdit *feeEdit;
    QLineEdit *identEdit;
    QLineEdit *updateDateEdit;
    QLineEdit *updateInvestmentEdit;
    QLineEdit *updateWorthEdit;
    QLineEdit *updateShareEdit;
    QLineEdit *updateFeeEdit;
    QLineEdit *computeResultEdit;
    QLineEdit *baseInvestmentEdit;
    QLineEdit *rateEdit;
    QLineEdit *multEdit;
    QLineEdit *powerEdit;
    QLineEdit *pathEdit;

    QPushButton *addRecordButton;
    QPushButton *clearButton;
    QPushButton *searchButton;
    QPushButton *deleteButton;
    QPushButton *updateButton;
    QPushButton *updateClearButton;
    QPushButton *computeButton;
    QPushButton *importButton;
    QPushButton *exportButton;

public:
    MainWindow();
    ~MainWindow(){

    }

    void printAllRecord();
    void printARecord(int rowId, Record r);

    void addNewRecord(Record r);
    void addNRow(int n);

    Record getAddRecordInput();
    void clearAddRecordInput();

    void installLabel(int x, int y, QString test);
    QLineEdit* installLineEdit(int x, int y, QValidator *validator = new QDoubleValidator, int width=65,int height=20);
    QPushButton* installButton(int x, int y, QString text);
};


#endif // MAINWINDOW_H
