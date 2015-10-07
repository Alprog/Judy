
#pragma once

#include "Document.h"

class SceneDocument : public IDocument
{
private:
    virtual QByteArray GetTextData() override;
};
