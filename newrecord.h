#ifndef NEWRECORD_H
#define NEWRECORD_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QDateEdit>
#include <QValidator>
#include <QObject>

class NewRecord : public QObject
{
public:
    NewRecord(QWidget *parent);
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

    QPushButton *addNewRecord;
    QPushButton *clearButton;

    void getInput();
    void clearLineEdit();

signals:
    void sendRecord(QString date, int inv, double worth, double share, double fee);
};

#endif // NEWRECORD_H
