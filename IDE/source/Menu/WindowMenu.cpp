
#include "WindowMenu.h"

WindowMenu::WindowMenu(MainWindow* window)
    : BaseMenu{"Window", window}
{
    auto layoutMenu = addMenu(tr("&Layout"));
    for (int i = 0; i < 4; i++)
    {
        auto str = std::to_string(i);
        auto name = str.c_str();
        auto action = createAction(name, "", SLOT(Stub()));
        layoutMenu->addAction(action);
    }
}

void WindowMenu::Stub()
{
    window->documents->GetCurrentDocument()->toggle();
    window->documents->GetCurrentDocument()->toggle();
}

//QByteArray ba;
//window->restoreState(ba, 0);
//    printf("save!\n");
//    ba = this->saveState(0);
