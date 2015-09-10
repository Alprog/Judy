
#pragma once

#include "BaseMenu.h"

class FileMenu : public BaseMenu
{
    Q_OBJECT

public:
    FileMenu();

private slots:
    void NewFile();
    void OpenFile();
    void SaveFile();
    void SaveAsFile();
};
