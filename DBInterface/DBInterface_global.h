#ifndef DBINTERFACE_GLOBAL_H
#define DBINTERFACE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(DBINTERFACE_LIBRARY)
#  define DBINTERFACESHARED_EXPORT Q_DECL_EXPORT
#else
#  define DBINTERFACESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // DBINTERFACE_GLOBAL_H
