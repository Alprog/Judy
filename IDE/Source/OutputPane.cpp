
#include "OutputPane.h"
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "sstream"
#include "iostream"
#include "stdio.h"

OutputPane::OutputPane()
    : QDockWidget("Output", 0, 0)
    , stdoutPipe(stdout)
{
    setObjectName("Output");

    auto layout = new QVBoxLayout();
    {
        layout->setMargin(0);

        auto hLayout = new QHBoxLayout();
        {
            hLayout->setMargin(0);

            auto button = new QPushButton("Clear");
            button->setIcon(QIcon());
            button->setMaximumSize(100, 30);
            hLayout->addWidget(button);
            connect(button, SIGNAL(clicked()), this, SLOT(clear()));

            //button = new QPushButton("Clear");
            //button->setMaximumSize(100, 30);
            //hLayout->addWidget(button);

            hLayout->addWidget(new QWidget);
        }
        layout->addLayout(hLayout);

        edit = new QTextEdit(nullptr);
        edit->setReadOnly(true);
        layout->addWidget(edit);
    }

    auto widget = new QWidget();
    widget->setLayout(layout);
    setWidget(widget);

    connect(&timer, SIGNAL(timeout()), this, SLOT(work()));
    timer.start(100);
}

void OutputPane::clear()
{
    edit->setPlainText(tr(""));
}

void OutputPane::work()
{
    fflush(stdout);

    auto text = stdoutPipe.readText();
    if (text.size() > 0)
    {
        edit->moveCursor(QTextCursor::End);
        edit->insertPlainText(text.c_str());
    }
}

OutputPane::~OutputPane()
{
}

