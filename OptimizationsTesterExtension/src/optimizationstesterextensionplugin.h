#pragma once

#include "optimizationstesterextension_global.h"
#include "codesamplesmodel.h"
#include "dataxmlreader.h"

#include <extensionsystem/iplugin.h>

#include <QQuickView>

namespace OptimizationsTesterExtension {
namespace Internal {

class OptimizationsTesterExtensionPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QtCreatorPlugin" FILE "OptimizationsTesterExtension.json")

    Q_PROPERTY(bool optimRunnerInstalled READ optimRunnerInstalled WRITE setOptimRunnerInstalled NOTIFY optimRunnerInstalledChanged)

public:
    OptimizationsTesterExtensionPlugin();
    ~OptimizationsTesterExtensionPlugin();

    bool initialize(const QStringList &arguments, QString *errorString);
    void extensionsInitialized();
    ShutdownFlag aboutToShutdown();

    bool optimRunnerInstalled() const;
    void setOptimRunnerInstalled(bool pOoptimRunnerInstalled);

public Q_SLOTS:
    void onQuickViewStatusChanged(QQuickView::Status status);
    void initializeOptimRunner();

signals:
    void optimRunnerInstalledChanged();

private:
    void triggerAction();

    // Main QQuickView : HMI entry points
    QQuickView mQuickView;

    //**
    // Create all object needed for the plugin here
    //**
    CodeSamplesModel mModel;
    DataXMLReader * mXMLReader = nullptr;

    bool mOptimRunnerInstalled = false;
};

} // namespace Internal
} // namespace OptimizationsTesterExtension
