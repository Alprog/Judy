
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

    connect(IDE::instance(), SIGNAL(selectNode(Node*)), this, SLOT(onSelectNode(Node*)));
}

InspectorPane::~InspectorPane()
{
}

void InspectorPane::onSelectNode(Node* node)
{
    auto model = new InspectorModel(node);
    tree->setModel(model);
    tree->expandAll();
}
