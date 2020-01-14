#ifndef MODEL_H
#define MODEL_H

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

#endif // MODEL_H
