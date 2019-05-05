#include "dataxmlreader.h"

#include <QDebug>
#include <QFile>

DataXMLReader::DataXMLReader(CodeSamplesModel * model)
{
    mModel = model;

    if (! mModel)
    {
        qWarning() << "Model must be filled by the XML Reader, please provide it a valid CodeSamples Model";
    }
}

bool DataXMLReader::read(QIODevice *device)
{
    mReader.setDevice(device);

    qDebug() << "DataXMLReader::read";
    if (mReader.readNextStartElement()) {
        qDebug() << "mReader.name() = " << mReader.name();
        if (mReader.name() == QLatin1String("optimizationsTester")) {
            qDebug() << "readOptimizationsTester()";
            readOptimizationsTester();
        } else {
            mReader.raiseError(QObject::tr("The file is not an XBEL version 1.0 file."));
        }
    }

    return !mReader.error();
}

QString DataXMLReader::errorString() const
{
    return QObject::tr("%1\nLine %2, column %3")
            .arg(mReader.errorString())
            .arg(mReader.lineNumber())
            .arg(mReader.columnNumber());
}

void DataXMLReader::readOptimizationsTester()
{
    Q_ASSERT(mReader.isStartElement() && mReader.name() == QLatin1String("optimizationsTester"));

    while (mReader.readNextStartElement()) {
        if (mReader.name() == QLatin1String("liveCoding")){
            qDebug() << "readLiveCoding()";
            readLiveCoding();
        }
        else if (mReader.name() == QLatin1String("optimizationExamples")){
            qDebug() << "readOptimizationExamples()";
            readOptimizationExamples();
        }
        else
            mReader.skipCurrentElement();
    }
}

void DataXMLReader::readLiveCoding()
{
    Q_ASSERT(mReader.isStartElement() && mReader.name() == QLatin1String("liveCoding"));
    while (mReader.readNextStartElement()) {
        if (mReader.name() == QLatin1String("skeleton"))
            readSkeleton();
        else
            mReader.skipCurrentElement();
    }

    mReader.skipCurrentElement();
}

void DataXMLReader::readOptimizationExamples()
{
    Q_ASSERT(mReader.isStartElement() && mReader.name() == QLatin1String("optimizationExamples"));
    while (mReader.readNextStartElement()) {
        if (mReader.name() == QLatin1String("example"))
            readExample();
        else
            mReader.skipCurrentElement();
    }
}

void DataXMLReader::readExample()
{
    Q_ASSERT(mReader.isStartElement() && mReader.name() == QLatin1String("example"));

    CodeSamplesModel::CodeSample lCodeSample;
    while (mReader.readNextStartElement()) {
        if (mReader.name() == QLatin1String("before"))
            readExampleBefore(lCodeSample);
        else if (mReader.name() == QLatin1String("after"))
            readExampleAfter(lCodeSample);
        else
            mReader.skipCurrentElement();
    }

    mModel->addExample(lCodeSample);
}

void DataXMLReader::readSkeleton()
{
    Q_ASSERT(mReader.isStartElement() && mReader.name() == QLatin1String("skeleton"));

    while (mReader.readNextStartElement()) {
        if (mReader.name() == QLatin1String("before"))
            readSkeletonBefore();
        else if (mReader.name() == QLatin1String("after"))
            readSkeletonAfter();
        else
            mReader.skipCurrentElement();
    }
}

/*
 * End elements (leaf)
 * Read hpp files content and create Code Sample model element
 */

void DataXMLReader::readSkeletonBefore()
{
    Q_ASSERT(mReader.isStartElement() && mReader.name() == QLatin1String("before"));

    // Retrieve code sample file name from XML
    QString beforeExampleFileName = mReader.readElementText();

    // Insert file content in codeSample to be displayed in text editor later
    mModel->setSkeletonBefore( loadFileContent(beforeExampleFileName) );
}
void DataXMLReader::readSkeletonAfter()
{
    Q_ASSERT(mReader.isStartElement() && mReader.name() == QLatin1String("after"));

    // Retrieve code sample file name from XML
    QString afterExampleFileName = mReader.readElementText();

    // Insert file content in codeSample to be displayed in text editor later
    mModel->setSkeletonAfter( loadFileContent(afterExampleFileName) );
}
void DataXMLReader::readExampleBefore(CodeSamplesModel::CodeSample & codeSample)
{
    Q_ASSERT(mReader.isStartElement() && mReader.name() == QLatin1String("before"));

    // Retrieve code sample file name from XML
    QString beforeExampleFileName = mReader.readElementText();

    // Insert file content in codeSample to be displayed in text editor later
    codeSample.codeBefore = loadFileContent(beforeExampleFileName);
}

void DataXMLReader::readExampleAfter(CodeSamplesModel::CodeSample & codeSample)
{
    Q_ASSERT(mReader.isStartElement() && mReader.name() == QLatin1String("after"));

    // Retrieve code sample file name from XML
    QString afterExampleFileName = mReader.readElementText();

    // Insert file content in codeSample to be displayed in text editor later
    codeSample.codeAfter = loadFileContent(afterExampleFileName);
}

QString DataXMLReader::loadFileContent(const QString & fileName){

    // Verify that the file exists and can be opened
    QFile lFile(QString("%1/%2").arg("examples").arg(fileName));
    if (!lFile.open(QFile::ReadOnly | QFile::Text)){
        qWarning() << "File mentionned in examples.xml cannot be opened : " << fileName;
        return QString("");
    }

    // Create the text stream to read the hpp file
    QTextStream lInStream(&lFile);

    // Return the text content which contains all the hpp source code as string
    return lInStream.readAll();
}
