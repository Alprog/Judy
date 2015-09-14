
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
    void set(int row, int col, std::string text);

private slots:
    void work();

private:
    QTableWidget* table;
    QTimer timer;
};
