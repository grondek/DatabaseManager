#ifndef SQLITECREATEDATABASE_H
#define SQLITECREATEDATABASE_H

#include <QWidget>
#include <QVariantMap>
#include "dbobject.h"

namespace Ui {
class SQLITECreateDatabase;
}

class SQLITECreateDatabase : public QWidget
{
    Q_OBJECT
private:
    Ui::SQLITECreateDatabase *ui;
signals:
    void createObject(
            DBObject *parent,
            const QString &type,
            const QVariantMap &params
            );
//    void created( DBObject *obj );
public:
    explicit SQLITECreateDatabase(QWidget *parent = 0);
    ~SQLITECreateDatabase();
public slots:
    void create();
private slots:
    void on_tbSelectFile_clicked();
    void readModeChanged();
};

#endif // SQLITECREATEDATABASE_H
