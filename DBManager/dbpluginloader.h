#ifndef DBPLUGINLOADER_H
#define DBPLUGINLOADER_H

#include <QObject>
#include <QHash>
#include <QPointer>

#include "dbinterface.h"

class QPluginLoader;

/**
 * @brief Database type plugin loader
 *
 * Loads all available plugins for database types
 *
 */
class DBPluginLoader : public QObject
{
    Q_OBJECT
private:
    QHash< QString, QPointer< QPluginLoader > > m_plugins; ///<! Database plugins
signals:
    void newObject( DBObject *obj );
public:
    /**
     * @brief Constructor
     * @param parent parent object
     */
    explicit DBPluginLoader(QObject *parent = 0);
    /**
     * @brief Destructor
     */
    virtual ~DBPluginLoader();

    /**
     * @brief Returns list of available plugins
     *
     * @return list of available plugins
     */
    QStringList availablePlugins() const;
    /**
     * @brief Load all available plugins
     *
     * @return true if loaded successfully
     */
    bool loadAll();

    /**
     * @brief Returns plugin by identificator iid
     *
     * @param iid plugin identificator
     *
     * @return Database creator object instance
     */
    DBInterface *plugin( const QString &iid );
};

#endif // DBPLUGINLOADER_H
