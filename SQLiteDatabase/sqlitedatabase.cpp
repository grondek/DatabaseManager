#include "sqlitedatabase.h"
#include "sqlitecreatedatabase.h"
#include "sqlitedbobject.h"
#include "sqlitegroupobject.h"
#include "dbdefaults.h"
#include "sqlitedbdefaults.h"

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

DBObject *SQLiteDatabase::createObject(const QString &type, quint32 parent, const QVariantMap &parameters)
{
    if ( type == dbmanager::OBJECT_TYPE_DATABASE ) {
        SQLITEDBObject *obj = new SQLITEDBObject;
        obj->setParentObject( parent );

        QVariantMap::const_iterator it;
        for ( it = parameters.begin(); it != parameters.end(); ++it )
            obj->setProperty( it.key().toLocal8Bit(), it.value() );

        connect( obj, SIGNAL(addChild(QString,quint32,QVariantMap) ),
                 this, SLOT(slotCreateObject(QString,quint32,QVariantMap) ) );

        return obj;
    }

    if ( type == sqlitedb::OBJECT_TYPE_SQLITE_GROUP_TABLES ) {
        SQLITEGroupObject *obj = new SQLITEGroupObject;
        obj->setParentObject( parent );

        QVariantMap::const_iterator it;
        for ( it = parameters.begin(); it != parameters.end(); ++it )
            obj->setProperty( it.key().toLocal8Bit(), it.value() );

        connect( obj, SIGNAL(addChild(QString,quint32,QVariantMap) ),
                 this, SLOT(slotCreateObject(QString,quint32,QVariantMap) ) );

        return obj;
    }

    if ( type == sqlitedb::OBJECT_TYPE_SQLITE_GROUP_VIEWS ) {
        SQLITEGroupObject *obj = new SQLITEGroupObject;
        obj->setParentObject( parent );

        QVariantMap::const_iterator it;
        for ( it = parameters.begin(); it != parameters.end(); ++it )
            obj->setProperty( it.key().toLocal8Bit(), it.value() );

        connect( obj, SIGNAL(addChild(QString,quint32,QVariantMap) ),
                 this, SLOT(slotCreateObject(QString,quint32,QVariantMap) ) );

        return obj;
    }

    return NULL;
}

QWidget *SQLiteDatabase::createObjectEditor(const QString &type, quint32 parent, QWidget *parentWidget)
{
    if ( type == dbmanager::OBJECT_TYPE_DATABASE  ) {
        SQLITECreateDatabase *creator = new SQLITECreateDatabase( parentWidget );
        connect( creator, SIGNAL(createObject(QString,quint32,QVariantMap) ),
                 this, SLOT(slotCreateObject(QString,quint32,QVariantMap) ) );
        return creator;
    }

    return NULL;
}

QWidget *SQLiteDatabase::createObjectEditor(DBObject *obj)
{
    return new QWidget();
}

void SQLiteDatabase::slotCreateObject(const QString &type, quint32 parent, const QVariantMap &params)
{
    DBObject *obj = createObject( type, parent, params );
    if ( obj ) {
        emit newObject( obj );
    }
}
