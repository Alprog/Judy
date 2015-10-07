
#pragma once

#include "Document.h"

class SceneDocument : public DocumentM
{
private:
    virtual QByteArray GetTextData() override;
};
