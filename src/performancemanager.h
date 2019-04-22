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

public slots:
    void compareLiveCoding(const QString & before, const QString & after);

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
