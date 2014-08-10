
#pragma once

#include "QTabWidget.h"
#include "string"

class DocumentsControl : public QTabWidget
{
    Q_OBJECT

public:
    DocumentsControl();

    void Add(std::string fileName);

private slots:
    void CloseTab(int index);
};
