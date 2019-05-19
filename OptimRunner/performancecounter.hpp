#ifndef THREADBEFORE_H
#define THREADBEFORE_H

#include <QObject>
#include <QRunnable>
#include <QDebug>
#include <QElapsedTimer>
#include <QSharedMemory>
#include <QThread>

#include "userwrittenclassbefore.hpp"
#include "userwrittenclassafter.hpp"

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
        // User writed function to check

        // Start timer into the if statement to avoid that the condition execution time interfer with the timer
        qint64 lTimeElapsed;
        if (mCodeNumber == UserCodeNumber::eCodeBefore){
            lTimeElapsed = mCodeBefore.checkPerformance();
        }
        else{
            lTimeElapsed = mCodeAfter.checkPerformance();
        }

        // Store in Shared Memory for the Qt Creator plugin to retreive it
        return lTimeElapsed;
    }

private:
    UserWrittenClassBefore mCodeBefore;
    UserWrittenClassAfter mCodeAfter;

    UserCodeNumber mCodeNumber;
};

#endif // THREADLAUNCHER_H
