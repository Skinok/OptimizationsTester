#ifndef DATAXMLREADER_H
#define DATAXMLREADER_H


#include <QDomDocument>
#include <QIcon>
#include <QTreeWidget>

#include <QIcon>
#include <QXmlStreamReader>

#include "CodeSamplesModel.h"

class DataXMLReader
{
public:
    DataXMLReader(CodeSamplesModel * model = nullptr);

    bool read(QIODevice *device);

    QString errorString() const;

    static inline QString versionAttribute() { return QStringLiteral("version"); }

private:
    void readOptimizationsTester();
    void readLiveCoding();
    void readOptimizationExamples();
    void readExample();
    void readSkeleton();
    void readSkeletonBefore();
    void readSkeletonAfter();
    void readExampleBefore(CodeSamplesModel::CodeSample & CodeSample);
    void readExampleAfter(CodeSamplesModel::CodeSample & CodeSample);

    QString loadFileContent(const QString & fileName);

    // XML Reader
    QXmlStreamReader mReader;

    // Data Model filled by the XML Reader
    CodeSamplesModel * mModel;
};

#endif // DATAXMLREADER_H
