#ifndef SQLITEDATABASE_GLOBAL_H
#define SQLITEDATABASE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(SQLITEDATABASE_LIBRARY)
#  define SQLITEDATABASESHARED_EXPORT Q_DECL_EXPORT
#else
#  define SQLITEDATABASESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // SQLITEDATABASE_GLOBAL_H
