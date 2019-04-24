#include "optimizationstesterplugin.h"
#include "optimizationstesterconstants.h"
#include "codesamplesmodel.h"
#include "dataxmlreader.h"

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


void OptimizationsTesterPlugin::initializeOptimRunner(){

    /*ProjectExplorer::ProjectTree lTree;
    ProjectExplorer::Project *contextProject = ProjectExplorer::ProjectTree::currentProject();

    if( ! contextProject ){
        qWarning() << "This tester use the current setting of your current project. Please open a project before using it.";
        return;
    }

    QStringList lFilePaths;
    lFilePaths << lTempFileBefore.fileName() << lTempFileAfter.fileName() ;
    contextProject->rootProjectNode()->addFiles(lFilePaths);
    */

    //**
    // SOME RESEARCHES ON QT CREATOR CLASSES

    //
    // Build files
    //ProjectExplorer::BuildManager * lBuildManager = ProjectExplorer::BuildManager::instance();

    // ClangToolRunner::run(const QString &filePath, const QStringList &compilerOptions) ???


    //QmakeManager::buildFile()

    /*if (Core::IDocument *currentDocument= Core::EditorManager::currentDocument()) {
        const Utils::FileName file = currentDocument->filePath();
        Node *n = ProjectTree::nodeForFile(file);
        FileNode *node  = n ? n->asFileNode() : nullptr;
        Project *project = SessionManager::projectForFile(file);

        if (project && node)
            handleSubDirContextMenu(BUILD, true, project, node->parentProjectNode(), node);
    }*/

    //::handleSubDirContextMenu()
    /*void QmakeManager::handleSubDirContextMenu(QmakeManager::Action action, bool isFileBuild,
                                               Project *contextProject, Node *contextNode,
                                               FileNode *buildableFile)
    {*/

    /*QTemporaryFile lTempFileBefore, lTempFileAfter;

    if ( lTempFileBefore.open() ){

        QTextStream outBefore(&lTempFileBefore);
        outBefore << before;
        lTempFileBefore.close();
    }
    if ( lTempFileAfter.open() ){
        QTextStream outAfter(&lTempFileAfter);
        outAfter << after;
        lTempFileAfter.close();
    }*/

    //
    // SOLUTION WITHOUT CLANG : Need the file to be in a project sub dir : complicated
    //


//    const Utils::FileName file( QFileInfo(lTempFileBefore.fileName())) ;

    /*ProjectExplorer::Node *n = ProjectExplorer::ProjectTree::nodeForFile(Utils::FileName::fromString(lTempFileBefore.fileName()));
    ProjectExplorer::FileNode *node  = n ? n->asFileNode() : nullptr;


    // impossible to get a filenode because the file does not belong to a project sub dir
    buildConfiguration->setFileNodeBuild(node);


    ProjectExplorer::BuildManager::buildList(buildConfiguration->stepList(ProjectExplorer::Constants::BUILDSTEPS_BUILD));

    // Remove temporary files of the current project
    contextProject->rootProjectNode()->removeFiles(lFilePaths);
    */

    /*
     * CLANG SOLUTION
     */

            /*ClangToolRunControl::ClangToolRunControl(RunControl *runControl,
                                                 Target *target,
                                                 const FileInfos &fileInfos)
            : RunWorker(runControl)
            , m_projectBuilder(new ProjectBuilder(runControl, target->project(), this))
            , m_clangExecutable(Core::ICore::clangExecutable(CLANG_BINDIR))
            , m_temporaryDir("clangtools-XXXXXX")
            , m_target(target)
            , m_fileInfos(fileInfos)
        {
            addStartDependency(m_projectBuilder);

            ClangToolsProjectSettings *projectSettings = ClangToolsProjectSettingsManager::getSettings(
                target->project());
            if (projectSettings->useGlobalSettings())
                m_projectBuilder->setEnabled(ClangToolsSettings::instance()->savedBuildBeforeAnalysis());
            else
                m_projectBuilder->setEnabled(projectSettings->buildBeforeAnalysis());
        }

        void ClangToolRunControl::init()
        {
            setSupportsReRunning(false);
            m_projectInfoBeforeBuild = CppTools::CppModelManager::instance()->projectInfo(
                        m_target->project());

            BuildConfiguration *buildConfiguration = m_target->activeBuildConfiguration();
            QTC_ASSERT(buildConfiguration, return);
            m_environment = buildConfiguration->environment();

            ToolChain *toolChain = ToolChainKitInformation::toolChain(m_target->kit(),
                                                                      ProjectExplorer::Constants::CXX_LANGUAGE_ID);
            QTC_ASSERT(toolChain, return);
            m_targetTriple = toolChain->originalTargetTriple();
            m_toolChainType = toolChain->typeId();
        }
        */


/*

    QTemporaryFile lTempFileBefore, lTempFileAfter;

    if ( lTempFileBefore.open() ){

        QTextStream outBefore(&lTempFileBefore);
        outBefore << before;
        lTempFileBefore.close();
    }
    if ( lTempFileAfter.open() ){
        QTextStream outAfter(&lTempFileAfter);
        outAfter << after;
        lTempFileAfter.close();
    }


    QProcessEnvironment env(QProcessEnvironment::systemEnvironment());


    QString lClangBinDir;
    if ( ! env.contains("LLVM_BINDIR"))
    {
        qWarning() << "Please set Clang compiler env variable : LLVM_BINDIR";
        return;
    }
    else {
        lClangBinDir = env.value("LLVM_BINDIR");
    }

    QString qtCreatorsClang = Core::ICore::clangExecutable(lClangBinDir);
    if ( qtCreatorsClang.isEmpty() )
    {
        qWarning() << "Please set Clang compiler path before compiling optimizations files";
        return;
    }

    Project *contextProject = ProjectTree::currentProject();
    Target *target = contextProject->activeTarget();
    if (!target)
        return;

    BuildConfiguration *lBuildConfiguration = target->activeBuildConfiguration();
    QTC_ASSERT(lBuildConfiguration, return);
    Utils::Environment lEnvironment = lBuildConfiguration->environment();
*/
    /*
     *     ClangTidyClazyRunner(const CppTools::ClangDiagnosticConfig &diagnosticConfig,
                         const QString &clangExecutable,
                         const QString &clangLogFileDir,
                         const Utils::Environment &environment,
                         QObject *parent = nullptr);*/

    //ClangTools::Internal::ClangTool *tool = ClangTidyClazyTool::instance();
/*
    CppTools::ClangDiagnosticConfig lDiagnosticConfig = ClangTidyClazyTool::getDiagnosticConfig(contextProject);

    ClangTools::Internal::ClangTidyClazyRunner clangRunner(
                        lDiagnosticConfig,
                        qtCreatorsClang,
                        QDir::currentPath(), // todo : change this later for a better log path
                        lEnvironment,
                        this
                   );


    QStringList compilerOptions = {"-o", lTempFileBefore.fileName() + ".exe"};
    clangRunner.run(lTempFileBefore.fileName(), compilerOptions);

    // Or use :

    //bool QmakeMakeStep::init(QList<const BuildStep *> &earlierSteps);


    //ProjectExplorer::BuildStep lStep;




    //**
    // Run files
    //**

    //RunWorker

    // Average run stats

    // Send QML results
*/
}

} // namespace Internal
} // namespace OptimizationsTester
