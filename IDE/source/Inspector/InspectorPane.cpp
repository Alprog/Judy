
#include "InspectorPane.h"
#include <QHeaderView>
#include <QTableView>
#include "../IDE.h"
#include "NodeInspectorModel.h"

InspectorPane::InspectorPane()
    : QDockWidget("Inspector", 0, 0)
{
    setObjectName("Inspector");
    setMinimumWidth(250);

    table = new QTableView();
    setWidget(table);

    connect(IDE::Instance(), SIGNAL(SelectNode(Node*)), this, SLOT(OnSelectNode(Node*)));
}

InspectorPane::~InspectorPane()
{
}

void InspectorPane::OnSelectNode(Node* node)
{
    auto model = new NodeInspectorModel(node);
    table->setModel(model);
}
