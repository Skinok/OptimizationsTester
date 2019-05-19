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

## uncomment to build plugin into user config directory
## <localappdata>/plugins/<ideversion>
##    where <localappdata> is e.g.
##    "%LOCALAPPDATA%\QtProject\qtcreator" on Windows Vista and later
##    "$XDG_DATA_HOME/data/QtProject/qtcreator" or "~/.local/share/data/QtProject/qtcreator" on Linux
##    "~/Library/Application Support/QtProject/Qt Creator" on OS X
# USE_USER_DESTDIR = yes

###### If the plugin can be depended upon by other plugins, this code needs to be outsourced to
###### <dirname>_dependencies.pri, where <dirname> is the name of the directory containing the
###### plugin's sources.

CONFIG(debug, debug|release) {
    isEmpty(IDE_BUILD_TREE): IDE_BUILD_TREE = "C:/Users/Public/CUBE/build-qtcreator-Qt_5_12_2_MSVC_2017_32-Debug"
    LIBS += $$IDE_BUILD_TREE/lib/qtcreator/plugins/Cored4.lib
    LIBS += $$IDE_BUILD_TREE/lib/qtcreator/plugins/QmakeProjectManagerd4.lib
    LIBS += $$IDE_BUILD_TREE/lib/qtcreator/plugins/ProjectExplorerd4.lib
}else {
    isEmpty(IDE_BUILD_TREE): IDE_BUILD_TREE = "C:/Users/Public/CUBE/build-qtcreator-Qt_5_12_2_MSVC_2017_32-Release"
    LIBS += $$IDE_BUILD_TREE/lib/qtcreator/plugins/QmakeProjectManager4.lib
    LIBS += $$IDE_BUILD_TREE/lib/qtcreator/plugins/ProjectExplorer4.lib
}

QTC_PLUGIN_NAME = OptimizationsTesterExtension
QTC_LIB_DEPENDS += \
    # nothing here at this time

QTC_PLUGIN_DEPENDS += \
    coreplugin

QTC_PLUGIN_RECOMMENDS += \
    # optional plugin dependencies. nothing here at this time

###### End _dependencies.pri contents ######

include($$IDE_SOURCE_TREE/src/qtcreatorplugin.pri)


#For our copy command, we neeed to fix the filepaths to use Windows-style path dividers.
OPTIMRUNNER_SOURCE_PATH = $$shell_path($$clean_path("$$PWD/../OptimRunner"))
message("source path" $$OPTIMRUNNER_SOURCE_PATH)
OPTIMRUNNER_DESTINATION = $$shell_path($$clean_path("$${DESTDIR}/OptimRunner"))
message("source path" $$OPTIMRUNNER_DESTINATION)

#Create a command, using the 'cmd' command line and Window's 'xcopy', to copy our shaders folder
win32:CopyProject.commands = $$quote(cmd /c xcopy /Y /S /I $${OPTIMRUNNER_SOURCE_PATH} $${OPTIMRUNNER_DESTINATION})

# Not tested on unix, this command should maybe be fixed
# On unix, it may be possible to use the INSTALLS qmake command
# It does not seem to work in our case on Windows
unix:CopyProject.commands = $$quote(cp -rf $${OPTIMRUNNER_SOURCE_PATH} $${OPTIMRUNNER_DESTINATION})

#Add the command to Qt.
QMAKE_EXTRA_TARGETS += CopyProject
POST_TARGETDEPS += CopyProject

