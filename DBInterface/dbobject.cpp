#include "dbobject.h"

#include <QChildEvent>

#include <QtDebug>

class DBObjectPrivate
{
public:
    quint32 uid;
    QString name;
    quint32 parent;
    QIcon icon;

    static quint32 _nextuid;

    static quint32 nextuid()
    {
        return ++_nextuid;
    }
};

quint32 DBObjectPrivate::_nextuid = 0;

DBObject::DBObject(QObject *parent) :
    QObject(parent)
{
    _pd = new DBObjectPrivate;
    _pd->uid = DBObjectPrivate::nextuid();
}

DBObject::DBObject( quint32 uid, quint32 parentuid, QObject *parent ) :
    QObject(parent)
{
    _pd = new DBObjectPrivate;
    _pd->uid = uid;
    _pd->parent = parentuid;
}

DBObject::~DBObject()
{
    delete _pd;
}

quint32 DBObject::uid() const
{
    return _pd->uid;
}

void DBObject::setUid(quint32 uid)
{
    _pd->uid = uid;
}

QString DBObject::name() const
{
    return _pd->name;
}

void DBObject::setName(const QString &name)
{
    _pd->name = name;
}

quint32 DBObject::parentObject() const
{
    return _pd->parent;
}

void DBObject::setParentObject( quint32 pid )
{
    _pd->parent = pid;
}

QIcon DBObject::icon() const
{
    return _pd->icon;
}

void DBObject::setIcon(const QIcon &icon)
{
    _pd->icon = icon;
}

int DBObject::childCount() const
{
    int count = 0;
    foreach ( QObject *child, children() )
        if ( qobject_cast< DBObject* >( child ) )
            count++;

    return count;
}

QList<QAction *> DBObject::actions() const
{
    return QList<QAction *>();
}


void DBObject::childEvent(QChildEvent *event)
{
    QObject::childEvent( event );

    if ( event->added() && qobject_cast< DBObject* >( event->child() ) ) {
        DBObject *child = qobject_cast< DBObject* >( event->child() );
        connect( child, SIGNAL(execQuery(quint32,QString) ),
                 this, SLOT(exec(quint32,QString) )
                 );
    }
}

void DBObject::exec(quint32 senderuid, const QString &query)
{
}
