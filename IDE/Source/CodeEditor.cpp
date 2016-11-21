
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

const int black = RGB(0, 0, 0);
const int white = RGB(220, 220, 220);
const int green = RGB(87, 166, 74);
const int red = RGB(229, 20, 0);
const int rust = RGB(214, 156, 66);
const int gray = RGB(128, 128, 139);
const int blue = RGB(66, 156, 214);
const int blueSelect = RGB(38, 79, 129);
const int darkBack = RGB(30, 30, 30);
const int lightBack = RGB(51, 51, 51);
const int sunglow = RGB(255, 216, 56);
const int shamrock = RGB(62, 201, 176);
const int moss = RGB(184, 215, 163);

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
    setTabWidth(4);

    setCaretFore(white);
    styleSetFont(STYLE_DEFAULT, "Consolas");
    styleSetSize(STYLE_DEFAULT, 11);
    styleSetBack(STYLE_DEFAULT, darkBack);
    styleClearAll();

    setSelBack(true, blueSelect);

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

    connect(RemotePlayer::getInstance(), SIGNAL(stateChanged()), this, SLOT(updateActiveLine()));
}

void CodeEditor::setText(std::string text)
{
    bool isReadOnly = readOnly();
    setReadOnly(false);
    Scintilla::ScintillaEdit::setText(text.c_str());
    setReadOnly(isReadOnly);
}

void CodeEditor::setSource(std::string source)
{
    this->source = source;
}

void CodeEditor::setHighlightType(HighlightType type)
{
    switch (type)
    {
        case HighlightType::Lua:
            setLuaLexer();
            break;

        case HighlightType::HLSL:
            setHlslLexer();
            break;

        default:
            styleSetFore(SCE_C_DEFAULT, white);
    }
}

void CodeEditor::setLuaLexer()
{
    setLexer(SCLEX_LUA);

    const char keyWords[] =
        "and break do else elseif end false for function goto if "
        "in nil not or repeat return require then true until while ";

    const char keyWords2[] = "local";

    setKeyWords(0, keyWords);
    setKeyWords(1, keyWords2);

    int colors[20][2] =
    {
        { SCE_LUA_DEFAULT, white },
        { SCE_LUA_COMMENT, green },
        { SCE_LUA_COMMENTLINE, green },
        { SCE_LUA_COMMENTDOC, green },
        { SCE_LUA_WORD, blue },
        { SCE_LUA_NUMBER, rust },
        { SCE_LUA_STRING, rust },
        { SCE_LUA_CHARACTER, rust },
        { SCE_LUA_LITERALSTRING, rust },
        { SCE_LUA_PREPROCESSOR, gray },
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
}

void CodeEditor::setHlslLexer()
{
    setLexer(SCLEX_CPP);

    const char keyWords[] =
        "AppendStructuredBuffer asm asm_fragment BlendState bool bool1 bool2 bool3 bool4 bool1x1 bool1x2 "
        "bool1x3 bool1x4 bool2x1 bool2x2 bool2x3 bool2x4 bool3x1 bool3x2 bool3x3 bool3x4 bool4x1 bool4x2 "
        "bool4x3 bool4x4 break Buffer ByteAddressBuffer case cbuffer centroid class column_major compile "
        "compile_fragment CompileShader const continue ComputeShader ConsumeStructuredBuffer default "
        "DepthStencilState DepthStencilView discard do double DomainShader dword else export extern false "
        "float float1 float2 float3 float4 float1x1 float1x2 float1x3 float1x4 float2x1 float2x2 float2x3 "
        "float2x4 float3x1 float3x2 float3x3 float3x4 float4x1 float4x2 float4x3 float4x4 for fxgroup "
        "GeometryShader groupshared half Hullshader if in inline inout InputPatch int int1 int2 int3 int4 "
        "int1x1 int1x2 int1x3 int1x4 int2x1 int2x2 int2x3 int2x4 int3x1 int3x2 int3x3 int3x4 int4x1 int4x2 "
        "int4x3 int4x4 interface line lineadj linear LineStream matrix min16float min10float min16int "
        "min12int min16uint namespace nointerpolation noperspective NULL out OutputPatch packoffset pass "
        "pixelfragment PixelShader point PointStream precise RasterizerState RenderTargetView return "
        "register row_major RWBuffer RWByteAddressBuffer RWStructuredBuffer RWTexture1D RWTexture1DArray "
        "RWTexture2D RWTexture2DArray RWTexture3D sample sampler SamplerState SamplerComparisonState shared "
        "snorm stateblock stateblock_state static string struct switch StructuredBuffer tbuffer technique "
        "technique10 technique11 texture Texture1D Texture1DArray Texture2D Texture2DArray Texture2DMS "
        "Texture2DMSArray Texture3D TextureCube TextureCubeArray true typedef triangle triangleadj "
        "TriangleStream uint uint1 uint2 uint3 uint4 uint1x1 uint1x2 uint1x3 uint1x4 uint2x1 uint2x2 uint2x3 "
        "uint2x4 uint3x1 uint3x2 uint3x3 uint3x4 uint4x1 uint4x2 uint4x3 uint4x4 uniform unorm unsigned "
        "vector vertexfragment VertexShader void volatile while";

    const char keyWords2[] =
        "SV_POSITION SV_TARGET POSITION COLOR";

    setKeyWords(0, keyWords);
    setKeyWords(1, keyWords2);

    int colors[20][2] =
    {
        { SCE_C_DEFAULT, white },
        { SCE_C_COMMENT, green },
        { SCE_C_COMMENTLINE, green },
        { SCE_C_COMMENTDOC, green },
        { SCE_C_NUMBER, rust },
        { SCE_C_WORD, blue },
        { SCE_C_STRING, rust },
        { SCE_C_CHARACTER, rust },
        { SCE_C_UUID, black },
        { SCE_C_PREPROCESSOR, gray },
        { SCE_C_OPERATOR, gray },
        { SCE_C_IDENTIFIER, white },
        { SCE_C_STRINGEOL, black },
        { SCE_C_VERBATIM, black },
        { SCE_C_REGEX, black },
        { SCE_C_COMMENTLINEDOC, green },
        { SCE_C_WORD2, moss },
        { SCE_C_COMMENTDOCKEYWORD, green },
        { SCE_C_COMMENTDOCKEYWORDERROR, green },
        { SCE_C_GLOBALCLASS, black }
    };

    for(int i = 0; i < 20; i++)
    {
        styleSetFore(colors[i][0], colors[i][1]);
    }
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

    auto call = RemotePlayer::getInstance()->getActiveCall();
    if (call != nullptr && caseInsensitiveCompare(call->source, source))
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

    auto lines = RemotePlayer::getInstance()->getBreakpoints(source);
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

    RemotePlayer::getInstance()->setBreakpoints(source, lines);
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
