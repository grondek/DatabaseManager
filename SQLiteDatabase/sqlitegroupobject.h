#ifndef SQLITEGROUPOBJECT_H
#define SQLITEGROUPOBJECT_H

#include "dbobject.h"

class SQLITEGroupObjectPrivate;

class SQLITEGroupObject : public DBObject
{
    Q_OBJECT
private:
    SQLITEGroupObjectPrivate *_pd;
public:
    explicit SQLITEGroupObject(QObject *parent = 0);
    virtual ~SQLITEGroupObject();

    void setGetChildQuery( const QString &query );
};

#endif // SQLITEGROUPOBJECT_H
