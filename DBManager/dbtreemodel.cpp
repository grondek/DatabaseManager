#include "dbtreemodel.h"
#include "dbobject.h"

#include <QtDebug>

class DBTreeModelPrivate
{
public:
    QList< DBObject* > root_objects;

    DBTreeModelPrivate()
    {

    }
    ~DBTreeModelPrivate()
    {
        foreach ( DBObject *root, root_objects )
            root->deleteLater();
    }
};

DBTreeModel::DBTreeModel(QObject *parent) :
    QAbstractItemModel(parent)
{
    _pd = new DBTreeModelPrivate;
}

DBTreeModel::~DBTreeModel()
{
    delete _pd;
}

int DBTreeModel::row( DBObject *obj ) const
{
    if ( !obj )
        return -1;

    if ( !obj->parent() ) {
        return _pd->root_objects.indexOf( obj );
    } else {
        QList< quint32 > uids;
        foreach ( QObject *child, obj->parent()->children() )
            if ( qobject_cast< DBObject* >( child ) )
                uids << qobject_cast< DBObject* >( child )->uid();

        qSort( uids );

        return uids.indexOf( obj->uid() );
    }

    return -1;
}

DBObject *DBTreeModel::object(int row, DBObject *pobj) const
{
    if ( !pobj )
        return _pd->root_objects.value( row );

    QList< quint32 > uids;
    foreach ( QObject *child, pobj->children() )
        if ( qobject_cast< DBObject* >( child ) )
            uids << qobject_cast< DBObject* >( child )->uid();

    qSort( uids );
    quint32 uid = uids.value( row, 0 );
    if ( !uid )
        return NULL;

    foreach ( QObject *child, pobj->children() )
        if ( qobject_cast< DBObject* >( child ) )
            if ( qobject_cast< DBObject* >( child )->uid() == uid )
                return qobject_cast< DBObject* >( child );

    return NULL;
}

Qt::ItemFlags DBTreeModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags fl = QAbstractItemModel::flags( index );
    fl &= ~Qt::ItemIsEditable;
    return fl;
}

int DBTreeModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED( parent );
    return 1;
}

int DBTreeModel::rowCount(const QModelIndex &parent) const
{
    if ( !parent.isValid() ) {
        return _pd->root_objects.count();
    }

    DBObject *obj = parent.data( DBObjectRole ).value< DBObject* >();
    if ( !obj )
        return 0;

    return obj->childCount();
}

QModelIndex DBTreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if ( column )
        return QModelIndex();

    quint32 uid = quint32( parent.internalId() );
    if ( !uid ) {
        DBObject *child = object( row, NULL );
        if ( !child )
            return QModelIndex();

        return createIndex( row, column, child->uid() );
    }

    foreach ( DBObject *obj, _pd->root_objects ) {
        if ( obj->uid() == uid ) {
            DBObject *child = object( row, obj );
            if ( !child )
                return QModelIndex();

            return createIndex( row, column, child->uid() );
        }

        foreach ( DBObject *child, obj->findChildren< DBObject* >() )
            if ( child->uid() == uid ) {
                DBObject *cchild = object( row, child );
                if ( !cchild )
                    return QModelIndex();

                return createIndex(
                            row,
                            0,
                            cchild->uid()
                            );
            }

    }

    return QModelIndex();
}

QModelIndex DBTreeModel::parent(const QModelIndex &index) const
{
    quint32 uid = quint32( index.internalId() );
    foreach ( DBObject *obj, _pd->root_objects ) {
        if ( obj->uid() == uid )
            return QModelIndex();

        foreach ( DBObject *child, obj->findChildren< DBObject* >() )
            if ( child->uid() == uid )
                return createIndex(
                            row( qobject_cast< DBObject* >( child->parent() ) ),
                            0,
                            child->parent()->property( "uid" ).toUInt()
                            );

    }

    return QModelIndex();
}

QModelIndex DBTreeModel::indexByUid( quint32 uid )
{
    if ( !uid )
        return QModelIndex();

    foreach ( DBObject *obj, _pd->root_objects ) {
        if ( obj->uid() == uid )
            return createIndex( row( obj ), 0, obj->uid() );

        foreach ( DBObject *child, obj->findChildren< DBObject* >() )
            if ( child->uid() == uid )
                return createIndex(
                            row( qobject_cast< DBObject* >( child ) ),
                            0,
                            child->property( "uid" ).toUInt()
                            );

    }

    return QModelIndex();
}

QVariant DBTreeModel::data(const QModelIndex &index, int role) const
{
    quint32 uid = quint32( index.internalId() );
    foreach ( DBObject *obj, _pd->root_objects ) {
        if ( obj->uid() == uid )
            return data( obj, role );

        foreach ( DBObject *child, obj->findChildren< DBObject* >() )
            if ( child->uid() == uid )
                return data( child, role );
    }

    return QVariant();
}


QVariant DBTreeModel::data(DBObject *obj, int role) const
{
    if ( role == Qt::DisplayRole || role == Qt::EditRole ) {
        return obj->name();
    }

    if ( role == DBObjectRole ) {
        return QVariant::fromValue< DBObject* >( obj );
    }

    if ( role == Qt::DecorationRole ) {
        return obj->icon();
    }

    return QVariant();
}


void DBTreeModel::addObject(DBObject *obj)
{
    if ( !obj->parent() ) {
        int row = _pd->root_objects.count();
        beginInsertRows( QModelIndex(), row, row );
        _pd->root_objects.append( obj );
        endInsertRows();
    }

    connect( obj, SIGNAL(chilrenAdded(DBObject*,int,int) ),
             this, SLOT(objectChildrenAdded(DBObject*,int,int) )
             );
}

void DBTreeModel::beginAddObjectChild(DBObject *pobj, int oldcount, int newcount)
{
    QModelIndex pindex = indexByUid( pobj->uid() );
    beginInsertRows( pindex, oldcount, newcount - 1 );
}

void DBTreeModel::endAddObjectChild()
{
    endInsertRows();
}

