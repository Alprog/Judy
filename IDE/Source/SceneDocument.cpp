
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
    reload();

    connect(&timer, SIGNAL(timeout()), this, SLOT(render()));

    IDE::getInstance()->selectScene(scene);
    IDE::getInstance()->selectNode(scene);

    timer.start(20);
}

DocumentType SceneDocument::getType() const
{
    return DocumentType::Scene;
}

void SceneDocument::setBinaryData(QByteArray data)
{  
    auto text = data.toStdString();
    auto& serializer = IDE::getInstance()->serializer;
    scene = serializer.deserialize<Node*>(text);
}

QByteArray SceneDocument::getBinaryData()
{
    auto& serializer = IDE::getInstance()->serializer;
    auto text = serializer.serialize(scene);
    return QByteArray::fromStdString(text);
}

bool SceneDocument::changed() const
{
    return false;
}

#include "Render/RenderManager.h"
#include "Render/RendererType.h"

void SceneDocument::render()
{
#if WIN
    auto renderer = RenderManager::getInstance()->getRenderer(RendererType::GL);
    renderer->render(scene, renderTarget);
#endif
}

