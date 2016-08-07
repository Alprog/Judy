
#pragma once

#include <QDockWidget>
#include <QTableWidget>
#include <QTimer>

class StackPane : public QDockWidget
{
    Q_OBJECT

public:
    StackPane();
    ~StackPane();

private:
    void Set(int row, int col, std::string text);

private slots:
    void OnDoubleClicked(const QModelIndex& index);
    void Work();

private:
    QTableWidget* table;
    QTimer timer;
};
