#include "performancecounter.hpp"
#include "threadlauncher.h"

#include <QFutureWatcher>
#include <QFuture>
#include <QtConcurrent/QtConcurrent>
#include <QThreadPool>

ThreadLauncher::ThreadLauncher()
{
    PerformanceCounter * beforePerformanceCounter = new PerformanceCounter(PerformanceCounter::UserCodeNumber::eCodeBefore);
    PerformanceCounter * afterPerformanceCounter = new PerformanceCounter(PerformanceCounter::UserCodeNumber::eCodeAfter);

    // New way
    QObject::connect(
        &watcherBeforeOptim, &QFutureWatcher<qint64>::finished,
        [=]() { qDebug() << "Time elapsed Before Optim : " << QString::number(watcherBeforeOptim.result()/ 1e6 ) << "ms"; } //  1 exponential 6 (ns->ms)
    );

    // Old fashion way
    QObject::connect(&watcherAfterOptim, SIGNAL(finished()), this, SLOT(onHandleFinished()));

    // Start the computation.

    // QtConcurrent::run( Object , Func, Parameters..)
    // Example : QFuture<int> future = QtConcurrent::run( &this->mJob, &MyJob::doSomething, QStirng("firstParam") );
    const QFuture<qint64> & beforeOptimFuture = QtConcurrent::run( beforePerformanceCounter, &PerformanceCounter::run );
    watcherBeforeOptim.setFuture(beforeOptimFuture);

    const QFuture<qint64> & afterOptimFuture = QtConcurrent::run( afterPerformanceCounter, &PerformanceCounter::run );
    watcherAfterOptim.setFuture(afterOptimFuture);
}

void ThreadLauncher::onHandleFinished()
{
    qint64 timeElapsed = watcherAfterOptim.result() ;
    qDebug() << "Time elapsed After Optim : " << QString::number(timeElapsed/ 1e6) << "ms"; //  1 exponential 6 (ns->ms)
}
