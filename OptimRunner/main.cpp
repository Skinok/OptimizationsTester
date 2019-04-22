#include <QCoreApplication>
#include <QDebug>
#include <QFutureWatcher>
#include <QFuture>
#include <QtConcurrent/QtConcurrent>
#include <QThreadPool>

#include "performancecounter.hpp"
#include "threadlauncher.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug() << "Main Thead : " << QThread::currentThread();

    ThreadLauncher lThreadLauncher;

    return a.exec();
}
