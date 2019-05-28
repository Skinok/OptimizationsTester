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
