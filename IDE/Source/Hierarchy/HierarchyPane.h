
#pragma once

#include <QDockWidget>
#include "HierarchyModel.h"
#include <QItemSelection>

class Node;
class QTreeView;
class NodeInspectorModel;

class HierarchyPane : public QDockWidget
{
    Q_OBJECT

public:
    HierarchyPane();
    ~HierarchyPane();

private slots:
    void onSelectScene(Node* scene);
    void onSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected);

private:
    QTreeView* tree;
    HierarchyModel model;
};
