
#pragma once

#include "BaseMenu.h"
#include <QTimer>

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
