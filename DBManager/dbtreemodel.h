#ifndef DBTREEMODEL_H
#define DBTREEMODEL_H

#include <QStandardItemModel>

class DBTreeModel : public QStandardItemModel
{
    Q_OBJECT
public:
    explicit DBTreeModel(QObject *parent = 0);
    
signals:
    
public slots:
    
};

#endif // DBTREEMODEL_H
