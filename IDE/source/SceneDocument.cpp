
#include "SceneDocument.h"
#include "IDE.h"

SceneDocument::SceneDocument(Path path)
    : IDocument{path}
{
    Reload();
}

DocumentType SceneDocument::GetType() const
{
    return DocumentType::Scene;
}

void SceneDocument::SetBinaryData(QByteArray data)
{  
    auto text = data.toStdString();
    auto& serializer = IDE::Instance()->serializer;
    scene = serializer.Deserialize<Node*>(text);
}

QByteArray SceneDocument::GetBinaryData()
{
    auto& serializer = IDE::Instance()->serializer;
    auto text = serializer.Serialize(scene);
    return QByteArray::fromStdString(text);
}

bool SceneDocument::Changed() const
{
    return false;
}
