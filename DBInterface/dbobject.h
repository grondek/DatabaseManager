#ifndef DBOBJECT_H
#define DBOBJECT_H

#include <QObject>

class DBObjectPrivate;

class DBObject: public QObject
{
    Q_OBJECT

    Q_PROPERTY( quint32 uid READ uid WRITE setUid USER true )
    Q_PROPERTY( QString name READ name WRITE setName USER true )
    Q_PROPERTY( QString parentObject READ parentObject WRITE setParentObject USER true )

private:
    DBObjectPrivate *_pd;
public:
    explicit DBObject(QObject *parent = 0);
    virtual ~DBObject();

    quint32 uid() const;
    void setUid( quint32 uid );

    QString name() const;
    void setName( const QString &name );

    QString parentObject() const;
    void setParentObject( const QString &pid );
};

#endif // DBOBJECT_H
