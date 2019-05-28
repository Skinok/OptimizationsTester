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

#include <QCoreApplication>
#include <QDebug>
#include <QFutureWatcher>
#include <QFuture>
#include <QtConcurrent/QtConcurrent>
#include <QThreadPool>
#include <QQuickView>
#include <QQmlContext>

#include "performancecounter.hpp"
#include "performancemanager.h"
#include "threadlauncher.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //Thread Launcher will handle user code execution in various threads to speed up the tests
    ThreadLauncher lThreadLauncher;
    lThreadLauncher.initialize();

    // Performance Manager will be used to give user some statistics about the code execution
    // The better should be to execute the user code many times and calculate an average execution time for both code (before & after optimizations)
    //PerformanceManager perfoMgr;

    return a.exec();
}
