#ifndef SQLITEDBOBJECT_H
#define SQLITEDBOBJECT_H

#include "dbobject.h"

class SQLITEDBObjectPrivate;

class SQLITEDBObject : public DBObject
{
    Q_OBJECT
private:
    SQLITEDBObjectPrivate *_pd;
public:
    explicit SQLITEDBObject( QObject *parent = NULL );
    virtual ~SQLITEDBObject();

    virtual QList< QAction *> actions() const;
private slots:
    void connectToDB();
    void remove();
};

#endif // SQLITEDBOBJECT_H
