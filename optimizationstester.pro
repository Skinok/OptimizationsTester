QT += qml quick xml
CONFIG += c++11

DEFINES += OPTIMIZATIONSTESTER_LIBRARY

# OptimizationsTester files

SOURCES += src/optimizationstesterplugin.cpp \
    src/dataxmlreader.cpp \
    src/codesamplesmodel.cpp \
    src/performancemanager.cpp


HEADERS += \
    src/optimizationstesterplugin.h \
    src/optimizationstester_global.h \
    src/optimizationstesterconstants.h \
    src/dataxmlreader.h \
    src/codesamplesmodel.h \
    src/performancemanager.h

RESOURCES += qml/optimizationstester.qrc

OTHER_FILES += examples/*.* \

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# Qt Creator linking

## Either set the IDE_SOURCE_TREE when running qmake,
## or set the QTC_SOURCE environment variable, to override the default setting
isEmpty(IDE_SOURCE_TREE): IDE_SOURCE_TREE = $$(QTC_SOURCE)
isEmpty(IDE_SOURCE_TREE): IDE_SOURCE_TREE = "C:/Users/Public/CUBE/qt-creator-opensource-src-4.8.2"

## Either set the IDE_BUILD_TREE when running qmake,
## or set the QTC_BUILD environment variable, to override the default setting
isEmpty(IDE_BUILD_TREE): IDE_BUILD_TREE = $$(QTC_BUILD)
isEmpty(IDE_BUILD_TREE): IDE_BUILD_TREE = "C:/Users/Public/CUBE/build-qtcreator-Qt_5_12_2_MSVC_2017_32-Release"

## uncomment to build plugin into user config directory
## <localappdata>/plugins/<ideversion>
##    where <localappdata> is e.g.
##    "%LOCALAPPDATA%\QtProject\qtcreator" on Windows Vista and later
##    "$XDG_DATA_HOME/data/QtProject/qtcreator" or "~/.local/share/data/QtProject/qtcreator" on Linux
##    "~/Library/Application Support/QtProject/Qt Creator" on OS X
## USE_USER_DESTDIR = yes

###### If the plugin can be depended upon by other plugins, this code needs to be outsourced to
###### <dirname>_dependencies.pri, where <dirname> is the name of the directory containing the
###### plugin's sources.

QTC_PLUGIN_NAME = OptimizationsTester
QTC_LIB_DEPENDS += \
    # nothing here at this time

QTC_PLUGIN_DEPENDS += \
    coreplugin

QTC_PLUGIN_RECOMMENDS += \
    # optional plugin dependencies. nothing here at this time



# Default rules for deployment.

DESTDIR = $$IDE_BUILD_TREE/lib/qtcreator/plugins

#DISTFILES += qml/optimizationsTester.qrc

##target.path += $$IDE_BUILD_TREE/lib/qtcreator/plugins
#deploiment.path =  C:/Users/Public/CUBE/build-qtcreator-Qt_5_12_2_MSVC_2017_32-Release/lib/qtcreator/plugins
#deploiment.files += qml/main

#INSTALLS += deploiment

#QMAKE_EXTRA_TARGETS += target

###### End _dependencies.pri contents ######

include($$IDE_SOURCE_TREE/src/qtcreatorplugin.pri)

DISTFILES += examples/*.*

splash.path  +=  $$IDE_BUILD_TREE/lib/qtcreator/plugins
splash.files += examples/*.*
INSTALLS += splash

QMAKE_EXTRA_TARGETS += splash
