#include "sqlitedbobject.h"

#include <QAction>

#include <QtDebug>

SQLITEDBObject::SQLITEDBObject( QObject *parent ) :
    DBObject( parent )
{
    setIcon( QIcon( ":/sqlitedatabase/images/Sqlite-square-icon.svg" ) );

    m_action_connect = new QAction( this );
    m_action_connect->setText( tr( "Connect" ) );
    connect( m_action_connect, SIGNAL(triggered() ),
             this, SLOT(connectToDB() ) );

    m_action_separator = new QAction( this );
    m_action_separator->setSeparator( true );

    m_action_remove = new QAction( this );
    m_action_remove->setText( tr( "Remove" ) );
    connect( m_action_remove, SIGNAL(triggered() ),
             this, SLOT(remove() ) );
}

SQLITEDBObject::~SQLITEDBObject()
{
}

QList<QAction *> SQLITEDBObject::actions() const
{
    return QList<QAction *>()
            << m_action_connect
            << m_action_separator
            << m_action_remove
            << m_action_separator;
}

void SQLITEDBObject::connectToDB()
{
    qDebug() << "Connect to db";
}

void SQLITEDBObject::remove()
{
    qDebug() << "Remove this";
}
