
#pragma once

#include "Document.h"
#include "SciLexer.h"
#include <QTimer>
#include "../qt/ScintillaEdit.h"
#include "string"

class TextEditor : public ScintillaEdit
{
    Q_OBJECT

public:
    TextEditor(QWidget* parent = 0);
    void setSource(std::string source);

    void getBreakpointLines();

private slots:
    void onMarginClicked(int position, int modifiers, int margin);
    void onLinesAdded(int arg);

    void tick();
    void onDwellStart(int x, int y);
    void onDwellEnd(int x, int y);

private:
    void init();
    void updateActiveLine();
    std::string source;

    QTimer timer;
    int mouseTime;
    QPoint mousePoint;
};
