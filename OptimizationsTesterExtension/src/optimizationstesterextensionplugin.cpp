#include "optimizationstesterextensionplugin.h"
#include "optimizationstesterextensionconstants.h"

#include <coreplugin/icore.h>
#include <coreplugin/icontext.h>
#include <coreplugin/actionmanager/actionmanager.h>
#include <coreplugin/actionmanager/command.h>
#include <coreplugin/actionmanager/actioncontainer.h>
#include <coreplugin/coreconstants.h>

#include <utils/theme/theme.h>

//

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


namespace OptimizationsTesterExtension {
namespace Internal {

OptimizationsTesterExtensionPlugin::OptimizationsTesterExtensionPlugin()
{
    // Create your members
}

OptimizationsTesterExtensionPlugin::~OptimizationsTesterExtensionPlugin()
{
    // Unregister objects from the plugin manager's object pool
    // Delete members
}

bool OptimizationsTesterExtensionPlugin::initialize(const QStringList &arguments, QString *errorString)
{
    // Register objects in the plugin manager's object pool
    // Load settings
    // Add actions to menus
    // Connect to other plugins' signals
    // In the initialize function, a plugin can be sure that the plugins it
    // depends on have initialized their members.

    Q_UNUSED(arguments)
    Q_UNUSED(errorString)

    auto action = new QAction(tr("OptimizationsTesterExtension Action"), this);
    Core::Command *cmd = Core::ActionManager::registerAction(action, Constants::ACTION_ID,
                                                             Core::Context(Core::Constants::C_GLOBAL));
    cmd->setDefaultKeySequence(QKeySequence(tr("Ctrl+Alt+Meta+A")));
    connect(action, &QAction::triggered, this, &OptimizationsTesterExtensionPlugin::triggerAction);

    Core::ActionContainer *menu = Core::ActionManager::createMenu(Constants::MENU_ID);
    menu->menu()->setTitle(tr("OptimizationsTesterExtension"));
    menu->addAction(cmd);
    Core::ActionManager::actionContainer(Core::Constants::M_TOOLS)->addMenu(menu);

    //***
    // Skinok Plugin
    //***


    //**
    // First, connect the QuickView to change state signal
    //**
    QObject::connect( &mQuickView, &QQuickView::statusChanged, this, &OptimizationsTesterExtensionPlugin::onQuickViewStatusChanged);

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

    // Add the Qt Creator Theme to the plugin qml engine
    // It will enable the use of Qt creator native theme
    //->setupTheme(mQuickView.engine());
    static const int typeIndex = qmlRegisterSingletonType<Utils::Theme>("QtQuickDesignerTheme", 1, 0,
        "Theme",  [](QQmlEngine *, QJSEngine *) {
            return qobject_cast<QObject*>(new Utils::Theme("MyTheme"));
    });
    Q_UNUSED(typeIndex);

    //mQuickView.engine()->addImageProvider(QLatin1String("icons"), new QmlDesignerIconProvider());

    //**
    // Set the QML main source file
    //**
    mQuickView.setSource(lMainFile);
    mQuickView.setResizeMode(QQuickView::SizeRootObjectToView);
    mQuickView.setTitle("Optimizations Tester");

    mQuickView.show(); // debug purpose only, it should move to Action triggered after finishing to code it

    return true;
}

void OptimizationsTesterExtensionPlugin::extensionsInitialized()
{
    // Retrieve objects from the plugin manager's object pool
    // In the extensionsInitialized function, a plugin can be sure that all
    // plugins that depend on it are completely initialized.
}

ExtensionSystem::IPlugin::ShutdownFlag OptimizationsTesterExtensionPlugin::aboutToShutdown()
{
    // Save settings
    // Disconnect from signals that are not needed during shutdown
    // Hide UI (if you add UI that is not in the main window directly)
    return SynchronousShutdown;
}

void OptimizationsTesterExtensionPlugin::triggerAction()
{
    QMessageBox::information(Core::ICore::mainWindow(),
                             tr("Action Triggered"),
                             tr("This is an action from OptimizationsTesterExtension."));
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
void OptimizationsTesterExtensionPlugin::onQuickViewStatusChanged(QQuickView::Status status)
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


void OptimizationsTesterExtensionPlugin::initializeOptimRunner(){

    // Todo : Add OptimRunner in the user session


}

} // namespace Internal
} // namespace OptimizationsTesterExtension
