#include "dbobject.h"

class DBObjectPrivate
{
public:
    QString name;
    QString parent;
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
