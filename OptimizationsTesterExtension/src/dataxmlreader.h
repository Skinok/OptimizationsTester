#ifndef DATAXMLREADER_H
#define DATAXMLREADER_H


#include <QDomDocument>
#include <QIcon>

#include <QIcon>
#include <QXmlStreamReader>

#include "CodeSamplesModel.h"

class DataXMLReader
{
public:
    DataXMLReader(CodeSamplesModel * model = nullptr);

    /**
    * @brief read the XML entry file that references all hpp files used in examples tab
    * @param device : file to load
    * @return
    */
    bool read(QIODevice *device);

    /**
     * @brief errorString : pre-formatted string to easily find errors
     * @return
     */
    QString errorString() const;

private:

    // XML Read functions
    void readOptimizationsTester();
    void readLiveCoding();
    void readOptimizationExamples();
    void readExample();
    void readSkeleton();
    void readSkeletonBefore();
    void readSkeletonAfter();
    void readExampleBefore(CodeSamplesModel::CodeSample & CodeSample);
    void readExampleAfter(CodeSamplesModel::CodeSample & CodeSample);

    /**
     * @brief loadFileContent Load the hpp files (examples) referenced in the XML entry file
     * @param fileName Relative file name
     * @return a string to easily display the code in QML text editors
     */
    QString loadFileContent(const QString & fileName);

    /**
     * @brief mReader XML Reader for the main entry files that reference all hpp files
     */
    QXmlStreamReader mReader;

    /**
     * @brief mModel Data Model filled by the XML Reader
     */
    CodeSamplesModel * mModel;
};

#endif // DATAXMLREADER_H
