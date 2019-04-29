QT += qml xml quick
CONFIG += c++11

DEFINES += OPTIMIZATIONSTESTEREXTENSION_LIBRARY

# OptimizationsTesterExtension files

SOURCES += \
        src/optimizationstesterextensionplugin.cpp \
        src/dataxmlreader.cpp \
        src/codesamplesmodel.cpp \
        src/optimizationstesterextensiontheme.cpp \

HEADERS += \
        src/optimizationstesterextensionplugin.h \
        src/optimizationstesterextension_global.h \
        src/optimizationstesterextensionconstants.h \
        src/dataxmlreader.h \
        src/codesamplesmodel.h \
        src/optimizationstesterextensiontheme.h \

RESOURCES += qml/optimizationstester.qrc

OTHER_FILES += examples/*.* \
# Qt Creator linking

## Either set the IDE_SOURCE_TREE when running qmake,
## or set the QTC_SOURCE environment variable, to override the default setting
isEmpty(IDE_SOURCE_TREE): IDE_SOURCE_TREE = $$(QTC_SOURCE)
isEmpty(IDE_SOURCE_TREE): IDE_SOURCE_TREE = "C:/Users/Public/CUBE/qt-creator-opensource-src-4.8.2"

## Either set the IDE_BUILD_TREE when running qmake,
## or set the QTC_BUILD environment variable, to override the default setting
isEmpty(IDE_BUILD_TREE): IDE_BUILD_TREE = $$(QTC_BUILD)
isEmpty(IDE_BUILD_TREE): IDE_BUILD_TREE = "C:/Users/Public/CUBE/build-qtcreator-Qt_5_12_2_MSVC_2017_32-Debug"

## uncomment to build plugin into user config directory
## <localappdata>/plugins/<ideversion>
##    where <localappdata> is e.g.
##    "%LOCALAPPDATA%\QtProject\qtcreator" on Windows Vista and later
##    "$XDG_DATA_HOME/data/QtProject/qtcreator" or "~/.local/share/data/QtProject/qtcreator" on Linux
##    "~/Library/Application Support/QtProject/Qt Creator" on OS X
USE_USER_DESTDIR = yes

###### If the plugin can be depended upon by other plugins, this code needs to be outsourced to
###### <dirname>_dependencies.pri, where <dirname> is the name of the directory containing the
###### plugin's sources.

QTC_PLUGIN_NAME = OptimizationsTesterExtension
QTC_LIB_DEPENDS += \
    # nothing here at this time

QTC_PLUGIN_DEPENDS += \
    coreplugin

QTC_PLUGIN_RECOMMENDS += \
    # optional plugin dependencies. nothing here at this time

###### End _dependencies.pri contents ######

include($$IDE_SOURCE_TREE/src/qtcreatorplugin.pri)