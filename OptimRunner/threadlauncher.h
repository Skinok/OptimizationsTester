#ifndef THREADLAUNCHER_H
#define THREADLAUNCHER_H

#include <QObject>
#include <QThreadPool>
#include <QFutureWatcher>

class ThreadLauncher : public QObject
{
    Q_OBJECT

public:
    ThreadLauncher();

    void initialize();

public slots:

    void onHandleFinished();

private:

    QFutureWatcher<qint64> watcherBeforeOptim,watcherAfterOptim;
};

#endif // THREADLAUNCHER_H
