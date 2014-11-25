#ifndef SQLITEDATABASE_H
#define SQLITEDATABASE_H

#include "SQLiteDatabase_global.h"
#include "dbinterface.h"
#include <QtPlugin>

class SQLITEDATABASESHARED_EXPORT SQLiteDatabase: public DBInterface
{
    Q_OBJECT
    Q_INTERFACES(DBInterface)
    Q_PLUGIN_METADATA( IID "sqlitedatabase" FILE "sqlitedatabase.json" )
public:
    explicit SQLiteDatabase( QObject *parent = 0);
    virtual ~SQLiteDatabase();

    /**
     * @brief Main icon
     * @return
     */
    virtual QIcon icon() const;

    /**
     * @brief Database name
     * @return
     */
    virtual QString name() const;

    /**
     * @brief Returns list of database object types
     * @return
     */
    virtual QStringList objects() const;

    /**
     * @brief Returns list of database object types, which can be child of parent_type
     * @param parent_type parent type for object types
     * @return
     */
    virtual QStringList childObjects( const QString &parent_type ) const;

    /**
     * @brief Returns information about object type
     *
     *
     *
     * @param type object type
     * @return
     */
    virtual DB_OBJECT_TYPE_INFO objectTypeInfo( const QString &type ) const;

    /**
     * @brief Create database object
     * @param type object type
     * @param parameters object parameters
     * @param parent parent object identifier
     * @return
     */
    virtual DBObject *createObject( const QString &type, const QVariantMap &parameters, const QString &parent );

    /**
     * @brief Create object editor for new object
     * @param type object type
     * @param parent parent object identifier
     * @return
     */
    virtual QWidget *createObjectEditor( const QString &type, const QString &parent, QWidget *parentWidget );
    /**
     * @brief Create object editor for existing object
     * @param obj editing object
     * @return
     */
    virtual QWidget *createObjectEditor( DBObject *obj );
};

#endif // SQLITEDATABASE_H
