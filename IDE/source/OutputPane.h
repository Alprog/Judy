
#pragma once

#include <QDockWidget>
#include <QTimer>
#include "Pipe.h"

class QTextEdit;

class OutputPane : public QDockWidget
{
    Q_OBJECT

public:
    OutputPane();
    ~OutputPane();

private slots:
    void clear();
    void work();

private:
    QTextEdit* edit;
    Pipe stdoutPipe;
    QTimer timer;
};
