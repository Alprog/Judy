
#pragma once

#include "BaseMenu.h"

class FileMenu : public BaseMenu
{
    Q_OBJECT

public:
    FileMenu(MainWindow* window);

private slots:
    void openFile();
    void saveFile();
    void saveAsFile();
    void compile();
};
