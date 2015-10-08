
#pragma once

#include <QDockWidget>

class Node;
class QTableView;
class NodeInspectorModel;

class InspectorPane : public QDockWidget
{
    Q_OBJECT

public:
    InspectorPane();
    ~InspectorPane();

private slots:
    void OnSelectNode(Node* node);

private:
    QTableView* table;
};
