#ifndef DBOBJECT_H
#define DBOBJECT_H

#include <QObject>
#include <QIcon>
#include <QAction>

class DBObjectPrivate;

class DBObject: public QObject
{
    Q_OBJECT

    Q_PROPERTY( quint32 uid READ uid WRITE setUid USER true )
    Q_PROPERTY( QString name READ name WRITE setName USER true )
    Q_PROPERTY( quint32 parentObject READ parentObject WRITE setParentObject USER true )
    Q_PROPERTY( QIcon icon READ icon WRITE setIcon USER true )

private:
    DBObjectPrivate *_pd;
signals:
    void childCountChanged( DBObject *thisobj );
    void addChild(
            const QString &type,
            quint32 parent,
            const QVariantMap &params
            );
    void removeChild( quint32 uid );

    void execQuery( quint32 senderuid, const QString &query );
public:
    explicit DBObject(QObject *parent = 0);
    DBObject(quint32 uid, quint32 parentuid, QObject *parent = 0);
    virtual ~DBObject();

    quint32 uid() const;
    void setUid( quint32 uid );

    QString name() const;
    void setName( const QString &name );

    quint32 parentObject() const;
    void setParentObject( quint32 pid );

    QIcon icon() const;
    void setIcon( const QIcon &icon );

    virtual int childCount() const;
    virtual QList< QAction *> actions() const;
public slots:
    virtual void exec( quint32 senderuid, const QString &query );
protected:
    virtual void childEvent(QChildEvent *event);
};

#endif // DBOBJECT_H
