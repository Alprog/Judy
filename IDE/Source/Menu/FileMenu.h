
#pragma once

#include "BaseMenu.h"

class FileMenu : public BaseMenu
{
    Q_OBJECT

public:
    FileMenu(MainWindow* window);

private slots:
    void NewFile();
    void OpenFile();
    void SaveFile();
    void SaveAsFile();
};
