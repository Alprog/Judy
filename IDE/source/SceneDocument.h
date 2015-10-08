
#pragma once

#include "Document.h"
#include <QTimer>
#include "Node.h"
#include "RenderTarget.h"

class SceneDocument : public IDocument
{
    Q_OBJECT

public:
    SceneDocument(Path path);
    virtual DocumentType GetType() const override;

    virtual bool Changed() const override;

private slots:
    void Render();

private:
    virtual void SetBinaryData(QByteArray data) override;
    virtual QByteArray GetBinaryData() override;

    Node* scene;
    RenderTarget* renderTarget;
    QTimer timer;
};
