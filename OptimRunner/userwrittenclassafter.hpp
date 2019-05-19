#ifndef USERWRITEDCLASSAFTER_H
#define USERWRITEDCLASSAFTER_H

#include <QElapsedTimer>

// Your includes here


class UserWrittenClassAfter{

public:

    UserWrittenClassAfter(){}

    qint64 checkPerformance(){
        // Start performance timer
        mTimer.start();

        //*******
        // Write your code below with your optimisations
        // This code will be compared to the one in UserWrittenClassBefore::checkPerformance
        // Results will then be shown in output when you will run this executable (OptimRunner)
        //*******





        //*******
        //*******

        return mTimer.nsecsElapsed();
    }

private:
    //*****
    // Your class members here
    //*****



    //*****
    QElapsedTimer mTimer;
};

#endif // USERWRITEDCLASSBEFORE_H
