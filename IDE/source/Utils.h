
#pragma once

class QAction;
class QKeySequence;

QAction* createAction(const char* name, std::string iconName, const char* slot,
                      const QKeySequence& shortcut = QKeySequence::UnknownKey);
