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
