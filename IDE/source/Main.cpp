
#include "IDE.h"

#include "MainWindow.h"

#include "Path.h"
#include <QDir>
#include <iostream>
#include <stdio.h>
#include "Utils.h"

int main(int argc, char *argv[])
{
    auto p1 = Path("D:\\Test\\../../../value//ef/efe");
    auto p2 = Path("./Test/../../efeg\\.././eg/");

    printf("%s %s\n", p1.c_str(), p2.c_str());
    fflush(stdout);
}

//int main(int argc, char *argv[])
//{
//    IDE ideApp(argc, argv);
//    return ideApp.Start();
//}

