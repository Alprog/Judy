
#include <vector>
#include <string>
#include <iostream>

#include <QObject>
#include <QString>
#include <QDir>

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
    for (auto& header : headers)
    {
        printf("%s\n", header.filePath().toStdString().c_str());
    }
}
