
#include "StackPane.h"
#include "RemotePlayer.h"
#include <QHeaderView>
#include "IDE.h"

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

    connect(&timer, SIGNAL(timeout()), this, SLOT(Work()));
    connect(table, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(OnDoubleClicked(const QModelIndex&)));
    timer.start(100);
}

void StackPane::OnDoubleClicked(const QModelIndex& index)
{
    auto row = index.row();
    auto& calls = RemotePlayer::Instance()->stack.calls;
    if (row < calls.size())
    {
        IDE::Instance()->FollowToCall(calls[row]);
    }
}

void StackPane::Work()
{
    auto& calls = RemotePlayer::Instance()->stack.calls;

    table->setRowCount(calls.size());
    for (int i = 0; i < calls.size(); i++)
    {
        auto& callInfo = calls[i];
        Set(i, 0, std::to_string(i));
        Set(i, 1, callInfo.name);
        Set(i, 2, callInfo.source);
        Set(i, 3, std::to_string(callInfo.line));

        table->setRowHeight(i, 20);
    }
}

void StackPane::Set(int row, int col, std::string text)
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

