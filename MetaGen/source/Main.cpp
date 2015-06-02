
#include <string>
#include <iostream>

#include <QObject>
#include <QString>
#include <QDir>

int main(int argc, char *argv[])
{
    auto dir = QDir::current();

    QString s = "../Engine/source";
    dir.cd(s);


    for (auto& info : dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot))
    {
        printf("%s\n", info.fileName().toStdString().c_str());
    }

    for (auto& info : dir.entryInfoList({"*.h"}, QDir::Files))
    {
        printf("%s\n", info.fileName().toStdString().c_str());
    }
}
