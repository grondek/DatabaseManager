#include "sqlitedbobject.h"

SQLITEDBObject::SQLITEDBObject( QObject *parent ) :
    DBObject( parent )
{
    setIcon( QIcon( ":/sqlitedatabase/images/Sqlite-square-icon.svg" ) );
}

SQLITEDBObject::~SQLITEDBObject()
{
}
