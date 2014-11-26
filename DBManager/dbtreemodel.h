#ifndef DBTREEMODEL_H
#define DBTREEMODEL_H

#include <QAbstractItemModel>

class DBObject;
class DBTreeModelPrivate;

class DBTreeModel : public QAbstractItemModel
{
    Q_OBJECT
private:
    DBTreeModelPrivate *_pd;
public:
    enum Roles {
        DBObjectRole = Qt::UserRole + 1
    };

    explicit DBTreeModel(QObject *parent = 0);
    virtual ~DBTreeModel();

    virtual Qt::ItemFlags flags( const QModelIndex & index ) const;

    virtual int columnCount( const QModelIndex & parent = QModelIndex() ) const;
    virtual int rowCount( const QModelIndex & parent = QModelIndex() ) const;

    virtual QModelIndex index( int row, int column, const QModelIndex & parent = QModelIndex() ) const;

    virtual QModelIndex parent( const QModelIndex & index ) const;

    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
public slots:
    void addObject( DBObject *obj );

private:
    QModelIndex indexByName( const QString &objname );

    int row( DBObject *obj ) const;
    DBObject *object( int row, DBObject *pobj ) const;
};

#endif // DBTREEMODEL_H
