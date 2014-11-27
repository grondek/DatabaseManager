#include "dbobject.h"

class DBObjectPrivate
{
public:
    quint32 uid;
    QString name;
    QString parent;
    QIcon icon;
};

DBObject::DBObject(QObject *parent) :
    QObject(parent)
{
    _pd = new DBObjectPrivate;
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

QString DBObject::parentObject() const
{
    return _pd->parent;
}

void DBObject::setParentObject(const QString &pid)
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
