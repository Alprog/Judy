
#include <vector>
#include <string>
#include <iostream>

#include <QObject>
#include <QString>
#include <QDir>
#include <QTextStream>

#include "Parser/CodeParser.h"
#include "Generator/CodeGenerator.h"

std::vector<QFileInfo> getFiles(QDir dir, const QStringList& nameFilters)
{
    std::vector<QFileInfo> result;

    for (auto& info : dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot))
    {
        auto files = getFiles(QDir(info.absoluteFilePath()), nameFilters);
        result.insert(std::end(result), std::begin(files), std::end(files));
    }

    for (auto& info : dir.entryInfoList(nameFilters, QDir::Files))
    {
        result.push_back(info);
    }

    return result;
}

std::string getFileText(QFileInfo& fileInfo)
{
    std::string result = "";

    QFile file(fileInfo.absoluteFilePath());
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        result = stream.readAll().toStdString();
        file.close();
    }

    return result;
}

void writeToFile(std::string fileName, std::string content)
{
    QFile file(QString(fileName.c_str()));
    file.open(QIODevice::WriteOnly);
    QTextStream stream(&file);
    stream << QString(content.c_str());
    file.close();
}

int main(int /*argc*/, char* /*argv*/[])
{
    CodeParser parser;

    auto dir = QDir::current();
    dir.cd("../Engine/source");
    auto headersInfo = getFiles(dir, {"*.h"});
    for (auto& headerInfo : headersInfo)
    {
        auto text = getFileText(headerInfo);
        auto fileName = headerInfo.fileName().toStdString();
        parser.parse(text, fileName);
    }

    CodeGenerator generator;

    auto classes = parser.getClasses();

    auto headerText = generator.generateHeader(classes);
    auto sourceText = generator.generateSource(classes);
    writeToFile("../Engine/source/Meta/Meta.gen.h", headerText);
    writeToFile("../Engine/source/Meta/Meta.gen.cpp", sourceText);
}
