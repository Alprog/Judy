
#pragma once

#include "Document.h"
#include "Node.h"

class SceneDocument : public IDocument
{
public:
    SceneDocument(Path path);
    virtual DocumentType GetType() const override;

    virtual bool Changed() const override;

private:
    virtual void SetBinaryData(QByteArray data) override;
    virtual QByteArray GetBinaryData() override;

    Node* scene;
};
