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

#include "performancecounter.hpp"
#include "threadlauncher.h"

#include <QFutureWatcher>
#include <QFuture>
#include <QtConcurrent/QtConcurrent>
#include <QThreadPool>

ThreadLauncher::ThreadLauncher()
{
}

void ThreadLauncher::initialize()
{
    PerformanceCounter * beforePerformanceCounter = new PerformanceCounter(PerformanceCounter::UserCodeNumber::eCodeBefore);
    PerformanceCounter * afterPerformanceCounter = new PerformanceCounter(PerformanceCounter::UserCodeNumber::eCodeAfter);

    // New way with lambda function
    QObject::connect(
        &watcherBeforeOptim, &QFutureWatcher<qint64>::finished,
        [=]() { qDebug() << "Execution time before optimizations : " << QString::number(watcherBeforeOptim.result()/ 1e6, 'f',2 ) << "ms"; } //  1e6 (ns->ms)
    );

    // New way to code slots with Qt 5
    QObject::connect(&watcherAfterOptim, &QFutureWatcher<qint64>::finished, this, &ThreadLauncher::onHandleFinished);

    // Start the computation in different threads thanks to QtConcurrent::run
    const QFuture<qint64> & beforeOptimFuture = QtConcurrent::run( beforePerformanceCounter, &PerformanceCounter::run );
    watcherBeforeOptim.setFuture(beforeOptimFuture);

    const QFuture<qint64> & afterOptimFuture = QtConcurrent::run( afterPerformanceCounter, &PerformanceCounter::run );
    watcherAfterOptim.setFuture(afterOptimFuture);
}

void ThreadLauncher::onHandleFinished()
{
    qint64 timeElapsed = watcherAfterOptim.result() ;
    qDebug() << "Execution time after optimizations  : " << QString::number(timeElapsed/ 1e6, 'f', 2) << "ms"; //  1e6 (ns->ms)
}
