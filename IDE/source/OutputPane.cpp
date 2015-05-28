
#include "OutputPane.h"
#include <QTextEdit>

#include "sstream"
#include "iostream"
#include "stdio.h"

OutputPane::OutputPane()
    : QDockWidget("Output", 0, 0)
    , stdoutPipe(stdout)
{
    setObjectName("Output");

    edit = new QTextEdit(nullptr);
    edit->setReadOnly(true);
    this->setWidget(edit);

    connect(&timer, SIGNAL(timeout()), this, SLOT(work()));
    timer.start(100);
}

void OutputPane::work()
{
    fflush(stdout);

    if (!stdoutPipe.isEof())
    {
        auto text = stdoutPipe.readText();
        edit->moveCursor(QTextCursor::End);
        edit->insertPlainText(text.c_str());
    }
}

OutputPane::~OutputPane()
{
}

