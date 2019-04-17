#pragma once

#include "optimizationstester_global.h"

#include <extensionsystem/iplugin.h>

#include <QQuickView>

namespace OptimizationsTester {
namespace Internal {

class OptimizationsTesterPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QtCreatorPlugin" FILE "OptimizationsTester.json")

public:
    OptimizationsTesterPlugin();
    ~OptimizationsTesterPlugin();

    bool initialize(const QStringList &arguments, QString *errorString);
    void extensionsInitialized();
    ShutdownFlag aboutToShutdown();

public Q_SLOTS:
    void onQuickViewStatusChanged(QQuickView::Status status);

private:
    void triggerAction();

    // Main QQuickView : HMI entry points
    QQuickView mQuickView;
};

} // namespace Internal
} // namespace OptimizationsTester
