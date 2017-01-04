
#include "SceneDocument.h"
#include <qlayout.h>
#include "IDE.h"

#include <PlatformRenderTarget.h>

#include "Render/IRenderer.h"

SceneDocument::SceneDocument()
    : scene {nullptr}
{
    auto canvas = new QWidget(nullptr);

    auto layout = new QGridLayout();
    layout->setSpacing(0);
    layout->setMargin(0);
    layout->addWidget(canvas);
    this->setLayout(layout);

#if WIN
    auto hInstance = GetModuleHandle(nullptr);
    auto hWnd = (HWND)canvas->winId();
    renderTarget = new PlatformRenderTarget(hInstance, hWnd);
#endif

    connect(&timer, SIGNAL(timeout()), this, SLOT(render()));
    timer.start(20);
}

void SceneDocument::reload()
{
    IDocument::reload();
    if (scene)
    {
        IDE::getInstance()->selectScene(scene);
        IDE::getInstance()->selectNode(scene);
    }
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

QByteArray SceneDocument::getBinaryData() const
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
    auto manager = RenderManager::getInstance();
    manager->addRenderer(RendererType::DX);

    auto renderer = manager->getRenderer(RendererType::DX);
    if (renderer && scene)
    {
        renderer->render(scene, renderTarget);
    }
}

