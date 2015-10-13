
#include "HierarchyPane.h"
#include <QHeaderView>
#include <QTreeView>
#include "../IDE.h"

HierarchyPane::HierarchyPane()
    : QDockWidget("Hierarchy", 0, 0)
{
    setObjectName("Hierarchy");
    setMinimumWidth(250);

    tree = new QTreeView();
    tree->setModel(&model);

    setWidget(tree);

    connect(IDE::Instance(), SIGNAL(SelectNode(Node*)), this, SLOT(OnSelectNode(Node*)));
}

HierarchyPane::~HierarchyPane()
{
}

void HierarchyPane::OnSelectNode(Node* node)
{
    model.SetNode(node);
}
