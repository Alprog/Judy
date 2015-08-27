
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

int main(int argc, char *argv[])
{
    CodeParser parser;

    auto dir = QDir::current();
    dir.cd("../Engine/source");
    auto headers = getFiles(dir, {"*.h"});
    for (auto& header : headers)
    {
        auto text = getFileText(header);
        parser.parse(text);
    }

    CodeGenerator generator;
    for (auto classInfo : parser.getClasses())
    {
        auto text = generator.Generate(classInfo);
        printf("%s \n", text.c_str());
    }
}
