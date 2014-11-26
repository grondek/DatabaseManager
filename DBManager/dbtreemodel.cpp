#include "dbtreemodel.h"
#include "dbobject.h"

#include <QtDebug>

DBTreeModel::DBTreeModel(QObject *parent) :
    QStandardItemModel(parent)
{
    insertColumns( 0, 1, QModelIndex() );
}

Qt::ItemFlags DBTreeModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags fl = QStandardItemModel::flags( index );
    fl &= ~Qt::ItemIsEditable;
    return fl;
}

QModelIndex DBTreeModel::indexByName(const QString &objname)
{
    if ( objname.isEmpty() )
        return QModelIndex();

    return QModelIndex();
}

QVariant DBTreeModel::data(const QModelIndex &index, int role) const
{
    if ( role == Qt::DisplayRole || role == Qt::EditRole ) {
        if ( index.data( DBObjectRole ).canConvert< DBObject* >() ) {
            DBObject *obj = index.data( DBObjectRole ).value< DBObject* >();

            return obj->property( "name" );
        }
    }

    return QStandardItemModel::data( index, role );
}

void DBTreeModel::addObject(DBObject *obj)
{
    QModelIndex pindex = indexByName( obj->parentObject() );

    int row = rowCount( pindex );
    insertRows( row, 1, pindex );
    QModelIndex index = this->index( row, 0, pindex );

    setData( index, QVariant::fromValue< DBObject* >( obj ), DBObjectRole );
}

