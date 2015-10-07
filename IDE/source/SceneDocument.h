
#pragma once

#include "Document.h"

class SceneDocument : public IDocument
{
public:
    virtual bool Changed() override;

private:
    virtual void SetBinaryData(QByteArray data) override;
    virtual QByteArray GetBinaryData() override;
};
