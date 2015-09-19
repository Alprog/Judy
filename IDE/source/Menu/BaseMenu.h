
#pragma once

#include <QMenu>
#include "../MainWindow.h"

class BaseMenu : public QMenu
{
    Q_OBJECT

public:
    BaseMenu(std::string name, MainWindow* window);

    QAction* createAction(const char* name, std::string iconName, const char* slot,
                          const QKeySequence& shortcut = QKeySequence::UnknownKey);

    QAction* addAction(QAction* action);

protected:
    MainWindow* window;
};
