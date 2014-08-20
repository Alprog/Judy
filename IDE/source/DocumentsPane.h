
#pragma once

#include "QWidget.h"
#include "QTabWidget.h"
#include "string"

class DocumentsPane : public QWidget
{
    Q_OBJECT

public:
    DocumentsPane();

    void Add(std::string fileName);


    void resizeEvent(QResizeEvent* event) override;

private slots:
    void CloseTab(int index);
};
