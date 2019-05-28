/*
  This file is part of OptimizationTester
  Copyright (C) 2019 Skinok Todar on GitHub
  Author: Frederic Lambert <skinok.todar@gmail.com>
  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "optimizationstesterextensionplugin.h"
#include "optimizationstesterextensionconstants.h"

#include <coreplugin/icore.h>
#include <coreplugin/icontext.h>
#include <coreplugin/actionmanager/actionmanager.h>
#include <coreplugin/actionmanager/command.h>
#include <coreplugin/actionmanager/actioncontainer.h>
#include <coreplugin/coreconstants.h>

#include <utils/theme/theme.h>
#include <utils/algorithm.h>
#include <utils/mimetypes/mimetype.h>
#include <utils/mimetypes/mimedatabase.h>

#include <projectexplorer/project.h>
#include <projectexplorer/session.h>
#include <projectexplorer/projectmanager.h>
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

using namespace ProjectExplorer;

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
    // Load example files
    //**
    QFile lDataFile("examples/examples.xml");
    if (! lDataFile.open(QFile::ReadOnly | QFile::Text) ){
        qWarning() << "Cannot find examples.xml file in " << QDir::currentPath();
        return false;
    }

    // XML Reader for the examples of the second tab
    mXMLReader = new DataXMLReader( &mModel );
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

    //**
    // Set the QML main source file
    //**
    QUrl lMainFile =  QUrl("qrc:///main.qml");

    //**
    // First, connect the QuickView to change state signal
    //**
    QObject::connect( &mQuickView, &QQuickView::statusChanged, this, &OptimizationsTesterExtensionPlugin::onQuickViewStatusChanged);

    // Record this c++ class in the QML engine and allow his slots to be called from QML
    mQuickView.engine()->rootContext()->setContextProperty("OptimManager",this);

    mQuickView.setSource(lMainFile);
    mQuickView.setResizeMode(QQuickView::SizeRootObjectToView);
    mQuickView.setTitle("Optimizations Tester");

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
    // Show the plugin QML window
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

//*********
// Add OptimRunner in the user session
//*********
void OptimizationsTesterExtensionPlugin::initializeOptimRunner(){

    //*********
    // Already existing project
    //*********
    QString fileName("../lib/qtcreator/plugins/OptimRunner/OptimRunner.pro");
    const QFileInfo fi(fileName);
    const auto filePath = Utils::FileName::fromString(fi.absoluteFilePath());
    Project *found = Utils::findOrDefault(SessionManager::projects(),
                                          Utils::equal(&Project::projectFilePath, filePath));
    if (found) {
        SessionManager::reportProjectLoadingProgress();
        return;
    }

    //****
    // Add Project to the user current session
    // Code retrieved from "ProjectExplorerPlugin::OpenProjectResult ProjectExplorerPlugin::openProjects(const QStringList &fileNames)" function
    //****
    Utils::MimeType mt = Utils::mimeTypeForFile(fileName);
    if (ProjectManager::canOpenProjectForMimeType(mt)) {
        if (!filePath.toFileInfo().isFile()) {
            qDebug() << tr("Failed opening project \"%1\": Project is not a file.").arg(fileName);
        } else if (Project *pro = ProjectManager::openProject(mt, filePath)) {
            QObject::connect(pro, &Project::parsingFinished, [pro]() {
                emit SessionManager::instance()->projectFinishedParsing(pro);
            });
            QString restoreError;
            Project::RestoreResult restoreResult = pro->restoreSettings(&restoreError);
            if (restoreResult == Project::RestoreResult::Ok) {
                SessionManager::addProject(pro);
            } else {
                delete pro;
            }
        }

        //All is OK, project is initialized correctly, tell it to HMI
        setOptimRunnerInstalled(true);

    } else {
        qDebug() << tr("Failed opening project \"%1\": No plugin can open project type \"%2\".")
                    .arg(QDir::toNativeSeparators(fileName))
                    .arg(mt.name());
    }
}

bool OptimizationsTesterExtensionPlugin::optimRunnerInstalled() const {
    return mOptimRunnerInstalled;
}

void OptimizationsTesterExtensionPlugin::setOptimRunnerInstalled(bool pOptimRunnerInstalled) {
    if (mOptimRunnerInstalled != pOptimRunnerInstalled ){
        mOptimRunnerInstalled = pOptimRunnerInstalled ;
        emit optimRunnerInstalledChanged();
    }
}

} // namespace Internal
} // namespace OptimizationsTesterExtension
