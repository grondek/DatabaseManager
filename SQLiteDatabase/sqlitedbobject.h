#ifndef SQLITEDBOBJECT_H
#define SQLITEDBOBJECT_H

#include "dbobject.h"

class SQLITEDBObject : public DBObject
{
    Q_OBJECT
public:
    explicit SQLITEDBObject( QObject *parent = NULL );
    virtual ~SQLITEDBObject();
};

#endif // SQLITEDBOBJECT_H
