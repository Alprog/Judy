
#include "SceneDocument.h"
#include <qlayout.h>
#include "IDE.h"
#if WINDOWS
#include "WinRenderTarget.h"
#endif
#include "Render/IRenderer.h"

SceneDocument::SceneDocument(Path path)
    : IDocument{path}
{
    auto canvas = new QWidget(nullptr);

    auto layout = new QGridLayout();
    layout->setSpacing(0);
    layout->setMargin(0);
    layout->addWidget(canvas);
    this->setLayout(layout);


#if WINDOWS
    auto hInstance = GetModuleHandle(nullptr);
    auto hWnd = (HWND)canvas->winId();
    renderTarget = new WinRenderTarget(hInstance, hWnd);
#endif
    Reload();

    connect(&timer, SIGNAL(timeout()), this, SLOT(Render()));

    IDE::Instance()->SelectScene(scene);
    IDE::Instance()->SelectNode(scene);

    timer.start(20);
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

#include "Render/RenderManager.h"
#include "Render/RendererType.h"

void SceneDocument::Render()
{
#if WINDOWS
    auto renderer = RenderManager::Instance()->renderers[(int)RendererType::GL];
    renderer->Render(scene, renderTarget);
#endif
}
