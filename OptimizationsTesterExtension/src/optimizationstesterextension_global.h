#pragma once

#include <QtGlobal>

#if defined(OPTIMIZATIONSTESTEREXTENSION_LIBRARY)
#  define OPTIMIZATIONSTESTEREXTENSIONSHARED_EXPORT Q_DECL_EXPORT
#else
#  define OPTIMIZATIONSTESTEREXTENSIONSHARED_EXPORT Q_DECL_IMPORT
#endif