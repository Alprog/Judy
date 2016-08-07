
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

    connect(IDE::Instance(), SIGNAL(SelectScene(Node*)), this, SLOT(OnSelectScene(Node*)));

}

HierarchyPane::~HierarchyPane()
{
}

void HierarchyPane::OnSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected)
{
    auto index = tree->selectionModel()->currentIndex();
    auto node = model.GetNode(index);
    IDE::Instance()->SelectNode(node);
}

void HierarchyPane::OnSelectScene(Node* scene)
{
    tree->setModel(nullptr);
    model.SetNode(scene);
    tree->setModel(&model);

    connect(tree->selectionModel(), SIGNAL(selectionChanged(QItemSelection, QItemSelection)),
            this, SLOT(OnSelectionChanged(QItemSelection, QItemSelection)));
}
