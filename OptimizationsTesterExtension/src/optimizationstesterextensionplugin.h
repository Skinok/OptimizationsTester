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

public:
    OptimizationsTesterExtensionPlugin();
    ~OptimizationsTesterExtensionPlugin();

    bool initialize(const QStringList &arguments, QString *errorString);
    void extensionsInitialized();
    ShutdownFlag aboutToShutdown();

public Q_SLOTS:
    void onQuickViewStatusChanged(QQuickView::Status status);
    void initializeOptimRunner();

private:
    void triggerAction();

    // Main QQuickView : HMI entry points
    QQuickView mQuickView;

    //**
    // Create all object needed for the plugin here
    //**
    CodeSamplesModel mModel;
    DataXMLReader * mXMLReader = nullptr;
};

} // namespace Internal
} // namespace OptimizationsTesterExtension
