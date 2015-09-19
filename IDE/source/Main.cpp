
#include "IDE.h"

#include "MainWindow.h"

#include "Path.h"
#include <QDir>

int main(int argc, char *argv[])
{


    //auto a = QDir("D:\\Test").absolutePath().toStdString();

    auto absPath = Path("D:/Test");


    auto relPath = Path("/Test");

    absPath.Combine(relPath);

    std::string a = "some";
    absPath.Combine(a);



    auto relPath2 = Path("../Test");

}


//int main(int argc, char *argv[])
//{
//    IDE ideApp(argc, argv);
//    return ideApp.Start();
//}

