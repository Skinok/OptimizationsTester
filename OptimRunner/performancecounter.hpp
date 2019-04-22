#ifndef THREADBEFORE_H
#define THREADBEFORE_H

#include <QObject>
#include <QRunnable>
#include <QDebug>
#include <QElapsedTimer>
#include <QSharedMemory>
#include <QThread>

#include "UserWritedClassBefore.hpp"
#include "UserWritedClassAfter.hpp"

class PerformanceCounter : public QObject
{
    Q_OBJECT

public:
    enum UserCodeNumber{
        eCodeBefore = 0,
        eCodeAfter
    };

    PerformanceCounter( PerformanceCounter::UserCodeNumber codeNumber)
    {
        mCodeNumber = codeNumber;
    }

    ~PerformanceCounter(){
    }

    qint64 run()
    {
        qDebug() << "run from thread before" << QThread::currentThread();

        // User writed function to check

        // Start timer into the if statement to avoid that the condition execution time interfer with the timer
        if (mCodeNumber == UserCodeNumber::eCodeBefore){
            mTimer.start();
            mCodeBefore.checkPerformance();
        }
        else{
            mTimer.start();
            mCodeAfter.checkPerformance();
        }

        // Store in Shared Memory for the Qt Creator plugin to retreive it
        return mTimer.nsecsElapsed() ;
    }

private:

    QElapsedTimer mTimer;

    UserWritedClassBefore mCodeBefore;
    UserWritedClassAfter mCodeAfter;

    UserCodeNumber mCodeNumber;
};

#endif // THREADLAUNCHER_H
