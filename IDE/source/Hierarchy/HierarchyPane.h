
#pragma once

#include <QDockWidget>
#include "HierarchyModel.h"

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
    void OnSelectNode(Node* node);

private:
    QTreeView* tree;
    HierarchyModel model;
};
