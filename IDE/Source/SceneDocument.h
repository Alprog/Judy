
#pragma once

#include "Document.h"
#include <QTimer>
#include "Node.h"
#include "Render/RenderTarget.h"

class SceneDocument : public IDocument
{
    Q_OBJECT

public:
    SceneDocument(Path path);
    virtual DocumentType getType() const override;

    virtual bool changed() const override;

private slots:
    void render();

private:
    virtual void setBinaryData(QByteArray data) override;
    virtual QByteArray getBinaryData() override;

    Node* scene;
    RenderTarget* renderTarget;
    QTimer timer;
};
