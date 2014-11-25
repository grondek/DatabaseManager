#ifndef DBPLUGINLOADER_H
#define DBPLUGINLOADER_H

#include <QObject>
#include <QHash>
#include <QPointer>

#include "dbinterface.h"

class QPluginLoader;

class DBPluginLoader : public QObject
{
    Q_OBJECT
private:
    QHash< QString, QPointer< QPluginLoader > > m_plugins;
public:
    explicit DBPluginLoader(QObject *parent = 0);
    virtual ~DBPluginLoader();

    QStringList availablePlugins() const;
    bool loadAll();

    DBInterface *plugin( const QString &iid );
};

#endif // DBPLUGINLOADER_H
