#ifndef MODEL_H
#define MODEL_H

#include<QList>
#include<QString>
#include<QStringList>

#include<QDebug>
#include<QObject>
#include<QFileInfo>
#include<QDir>
#include<QFile>
#include<QSettings>
#include<QMap>


#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

#include "QMainWindow"

typedef QMap<QString, QString> DictSS;

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
    QString stringDate()
    {
        // 20180101 [0-4][4-6][6]
        QString dTemp = QString::number(date, 10);
        QString year = dTemp.mid(0,4);
        QString month = dTemp.mid(4,2);
        QString day = dTemp.mid(6);
        return year + '-' + month + '-' + day;
    }
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

        initSession();
    }
    ~Server(){
        session.close();
    }

    void initSession()
    {
        session.setDatabaseName(saveFilePath);

        if(session.open())
        {
            if(!tableCashExists())
                createCashTable();
        }
    }

    bool tableCashExists();
    void createCashTable();
    void insert(Record r);
    void deleteWithId(int id);
    void updateWithRecord(Record r);
    bool searchWithId(int id, Record *r);
    void searchWithDate(int date, Record *r);
    void searchAll(RecordList *rList);
    Record queryToRecord(QSqlQuery &q);
    QString linkPath(QString root, QString filePath){ return root + '/' + filePath; }
    void setFilePath(QString filePath)
    {
        saveFilePath = filePath;
        initSession();
    }

    QString saveFilePath;
    QSqlDatabase session;

signals:
    void sendMessage(const QString &msg);
};

#endif // MODEL_H
