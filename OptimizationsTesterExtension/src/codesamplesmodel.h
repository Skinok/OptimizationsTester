#ifndef CODESAMPLESMODEL_H
#define CODESAMPLESMODEL_H

#include <QObject>
#include <QVector>

/**
 * @brief The CodeSamplesModel class will store the Data model read by the XML parser
 */
class CodeSamplesModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString skeletonBefore READ getSkeletonBefore WRITE setSkeletonBefore NOTIFY skeletonBeforeChanged )
    Q_PROPERTY(QString skeletonAfter READ getSkeletonAfter WRITE setSkeletonAfter NOTIFY skeletonAfterChanged )    

public:

    CodeSamplesModel( QObject * parent = nullptr );

    /**
     * @brief The CodeSample struct represent an optimization example ( 1 title and 2 .hpp files )
     */
    struct CodeSample{
        CodeSample() {}
        CodeSample( const QString & pTitle, const QString & pCodeBefore, const QString & pCodeAfter)
            : title(pTitle), codeBefore(pCodeBefore), codeAfter(pCodeAfter)
            {  }
        QString title;
        QString codeBefore;
        QString codeAfter;
    };


    /**
     * @brief setSkeletonBefore Load the skeleton template (left) in live coding tab to help user coding its optimizations tests
     * @param code
     */
    inline void setSkeletonBefore(const QString& code){
        mSkeletonBefore = code;
        emit skeletonBeforeChanged();
    }
    inline QString getSkeletonBefore() const{ return mSkeletonBefore; }

    /**
     * @brief setSkeletonAfter Load the skeleton template (right) in live coding tab to help user coding its optimizations tests
     * @param code
     */
    inline void setSkeletonAfter(const QString& code){
        mSkeletonAfter = code;
        emit skeletonAfterChanged();
    }
    inline QString getSkeletonAfter() const{ return mSkeletonAfter; }

    /**
     * @brief addExample From the XML loader, add new examples in the model to be displayed in the Optimizations Examples tab
     * @param codeSample
     */
    void addExample(const CodeSample& codeSample);
    inline QVector<CodeSample> getExamples() const{ return mCodeExamples; }

Q_SIGNALS:

    void skeletonBeforeChanged();
    void skeletonAfterChanged();

private:

    QString mSkeletonBefore;
    QString mSkeletonAfter;

    /**
     * @brief List of all code examples
     */
    QVector<CodeSample> mCodeExamples;

};

#endif // CODESAMPLESMODEL_H
