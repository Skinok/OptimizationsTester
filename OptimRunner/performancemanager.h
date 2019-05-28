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

#ifndef PERFORMANCEMANAGER_H
#define PERFORMANCEMANAGER_H

#include <QObject>

class PerformanceManager : public QObject
{
    Q_OBJECT

    Q_PROPERTY( QString leftPerfoPercentage READ getLeftPerfoPercentage WRITE setLeftPerfoPercentage NOTIFY leftPerfoPercentageChanged )
    Q_PROPERTY( QString leftTimeElapsed READ getLeftTimeElapsed WRITE setLeftTimeElapsed NOTIFY leftTimeElapsedChanged )

    Q_PROPERTY( QString rightPerfoPercentage READ getRightPerfoPercentage WRITE setRightPerfoPercentage NOTIFY rightPerfoPercentageChanged )
    Q_PROPERTY( QString rightTimeElapsed READ getRightTimeElapsed WRITE setRightTimeElapsed NOTIFY rightTimeElapsedChanged )

public:
    PerformanceManager(QObject * parent = nullptr);

    inline QString getLeftTimeElapsed() const {
        return mLeftTimeElapsed;
    }
    inline QString getRightTimeElapsed() const {
        return mRightTimeElapsed;
    }
    inline QString getLeftPerfoPercentage() const {
        return mLeftPerfoPercentage;
    }
    inline QString getRightPerfoPercentage() const {
        return mRightPerfoPercentage;
    }

    inline void setLeftTimeElapsed(const QString & leftTimeElapsed) {
        mLeftTimeElapsed = leftTimeElapsed;
    }
    inline void setRightTimeElapsed(const QString & rightTimeElapsed) {
        mRightTimeElapsed = rightTimeElapsed;
    }
    inline void setLeftPerfoPercentage(const QString & leftPerfoPercentage) {
        mLeftPerfoPercentage = leftPerfoPercentage;
    }
    inline void setRightPerfoPercentage(const QString & rightPerfoPercentage) {
        mRightPerfoPercentage = rightPerfoPercentage;
    }

Q_SIGNALS:
    void leftPerfoPercentageChanged();
    void leftTimeElapsedChanged();
    void rightPerfoPercentageChanged();
    void rightTimeElapsedChanged();

private:

    QString mLeftPerfoPercentage;
    QString mLeftTimeElapsed;
    QString mRightPerfoPercentage;
    QString mRightTimeElapsed;

};

#endif // PERFORMANCEMANAGER_H
