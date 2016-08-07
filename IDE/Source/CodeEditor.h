
#pragma once

#include "Document.h"
#include "SciLexer.h"
#include <QTimer>
#include "string"

#define Window SciWindow
#include "../qt/ScintillaEdit.h"
#undef Window

class CodeEditor : public ScintillaEdit
{
    Q_OBJECT

public:
    CodeEditor(QWidget* parent = 0);
    void setSource(std::string source);

    void pullBreakpoints();
    void pushBreakpoints();

private slots:
    void onMarginClicked(int position, int modifiers, int margin);
    void onLinesAdded(int arg);

    void tick();
    void onDwellStart(int x, int y);
    void onDwellEnd(int x, int y);

public slots:
    void updateActiveLine();

private:
    void init();

    std::string source;
    QTimer timer;
    int mouseTime;
    QPoint mousePoint;
};
