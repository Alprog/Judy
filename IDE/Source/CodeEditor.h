
#pragma once

#include "Document.h"
#include "SciLexer.h"
#include <QTimer>
#include "string"
#include "../qt/ScintillaEdit.h"

class CodeEditor : public Scintilla::ScintillaEdit
{
    Q_OBJECT

public:
    enum class Type
    {
        Unknown,
        Lua,
        HLSL
    };

    CodeEditor(Type type, QWidget* parent = 0);
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
    void init(Type type);
    void setLuaLexer();
    void setHlslLexer();

    std::string source;
    QTimer timer;
    int mouseTime;
    QPoint mousePoint;
};
