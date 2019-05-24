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

    // Old fashion way to connect signal/slots in Qt
    QObject::connect(&watcherAfterOptim, SIGNAL(finished()), this, SLOT(onHandleFinished()));

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
