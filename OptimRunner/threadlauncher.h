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
