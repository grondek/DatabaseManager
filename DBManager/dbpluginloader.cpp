#include "dbpluginloader.h"

#include <QDirIterator>
#include <QFileInfo>
#include <QJsonObject>
#include <QPluginLoader>

#include <QtDebug>

DBPluginLoader::DBPluginLoader(QObject *parent) :
    QObject(parent)
{
}

DBPluginLoader::~DBPluginLoader()
{
    foreach ( const QString &iid, m_plugins.uniqueKeys() ) {
        if ( m_plugins.value( iid ) ) {
            m_plugins.value( iid )->unload();
            m_plugins.value( iid )->deleteLater();
        }
    }
}

QStringList DBPluginLoader::availablePlugins() const
{
    QStringList plugins;

    QDirIterator dit( "plugins" );
    while ( dit.hasNext() ) {
        dit.next();
        QFileInfo fi( dit.filePath() );
        if ( !fi.isFile() || fi.isSymLink() )
            continue;

        QPluginLoader *loader = new QPluginLoader( dit.filePath() );
        plugins << loader->metaData().toVariantMap().value( "IID" ).toString();
        loader->deleteLater();
    }

    return plugins;
}

bool DBPluginLoader::loadAll()
{
    QDirIterator dit( "plugins" );
    while ( dit.hasNext() ) {
        dit.next();
        QFileInfo fi( dit.filePath() );
        if ( !fi.isFile() || fi.isSymLink() )
            continue;

        QPointer< QPluginLoader > loader = new QPluginLoader( dit.filePath() );
        loader->load();
        m_plugins.insert(
                    loader->metaData().toVariantMap().value( "IID" ).toString(),
                    loader
                    );

        connect( loader->instance(), SIGNAL(newObject(DBObject*) ),
                 this, SIGNAL(newObject(DBObject*) ) );
    }

    return true;
}

DBInterface *DBPluginLoader::plugin(const QString &iid)
{
    return qobject_cast< DBInterface* >( m_plugins.value( iid )->instance() );
}
