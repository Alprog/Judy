
#include "StackPane.h"
#include "RemotePlayer.h"
#include "QHeaderView.h"

StackPane::StackPane()
    : QDockWidget("Stack", 0, 0)
{
    setObjectName("Stack");

    setMinimumWidth(250);

    table = new QTableWidget();

    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->verticalHeader()->hide();

    table->setColumnCount(4);
    table->setRowCount(0);

    table->setColumnWidth(0, 35);
    table->setColumnWidth(1, 90);
    table->setColumnWidth(2, 90);
    table->setColumnWidth(3, 35);

    table->horizontalHeader()->setStretchLastSection(true);

    QStringList headers;
    headers << "#" << "Name" << "Source" << "Line";
    table->setHorizontalHeaderLabels(headers);

    table->setItem(0, 0, new QTableWidgetItem("Hello"));
    table->setItem(0, 1, new QTableWidgetItem("Hello"));

    setWidget(table);

    connect(&timer, SIGNAL(timeout()), this, SLOT(work()));
    timer.start(100);
}

void StackPane::work()
{
    auto& calls = RemotePlayer::Instance()->stack.calls;

    table->setRowCount(calls.size());
    for (int i = 0; i < calls.size(); i++)
    {
        auto& callInfo = calls[i];
        set(i, 0, std::to_string(i));
        set(i, 1, callInfo.name);
        set(i, 2, callInfo.source);
        set(i, 3, std::to_string(callInfo.line));

        table->setRowHeight(i, 20);
    }
}

void StackPane::set(int row, int col, std::string text)
{
    auto* item = new QTableWidgetItem();
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setTextAlignment(Qt::AlignCenter);
    item->setText(tr(text.c_str()));
    table->setItem(row, col, item);
}

StackPane::~StackPane()
{
}

