
#include "Model.h"

bool Server::tableCashExists()
{
    QSqlQuery query("SELECT COUNT(*) FROM sqlite_master WHERE type='table' AND name='cash'");
    if(query.next())
        if(query.value(0).toInt() > 0)
            return true;
    return false;
}

void Server::createCashTable()
{
    QSqlQuery query;
    query.exec("CREATE TABLE cash("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "date INTEGER(8),"
                    "investment INTEGER,"
                    "worth REAL,"
                    "share REAL,"
                    "fee REAL);");
}

void Server::insert(Record r)
{
    QSqlQuery query;
    query.prepare("INSERT INTO cash VALUES("
                    "NULL,:date, :investment, :worth, :share, :fee);");
    query.bindValue(":date", r.date);
    query.bindValue(":investment", r.investment);
    query.bindValue(":worth", r.worth);
    query.bindValue(":share", r.share);
    query.bindValue(":fee", r.fee);
    query.exec();
}

void Server::deleteWithId(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM cash WHERE id=:id");
    query.bindValue(":id", id);
    query.exec();
}

void Server::updateWithRecord(Record r)
{
    if(r.id == -1)
    {
        insert(r);
        return;
    }

    QSqlQuery query;
    query.prepare("UPDATE cash SET date=:d, investment=:inv, worth=:w, share=:s, fee=:f WHERE id=:i");
    query.bindValue(":d", r.date);
    query.bindValue(":inv", r.investment);
    query.bindValue(":w", r.worth);
    query.bindValue(":s", r.share);
    query.bindValue(":f", r.fee);
    query.bindValue(":i", r.id);
    query.exec();
}

bool Server::searchWithId(int id, Record *r)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM cash WHERE id=:id");
    query.bindValue(":id", id);
    query.exec();

    if(query.next())
    {
        *r = queryToRecord(query);
        return r->id == id;
    }

    return false;
}

void Server::searchWithDate(int date, Record *r)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM cash WHERE date=:date");
    query.bindValue(":date", date);
    query.exec();

    if(query.next())
    {
        *r = queryToRecord(query);
    }
}

void Server::searchAll(RecordList *rList)
{
    rList->clear();

    QSqlQuery query("SELECT * FROM cash");
    while(query.next())
    {
        Record rTemp = queryToRecord(query);
        *rList << rTemp;
    }
}

Record Server::queryToRecord(QSqlQuery &q)
{
    int id = q.value("id").toInt();
    int date = q.value("date").toInt();
    int inv = q.value("investment").toInt();
    double worth = q.value("worth").toDouble();
    double share = q.value("share").toDouble();
    double fee = q.value("fee").toDouble();

    Record rTemp(date, inv, worth, share, fee);
    rTemp.id = id;
    return rTemp;
}
