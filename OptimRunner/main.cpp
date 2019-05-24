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
