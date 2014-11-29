#ifndef SQLITEDBOBJECT_H
#define SQLITEDBOBJECT_H

#include "dbobject.h"

class QAction;

class SQLITEDBObject : public DBObject
{
    Q_OBJECT
private:
    QAction *m_action_connect;
    QAction *m_action_separator;
    QAction *m_action_remove;
public:
    explicit SQLITEDBObject( QObject *parent = NULL );
    virtual ~SQLITEDBObject();

    virtual QList< QAction *> actions() const;
private slots:
    void connectToDB();
    void remove();
};

#endif // SQLITEDBOBJECT_H
