#include "sqlitegroupobject.h"

class SQLITEGroupObjectPrivate
{
public:
    QString query;
};

SQLITEGroupObject::SQLITEGroupObject(QObject *parent) :
    DBObject(parent)
{
    _pd = new SQLITEGroupObjectPrivate;
}

SQLITEGroupObject::~SQLITEGroupObject()
{
    delete _pd;
}

void SQLITEGroupObject::setGetChildQuery(const QString &query)
{
    _pd->query = query;
}
