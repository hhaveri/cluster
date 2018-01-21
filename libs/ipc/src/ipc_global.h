#ifndef IPC_GLOBAL_H
#define IPC_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(IPC_LIBRARY)
#  define IPC_SHARED_EXPORT Q_DECL_EXPORT
#else
#  define IPC_SHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // IPC_GLOBAL_H

