
#include <vector>
#include <string>
#include <iostream>

#include <QObject>
#include <QString>
#include <QDir>
#include <QTextStream>

#include "Parser.h"

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

int main(int argc, char *argv[])
{
    auto dir = QDir::current();

    QString s = "../Engine/source";
    dir.cd(s);

    auto headers = getFiles(dir, {"*.h"});

    int i = 0;
    for (auto& header : headers)
    {
        QFile file(header.absoluteFilePath());

        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream stream(&file);
            std::string text = stream.readAll().toStdString();
            parse(text);
        }

        file.close();

        i++;
        if (i == 15) break;
    }
}
