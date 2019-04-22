#include "performancemanager.h"

#include <projectexplorer/toolchainmanager.h>
#include <projectexplorer/kit.h>
#include <projectexplorer/kitchooser.h>
#include <projectexplorer/buildmanager.h>
#include <projectexplorer/runconfiguration.h>
#include <projectexplorer/session.h>
#include <projectexplorer/projecttree.h>
#include <projectexplorer/target.h>
#include <projectexplorer/project.h>
#include <projectexplorer/projectnodes.h>

#include <coreplugin/icore.h>

#include <qmakeprojectmanager/qmakebuildconfiguration.h>


#include <clangtools/clangtidyclazyrunner.h>
/*
 * #include <clangtools/clangtidyclazytool.h>
#include <clangtools/clangtool.h>
#include <clangtools/clangtoolsdiagnostic.h>
*/

#include <QTemporaryFile>
#include <QTextStream>

PerformanceManager::PerformanceManager(QObject * parent)
    : QObject(parent)
{

}

void PerformanceManager::compareLiveCoding(const QString & before, const QString & after){

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

    //
    // SOLUTION WITHOUT CLANG : Need the file to be in a project sub dir : complicated
    //
    ProjectExplorer::Project *contextProject = ProjectExplorer::ProjectTree::currentProject();

    if( ! contextProject ){
        qWarning() << "This tester use the current setting of your current project. Please open a project before using it.";
        return;
    }

    QStringList lFilePaths;
    lFilePaths << lTempFileBefore.fileName() << lTempFileAfter.fileName() ;
    contextProject->rootProjectNode()->addFiles(lFilePaths);
    //contextProject->ad

    QCoreApplication::processEvents();

    ProjectExplorer::Target *target = contextProject->activeTarget();
    if (!target)
        return;

    auto *buildConfiguration = qobject_cast<QmakeProjectManager::QmakeBuildConfiguration *>(target->activeBuildConfiguration());
    if (!buildConfiguration)
        return;

    ProjectExplorer::BuildStep step();
    step.run();


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
