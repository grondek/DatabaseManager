#include "sqlitedatabase.h"
#include "sqlitecreatedatabase.h"

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

DBObject *SQLiteDatabase::createObject(const QString &type, const QVariantMap &parameters, const QString &parent)
{
    return NULL;
}

QWidget *SQLiteDatabase::createObjectEditor(const QString &type, const QString &parent, QWidget *parentWidget)
{
    if ( type == "database" ) {
        SQLITECreateDatabase *creator = new SQLITECreateDatabase( parentWidget );
        return creator;
    }

    return NULL;
}

QWidget *SQLiteDatabase::createObjectEditor(DBObject *obj)
{
    return new QWidget();
}
