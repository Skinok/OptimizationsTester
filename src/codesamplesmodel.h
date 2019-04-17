#ifndef CODESAMPLESMODEL_H
#define CODESAMPLESMODEL_H

#include <QObject>

/*
 * This class will store the Data model read by the XML parser
 * It will store the code examples, and skeletons to help users in optimizations
*/
class CodeSamplesModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString skeletonBefore READ getSkeletonBefore WRITE setSkeletonBefore NOTIFY skeletonBeforeChanged )
    Q_PROPERTY(QString skeletonAfter READ getSkeletonAfter WRITE setSkeletonAfter NOTIFY skeletonAfterChanged )

    //Q_PROPERTY(QStringList examplesNames )

public:
    CodeSamplesModel( QObject * parent = nullptr );

    // Store each hpp file in a QString way to display it in code editors
    struct CodeSample{
        QString title;
        QString codeBefore;
        QString codeAfter;
    };

    /*
     * Skeleton code for live coding
    */
    inline void setSkeletonBefore(const QString& code){
        mSkeletonBefore = code;
        emit skeletonBeforeChanged();
    }
    inline void setSkeletonAfter(const QString& code){
        mSkeletonAfter = code;
        emit skeletonAfterChanged();
    }
    inline QString getSkeletonBefore() const{ return mSkeletonBefore; }
    inline QString getSkeletonAfter() const{ return mSkeletonAfter; }

    /*
     * Code Examples
    */
    void addExample(const CodeSample& codeSample);
    inline QVector<CodeSample> getExamples() const{ return mCodeExamples; }

Q_SIGNALS:

    void skeletonBeforeChanged();
    void skeletonAfterChanged();

private:
    /*
     * Code Skeletons for live coding HMI
     */
    QString mSkeletonBefore;
    QString mSkeletonAfter;

    /*
     * Many Examples
     */
    QVector<CodeSample> mCodeExamples;

};

#endif // CODESAMPLESMODEL_H
