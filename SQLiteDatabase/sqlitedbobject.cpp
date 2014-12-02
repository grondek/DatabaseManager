#include "sqlitedbobject.h"
#include "dbdefaults.h"
#include "sqlitedbdefaults.h"

#include <QAction>

#include <sqlite3.h>

#include <QtDebug>

class SQLITEDBObjectPrivate
{
public:
    QAction *action_connect;
    QAction *action_separator;
    QAction *action_remove;

    sqlite3 *dbhandler;

    QString errmsg;

    SQLITEDBObjectPrivate( SQLITEDBObject *parent ) :
        dbhandler( NULL )
    {
        action_connect = new QAction( parent );
        action_connect->setText( SQLITEDBObject::tr( "Connect" ) );
        parent->connect( action_connect, SIGNAL(triggered() ),
                 parent, SLOT(connectToDB() ) );

        action_separator = new QAction( parent );
        action_separator->setSeparator( true );

        action_remove = new QAction( parent );
        action_remove->setText( SQLITEDBObject::tr( "Remove" ) );
        parent->connect( action_remove, SIGNAL(triggered() ),
                 parent, SLOT(remove() ) );
    }

    ~SQLITEDBObjectPrivate()
    {
        close();

        action_connect->deleteLater();
        action_separator->deleteLater();
        action_remove->deleteLater();
    }

    int open( const char *filename, int flags )
    {
        errmsg.clear();

        int result = sqlite3_open_v2(
                    filename,
                    &dbhandler,
                    flags,
                    NULL
                    );

        if ( result != SQLITE_OK ) {
            errmsg = QString( sqlite3_errmsg( dbhandler ) );
            sqlite3_close_v2( dbhandler );
            dbhandler = NULL;
            return result;
        }

        return result;
    }

    void close()
    {
        if ( dbhandler ) {
            sqlite3_close_v2( dbhandler );
            dbhandler = NULL;
        }
    }
};

SQLITEDBObject::SQLITEDBObject( QObject *parent ) :
    DBObject( parent )
{
    setIcon( QIcon( ":/sqlitedatabase/images/Sqlite-square-icon.svg" ) );

    _pd = new SQLITEDBObjectPrivate( this );
}

SQLITEDBObject::~SQLITEDBObject()
{
    delete _pd;
}

QList<QAction *> SQLITEDBObject::actions() const
{
    return QList<QAction *>()
            << _pd->action_connect
            << _pd->action_separator
            << _pd->action_remove
            << _pd->action_separator;
}

void SQLITEDBObject::connectToDB()
{
    if ( _pd->dbhandler )
        return;

    qDebug() << "Connect to db";
    int flags = 0;

    if ( property( "create_if_not_exists" ).toBool() )
        flags |= SQLITE_OPEN_CREATE;
    if ( property( "rw_mode" ).toString() == QString( "rw" ) )
        flags |= SQLITE_OPEN_READWRITE;
    else
        flags |= SQLITE_OPEN_READONLY;

    if ( _pd->open( property( "filename" ).toByteArray(), flags ) != SQLITE_OK ) {
        //TODO show error message
        return;
    }

    QVariantMap params;
    params.insert( dbmanager::NAME_PROPERTY, tr( "Tables" ) );
    params.insert( dbmanager::PARENT_PROPERTY, uid() );
    emit addChild( sqlitedb::OBJECT_TYPE_SQLITE_GROUP_TABLES, uid(), params );

    /*
SELECT
  name, type
FROM
  sqlite_master
WHERE
  type in ('table', 'view')
  */

}

void SQLITEDBObject::remove()
{
    _pd->close();

    qDebug() << "Remove this";
}
