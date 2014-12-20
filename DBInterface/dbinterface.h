#ifndef DBINTERFACE_H
#define DBINTERFACE_H

#include "DBInterface_global.h"
#include "dbobject.h"
#include <QIcon>
#include <QObject>
#include <QWidget>
#include <QVariantMap>
#include <QtPlugin>

typedef struct _DB_OBJECT_TYPE_PARAMETER_INFO {
    QString name;
    QVariant::Type type;
} DB_OBJECT_TYPE_PARAMETER_INFO;

typedef struct _DB_OBJECT_TYPE_INFO {
    QString name;
    QIcon icon;
    QMap< QString, DB_OBJECT_TYPE_PARAMETER_INFO > parameters;
} DB_OBJECT_TYPE_INFO;

/**
 * @brief Database description interface
 *
 */
class DBINTERFACESHARED_EXPORT DBInterface: public QObject
{
    Q_OBJECT
signals:
    void newObject( DBObject *obj );

    void beginAddChildren( DBObject *thisobj, int oldcount, int newcount );
    void endAddChildren();
public:
    /**
     * @brief Default constructor
     * @param parent parent object
     */
    explicit DBInterface( QObject *parent = 0 );
    /**
     * @brief Destructor
     */
    virtual ~DBInterface();

    /**
     * @brief Main icon
     * @return
     */
    virtual QIcon icon() const = 0;

    /**
     * @brief Database name
     * @return
     */
    virtual QString name() const = 0;

    /**
     * @brief Returns list of database object types
     * @return
     */
    virtual QStringList objects() const = 0;

    /**
     * @brief Returns list of database object types, which can be child of parent_type
     * @param parent_type parent type for object types
     * @return
     */
    virtual QStringList childObjects( const QString &parent_type ) const = 0;

    /**
     * @brief Returns information about object type
     *
     *
     *
     * @param type object type
     * @return
     */
    virtual DB_OBJECT_TYPE_INFO objectTypeInfo( const QString &type ) const = 0;

    /**
     * @brief Create database object
     * @param type object type
     * @param parameters object parameters
     * @param parent parent object identifier
     * @return
     */
    virtual DBObject *createObject( DBObject *parent, const QString &type, const QVariantMap &parameters ) = 0;

    /**
     * @brief Create object editor for new object
     * @param type object type
     * @param parent parent object identifier
     * @return
     */
    virtual QWidget *createObjectEditor( const QString &type, quint32 parent, QWidget *parentWidget ) = 0;
    /**
     * @brief Create object editor for existing object
     * @param obj editing object
     * @return
     */
    virtual QWidget *createObjectEditor( DBObject *obj ) = 0;
};

Q_DECLARE_INTERFACE(DBInterface, "org.databasemanager.dbinterface")


#endif // DBINTERFACE_H
