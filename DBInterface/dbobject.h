#ifndef DBOBJECT_H
#define DBOBJECT_H

#include <QObject>

class DBObject: public QObject
{
    Q_OBJECT
public:
    explicit DBObject(QObject *parent = 0);
    virtual ~DBObject();
};

#endif // DBOBJECT_H
