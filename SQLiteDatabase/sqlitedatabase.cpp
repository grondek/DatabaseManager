#include "sqlitedatabase.h"
#include "sqlitecreatedatabase.h"
#include "sqlitedbobject.h"
#include "dbdefaults.h"

#include <QtDebug>

SQLiteDatabase::SQLiteDatabase( QObject *parent ) :
    DBInterface( parent )
{
}

SQLiteDatabase::~SQLiteDatabase()
{
}

QIcon SQLiteDatabase::icon() const
{
    return QIcon( ":/sqlitedatabase/images/Sqlite-square-icon.svg" );
}

QString SQLiteDatabase::name() const
{
    return tr( "SQLite" );
}

QStringList SQLiteDatabase::objects() const
{
    return QStringList()
            << "database"
            << "table";
}

QStringList SQLiteDatabase::childObjects(const QString &parent_type) const
{
    return QStringList();
}

DB_OBJECT_TYPE_INFO SQLiteDatabase::objectTypeInfo(const QString &type) const
{
    return DB_OBJECT_TYPE_INFO();
}

DBObject *SQLiteDatabase::createObject(const QString &type, const QString &parent, const QVariantMap &parameters)
{
    if ( type == dbmanager::OBJECT_TYPE_DATABASE ) {
        SQLITEDBObject *obj = new SQLITEDBObject;
        QVariantMap::const_iterator it;
        for ( it = parameters.begin(); it != parameters.end(); ++it )
            obj->setProperty( it.key().toLocal8Bit(), it.value() );

        return obj;
    }

    return NULL;
}

QWidget *SQLiteDatabase::createObjectEditor(const QString &type, const QString &parent, QWidget *parentWidget)
{
    if ( type == "database" ) {
        SQLITECreateDatabase *creator = new SQLITECreateDatabase( parentWidget );
        connect( creator, SIGNAL(createObject(QString,QString,QVariantMap) ),
                 this, SLOT(slotCreateObject(QString,QString,QVariantMap) ) );
        return creator;
    }

    return NULL;
}

QWidget *SQLiteDatabase::createObjectEditor(DBObject *obj)
{
    return new QWidget();
}

void SQLiteDatabase::slotCreateObject(const QString &type, const QString &parent, const QVariantMap &params)
{
    DBObject *obj = createObject( type, parent, params );
    if ( obj )
        emit newObject( obj );
}
