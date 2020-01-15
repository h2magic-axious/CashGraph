#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QValidator>
#include <QTableWidgetItem>
#include <QDate>
#include <QDateTime>
#include <QDialog>
#include <QObject>

#include <QDebug>
#include <cmath>

#include "Model.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_updateSumButton_clicked();

    void on_addNewRecordButton_clicked();

    void on_addClearButton_clicked();

    void on_searchFromIDButton_clicked();

    void on_updateClearButton_clicked();

    void on_deleteRecordButton_clicked();

    void on_updateRecordButton_clicked();

    void on_computeClearButton_clicked();

    void on_computeButton_clicked();

    void on_exportButton_clicked();

    void on_exportButton_2_clicked();

private:
    int rowNumber = 0;
    int tableHSize = 30;
    int tableItemVSize[6] = {50,80,80,80,80,50};
    int memorySearch = -1;

    QFont font;
    RecordList recordList;

    QString configFilePath = "/opt/CashGraph/config.ini";
    QString DataKey = "DATA_BASE_FILE";

    QSettings *setting;

    Server *server;
    Ui::MainWindow *ui;
    QValidator *OnlyInt = new QIntValidator;
    QValidator *OnlyDouble = new QDoubleValidator;

    void addRow(int n=20);

    QTableWidgetItem *newItem();

    void initTableDisplay();

    void insertOneRecord(int row, Record record);

    void clearTable();

    void displayAllRecord();

    inline QString dateToInteger(QDate date);

    QString getText(QLineEdit *lineEdit);

    Record csvGetWithId(int id);

    void setTCOrder();

    void initConfig();

public slots:
    void printMessage(const QString& msg);

};
#endif // MAINWINDOW_H
