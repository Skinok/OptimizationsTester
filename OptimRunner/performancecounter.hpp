/*
  This file is part of OptimizationTester
  Copyright (C) 2019 Skinok Todar on GitHub
  Author: Frederic Lambert <skinok.todar@gmail.com>
  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

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
