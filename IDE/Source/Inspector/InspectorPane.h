
#pragma once

#include <QDockWidget>

class Node;
class QTreeView;
class NodeInspectorModel;

class InspectorPane : public QDockWidget
{
    Q_OBJECT

public:
    InspectorPane();
    ~InspectorPane();

private slots:
    void onSelectNode(Node* node);

private:
    QTreeView* tree;
};
