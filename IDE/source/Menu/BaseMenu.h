
#pragma once

#include <QMenu>

class BaseMenu : public QMenu
{
    Q_OBJECT

public:
    BaseMenu(std::string name);

    QAction* addAction(const char* name, std::string iconName, const char* slot,
                       const QKeySequence& shortcut = QKeySequence::UnknownKey);
};
