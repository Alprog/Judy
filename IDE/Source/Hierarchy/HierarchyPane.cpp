
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

    connect(IDE::getInstance(), SIGNAL(selectScene(Node*)), this, SLOT(onSelectScene(Node*)));

}

HierarchyPane::~HierarchyPane()
{
}

void HierarchyPane::onSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected)
{
    auto index = tree->selectionModel()->currentIndex();
    auto node = model.getNode(index);
    IDE::getInstance()->selectNode(node);
}

void HierarchyPane::onSelectScene(Node* scene)
{
    tree->setModel(nullptr);
    model.setNode(scene);
    tree->setModel(&model);

    connect(tree->selectionModel(), SIGNAL(selectionChanged(QItemSelection, QItemSelection)),
            this, SLOT(onSelectionChanged(QItemSelection, QItemSelection)));
}
