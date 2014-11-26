#ifndef DBTREEMODEL_H
#define DBTREEMODEL_H

#include <QStandardItemModel>

class DBObject;

class DBTreeModel : public QStandardItemModel
{
    Q_OBJECT
public:
    enum Roles {
        DBObjectRole = Qt::UserRole + 1
    };

    explicit DBTreeModel(QObject *parent = 0);

    virtual Qt::ItemFlags flags( const QModelIndex & index ) const;

    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
public slots:
    void addObject( DBObject *obj );

private:
    QModelIndex indexByName( const QString &objname );
};

#endif // DBTREEMODEL_H
