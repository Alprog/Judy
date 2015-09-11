
#include "BaseMenu.h"
#include "../MainWindow.h"

BaseMenu::BaseMenu(std::string name, MainWindow* window)
    : QMenu(tr(name.c_str()), window)
    , window{window}
{
}

QAction* BaseMenu::createAction(const char* name, std::string iconName, const char* slot, const QKeySequence& shortcut)
{
    auto action = new QAction(QObject::tr(name), this);
    if (iconName != "")
    {
        auto normalName = ":/images/" + iconName + ".png";
        auto disabledName = ":/images/" + iconName + "_disabled.png";

        QIcon icon;
        icon.addPixmap(QPixmap(normalName.c_str()));
        icon.addPixmap(QPixmap(disabledName.c_str()), QIcon::Disabled);
        action->setIcon(icon);
    }

    action->setShortcut(shortcut);
    connect(action, SIGNAL(triggered()), this, slot);
    return action;
}

QAction* BaseMenu::addAction(QAction* action)
{
    QMenu::addAction(action);
    return action;
}
