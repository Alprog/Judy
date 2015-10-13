
#include "InspectorPane.h"
#include <QHeaderView>
#include <QTreeView>
#include "../IDE.h"
#include "InspectorModel.h"

InspectorPane::InspectorPane()
    : QDockWidget("Inspector", 0, 0)
{
    setObjectName("Inspector");
    setMinimumWidth(250);

    tree = new QTreeView();
    setWidget(tree);

    connect(IDE::Instance(), SIGNAL(SelectNode(Node*)), this, SLOT(OnSelectNode(Node*)));
}

InspectorPane::~InspectorPane()
{
}

void InspectorPane::OnSelectNode(Node* node)
{
    auto model = new InspectorModel(node);
    tree->setModel(model);
}
