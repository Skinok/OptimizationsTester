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

    ThreadLauncher lThreadLauncher;

    // Main QQuickView : HMI entry points
    /*QQuickView lViewer();

    PerformanceManager perfoMgr;
    lViewer.rootContext()->setContextProperty("PerformanceMgr", &perfoMgr);
    */

    return a.exec();
}
