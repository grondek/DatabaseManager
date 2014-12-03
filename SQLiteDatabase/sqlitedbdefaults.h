#ifndef SQLITEDBDEFAULTS_H
#define SQLITEDBDEFAULTS_H

#include <QString>

namespace sqlitedb {

const QString SETTINGS_PREFIX( "sqlite" );
const QString SETTINGS_LAST_OPEN_DIR( "last_open_dir" );


const QString OBJECT_TYPE_SQLITE_GROUP_TABLES( "sqlite.group.tables" );
const QString OBJECT_TYPE_SQLITE_GROUP_VIEWS( "sqlite.group.views" );

const char SQLITE_QUERY_PROPERTY[] = "sqlite.query";

} // namespace sqlitedb


#endif // SQLITEDBDEFAULTS_H
