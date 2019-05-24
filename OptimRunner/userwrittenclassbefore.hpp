#ifndef USERWRITEDCLASSBEFORE_H
#define USERWRITEDCLASSBEFORE_H

#include <QElapsedTimer>

// Your includes here


class UserWrittenClassBefore{

public:

    UserWrittenClassBefore(){}

    qint64 checkPerformance(){
        // Start performance timer
        mTimer.start();

        //*******
        // Write your code below without any optimisation
        // This code will be compared to the one in UserWrittenClassAfter::checkPerformance
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
