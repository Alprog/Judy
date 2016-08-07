
#include "CodeEditor.h"
#include <QWidget>
#include "LuaMachine/LuaMachine.h"
#include <QMouseEvent>
#include "RemotePlayer.h"
#include "Utils.h"

int RGB(int r, int g, int b)
{
    return r | g << 8 | b << 16;
}

const int black = RGB( 0, 0, 0 );
const int white = RGB( 220, 220, 220 );
const int green = RGB( 87, 166, 74 );
const int red = RGB( 229, 20, 0 );
const int rust = RGB( 214, 156, 66 );
const int gray = RGB( 128, 128, 139 );
const int blue = RGB( 66, 156, 214 );
const int blueSelect = RGB(38, 79, 129);
const int darkBack = RGB(30, 30, 30);
const int lightBack = RGB(51, 51, 51);
const int sunglow = RGB(255, 216, 56);

const int TextMarginStyle = 1;

const int dwellStartTime = 500;
const int tickInterval = 50;

enum Markers
{
    Breakpoint,
    ActiveLine
};

CodeEditor::CodeEditor(QWidget* parent)
    : ScintillaEdit(parent)
    , mouseTime{0}
    , mousePoint{0, 0}
{
    init();
}

void CodeEditor::setSource(std::string source)
{
    this->source = source;
}

void CodeEditor::init()
{
    setTabWidth(4);

    setLexer(SCLEX_LUA);

    const char keyWords[] =
        "and break do else elseif end false for function goto if "
        "in nil not or repeat return require then true until while ";

    const char keyWords2[] = "local";

    setKeyWords(0, keyWords);
    setKeyWords(1, keyWords2);

    setCaretFore(white);
    styleSetFont(STYLE_DEFAULT, "Consolas");
    styleSetSize(STYLE_DEFAULT, 11);
    styleSetBack(STYLE_DEFAULT, darkBack);
    styleClearAll();

    setSelBack(true, blueSelect);

    int colors[20][2] =
    {
        { SCE_LUA_DEFAULT, white },
        { SCE_LUA_COMMENT, green },
        { SCE_LUA_COMMENTLINE, green },
        { SCE_LUA_COMMENTDOC, green },
        { SCE_LUA_NUMBER, rust },
        { SCE_LUA_WORD, blue },
        { SCE_LUA_STRING, rust },
        { SCE_LUA_CHARACTER, rust },
        { SCE_LUA_LITERALSTRING, rust },
        { SCE_LUA_PREPROCESSOR, white },
        { SCE_LUA_OPERATOR, gray },
        { SCE_LUA_IDENTIFIER, white },
        { SCE_LUA_STRINGEOL, green },
        { SCE_LUA_WORD2, blue },
        { SCE_LUA_WORD3, green },
        { SCE_LUA_WORD4, green },
        { SCE_LUA_WORD5, green },
        { SCE_LUA_WORD6, green },
        { SCE_LUA_WORD7, green },
        { SCE_LUA_WORD8, green }
    };

    for(int i = 0; i < 20; i++)
    {
        styleSetFore(colors[i][0], colors[i][1]);
    }

    styleSetSize(STYLE_LINENUMBER, 10);
    styleSetFore(STYLE_LINENUMBER, blue);
    styleSetBack(STYLE_LINENUMBER, darkBack);
    styleSetBack(TextMarginStyle, lightBack);
    connect(this, SIGNAL(linesAdded(int)), this, SLOT(onLinesAdded(int)));
    int INDEX;

    INDEX = 0;
    setMarginTypeN(INDEX, SC_MARGIN_TEXT);
    setMarginMaskN(INDEX, (1 << Breakpoint) | (1 << ActiveLine));
    setMarginWidthN(INDEX, 14);
    setMarginSensitiveN(INDEX, true);
    connect(this, SIGNAL(marginClicked(int, int, int)), this, SLOT(onMarginClicked(int, int, int)));

    INDEX = 1;
    setMarginTypeN(INDEX, SC_MARGIN_NUMBER);
    setMarginMaskN(INDEX, 0);
    setMarginWidthN(INDEX, 40);

    INDEX = 2;
    setMarginTypeN(INDEX, SC_MARGIN_SYMBOL);
    setMarginMaskN(INDEX, SC_MASK_FOLDERS);
    setMarginWidthN(INDEX, 12);
    setMarginSensitiveN(INDEX, true);
    setAutomaticFold(SC_AUTOMATICFOLD_SHOW | SC_AUTOMATICFOLD_CLICK);
    setFoldMarginColour(true, darkBack);
    setFoldMarginHiColour(true, darkBack);
    setProperty("fold", "1");
    setProperty("fold.compact", "0");
    setProperty("fold.comment", "1");
    setProperty("fold.preprocessor", "1");

    markerDefine(SC_MARKNUM_FOLDER, SC_MARK_BOXPLUS);
    markerDefine(SC_MARKNUM_FOLDEREND, SC_MARK_BOXPLUSCONNECTED);
    markerDefine(SC_MARKNUM_FOLDEROPEN, SC_MARK_BOXMINUS);
    markerDefine(SC_MARKNUM_FOLDERSUB, SC_MARK_VLINE);
    markerDefine(SC_MARKNUM_FOLDERTAIL, SC_MARK_LCORNER);
    markerDefine(SC_MARKNUM_FOLDEROPENMID, SC_MARK_BOXMINUSCONNECTED);
    markerDefine(SC_MARKNUM_FOLDERMIDTAIL, SC_MARK_TCORNER);

    markerDefine(Breakpoint, SC_MARK_CIRCLE);
    markerSetFore(Breakpoint, white);
    markerSetBack(Breakpoint, red);

    markerDefine(ActiveLine, SC_MARK_SHORTARROW);
    markerSetFore(ActiveLine, black);
    markerSetBack(ActiveLine, sunglow);

    setMarginLeft(7);

    setMouseDwellTime(500);
    callTipSetBack(lightBack);
    callTipSetFore(white);

    connect(&timer, SIGNAL(timeout()), this, SLOT(tick()));
    timer.start(tickInterval);

    connect(RemotePlayer::Instance(), SIGNAL(StateChanged()), this, SLOT(updateActiveLine()));
}

void CodeEditor::tick()
{
    if (this->isVisible())
    {
        // dwellStart and dwellEnd signals not work properly
        // with toggle visiblity, so provide own mechanism
        auto point = this->mapFromGlobal(QCursor::pos());
        if (point == mousePoint)
        {
            if (mouseTime < dwellStartTime)
            {
                mouseTime += tickInterval;
                if (mouseTime >= dwellStartTime)
                {
                    onDwellStart(point.x(), point.y());
                }
            }
        }
        else
        {
            if (mouseTime >= dwellStartTime)
            {
                onDwellEnd(mousePoint.x(), mousePoint.y());
            }
            mousePoint = point;
            mouseTime = 0;
        }
    }
}

void CodeEditor::updateActiveLine()
{
    markerDeleteAll(ActiveLine);

    auto call = RemotePlayer::Instance()->GetActiveCall();
    if (call != nullptr && CaseInsensitiveCompare(call->source, source))
    {
        markerAdd(call->line - 1, ActiveLine);
    }
}

void CodeEditor::onLinesAdded(int arg)
{
    for (int i = 0; i < lineCount(); i++)
    {
       marginSetStyle(i, TextMarginStyle);
    }
    pushBreakpoints();
}

void CodeEditor::onDwellStart(int x, int y)
{
    return; // disable function

    auto pos = positionFromPoint(x, y);
    auto startPos = wordStartPosition(pos, true);
    auto endPos = wordEndPosition(pos, true);
    if (pos >= startPos && pos < endPos)
    {
        std::string text = get_text_range(startPos, endPos).constData();
        callTipCancel();
        callTipShow(pos, text.c_str());
    }
}

void CodeEditor::onDwellEnd(int x, int y)
{
    callTipCancel();
}

void CodeEditor::pullBreakpoints()
{
    markerDeleteAll(Breakpoint);

    auto lines = RemotePlayer::Instance()->GetBreakpoints(source);
    for (auto line : lines)
    {
        markerAdd(line - 1, Breakpoint);
    }
}

void CodeEditor::pushBreakpoints()
{
    Set<int> lines;

    int mask = (1 << Breakpoint);
    int line = 0;
    line = markerNext(line, mask);
    while (line >= 0)
    {
        lines.insert(line + 1);
        line = markerNext(line + 1, mask);
    }

    RemotePlayer::Instance()->SetBreakpoints(source, lines);
}

void CodeEditor::onMarginClicked(int position, int modifiers, int margin)
{
    auto line = lineFromPosition(position);
    if (markerGet(line) & (1 << Breakpoint))
    {
        markerDelete(line, Breakpoint);
    }
    else
    {
        markerAdd(line, Breakpoint);
    }

    pushBreakpoints();
}
