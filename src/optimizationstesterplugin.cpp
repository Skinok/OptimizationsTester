#include "optimizationstesterplugin.h"
#include "optimizationstesterconstants.h"
#include "codesamplesmodel.h"
#include "dataxmlreader.h"
#include "performancemanager.h"

#include <coreplugin/icore.h>
#include <coreplugin/icontext.h>
#include <coreplugin/actionmanager/actionmanager.h>
#include <coreplugin/actionmanager/command.h>
#include <coreplugin/actionmanager/actioncontainer.h>
#include <coreplugin/coreconstants.h>

#include <QAction>
#include <QMessageBox>
#include <QMainWindow>
#include <QMenu>
#include <QQuickView>
#include <QDebug>
#include <QDir>
#include <QObject>
#include <QQmlError>
#include <QQmlEngine>
#include <QQmlContext>

namespace OptimizationsTester {
namespace Internal {

OptimizationsTesterPlugin::OptimizationsTesterPlugin()
{
    // Create your members
}

OptimizationsTesterPlugin::~OptimizationsTesterPlugin()
{
    // Unregister objects from the plugin manager's object pool
    // Delete members
}

bool OptimizationsTesterPlugin::initialize(const QStringList &arguments, QString *errorString)
{
    // Register objects in the plugin manager's object pool
    // Load settings
    // Add actions to menus
    // Connect to other plugins' signals
    // In the initialize function, a plugin can be sure that the plugins it
    // depends on have initialized their members.

    Q_UNUSED(arguments)
    Q_UNUSED(errorString)

    auto action = new QAction(tr("OptimizationsTester Action"), this);
    Core::Command *cmd = Core::ActionManager::registerAction(action, Constants::ACTION_ID,
                                                             Core::Context(Core::Constants::C_GLOBAL));
    cmd->setDefaultKeySequence(QKeySequence(tr("Ctrl+Alt+Meta+A")));
    connect(action, &QAction::triggered, this, &OptimizationsTesterPlugin::triggerAction);

    Core::ActionContainer *menu = Core::ActionManager::createMenu(Constants::MENU_ID);
    menu->menu()->setTitle(tr("Optimitazions Tester"));
    menu->addAction(cmd);
    Core::ActionManager::actionContainer(Core::Constants::M_TOOLS)->addMenu(menu);

    //**
    // First, connect the QuickView to change state signal
    //**
    QObject::connect( &mQuickView, &QQuickView::statusChanged, this, &OptimizationsTesterPlugin::onQuickViewStatusChanged);

    // Get the QML entry point
    QUrl lMainFile =  QUrl("qrc:///main.qml");



    mXMLReader = new DataXMLReader( &mModel );

    //**
    // Load example files
    //**
    QFile lDataFile("examples/examples.xml");
    if (! lDataFile.open(QFile::ReadOnly | QFile::Text) ){
        qWarning() << "Cannot find examples.xml file in " << QDir::currentPath();
        return false;
    }
    mXMLReader->read( &lDataFile );

    //**
    //Give QML access to the C++ model and utility classes
    //**
    mQuickView.rootContext()->setContextProperty("DataModel", &mModel);
    mQuickView.rootContext()->setContextProperty("PerformanceMgr", &mPerfoMgr);

    //**
    // Set the QML main source file
    //**
    mQuickView.setSource(lMainFile);
    mQuickView.setResizeMode(QQuickView::SizeRootObjectToView);
    mQuickView.setTitle("Optimizations Tester");

    mQuickView.show(); // debug purpose only

    return true;
}

void OptimizationsTesterPlugin::extensionsInitialized()
{
    // Retrieve objects from the plugin manager's object pool
    // In the extensionsInitialized function, a plugin can be sure that all
    // plugins that depend on it are completely initialized.
}

ExtensionSystem::IPlugin::ShutdownFlag OptimizationsTesterPlugin::aboutToShutdown()
{
    // Save settings
    // Disconnect from signals that are not needed during shutdown
    // Hide UI (if you add UI that is not in the main window directly)
    return SynchronousShutdown;
}

void OptimizationsTesterPlugin::triggerAction()
{
    // Show the view only when user click on the plugin action
    // Initialiaze our QML view and check if the file exists otherwise return false.
    // It will prevent the user that there is an issue when loading this plugin
    mQuickView.show();
}

/*
 * *
Specifies the loading status of the QQuickView.

Constant	Value	Description
QQuickView::Null	0	This QQuickView has no source set.
QQuickView::Ready	1	This QQuickView has loaded and created the QML component.
QQuickView::Loading	2	This QQuickView is loading network data.
QQuickView::Error	3	One or more errors has occurred. Call errors() to retrieve a list of errors.
*/
void OptimizationsTesterPlugin::onQuickViewStatusChanged(QQuickView::Status status)
{
    switch(status)
    {
    case QQuickView::Ready:
        {
            qDebug() << "QQuickview is ready";
        }
        break;
    case QQuickView::Loading:
        {

        }
        break;
    case QQuickView::Error:
        {
            qWarning() << "QQuickview error when loading source";

            QString lErrorString;

            foreach( QQmlError lError, mQuickView.errors())
            {
                lErrorString.append(lError.toString()).append("\n");
            }

            QMessageBox::warning(nullptr, "Error in OptimizationsTester QML plugin", lErrorString );
        }
        break;
    default:
        break;
    }
}

} // namespace Internal
} // namespace OptimizationsTester
