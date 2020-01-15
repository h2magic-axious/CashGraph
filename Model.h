#ifndef MODEL_H
#define MODEL_H

#include<QList>
#include<QString>
#include<QDebug>
#include <QObject>

#include<QFileInfo>
#include<QDir>
#include<QFile>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

#include "QMainWindow"

class Record
{
public:
    int id = -1;
    int date;
    int investment;
    double worth;
    double share;
    double fee;

    Record(int d, int inv, double w, double s, double f):
        date(d),investment(inv),worth(w),share(s),fee(f){}
    Record():date(0),investment(0),worth(0),share(0),fee(0){}
    ~Record() = default;

    bool operator==(const int d) {return date == d;}

    QString stringId(){return QString::number(id,10);}
    QString stringDate(){ return QString::number(date, 10); }
    QString stringInv(){ return QString::number(investment, 10); }
    QString stringWorth(){ return QString::number(worth, 10, 4); }
    QString stringShare(){ return QString::number(share, 10, 2); }
    QString stringFee(){ return QString::number(fee, 10, 2); }
};

typedef QList<Record> RecordList;

class Server : public QObject
{
    Q_OBJECT
public:
    Server(QString sfp):saveFilePath(sfp){
        session = QSqlDatabase::addDatabase("QSQLITE");

        QString currentDir = QDir::currentPath();
        absFilePath = linkPath(currentDir, saveFilePath);

        initSession();
    }
    ~Server(){
        session.close();
    }

    void initSession()
    {
        session.setDatabaseName(absFilePath);

        if(session.open())
        {
            if(!tableCashExists())
                createCashTable();
        }
    }

    bool tableCashExists();
    void createCashTable();
    QString linkPath(QString root, QString filePath){ return root + '/' + filePath; }
    void insert(Record r);
    void deleteWithId(int id);
    void updateWithRecord(Record r);
    bool searchWithId(int id, Record *r);
    void searchWithDate(int date, Record *r);
    void searchAll(RecordList *rList);
    Record queryToRecord(QSqlQuery &q);

    void setFilePath(QString filePath)
    {
        saveFilePath = filePath;
        absFilePath = filePath;
        initSession();
    }

    QString saveFilePath;
    QString absFilePath;
    QSqlDatabase session;

signals:
    void sendMessage(const QString &msg);
};

#endif // MODEL_H
