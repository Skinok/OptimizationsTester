#include "codesamplesmodel.h"

#include <QVector>

CodeSamplesModel::CodeSamplesModel(QObject * parent)
    : QObject(parent)
{

}

void CodeSamplesModel::addExample(const CodeSample& codeSample){
    mCodeExamples.append(codeSample);
}
