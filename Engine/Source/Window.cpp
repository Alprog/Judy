
#include "Window.h"
#include "Platforms.h"

#ifdef WIN
#include "GLRenderer.h"
#include "DXRenderer.h"
#endif

#include "Quad.h"
#include "Model.h"

WindowM* WindowM::Create()
{
    return new PlatformWindow();
}

WindowM::WindowM()
{
    auto model = new Model();

//    auto quad = new Quad();
//    quad->Size = Vector2(0.3f, 0.3f);

    scene = model;
    scene->transform.setScaling(Vector3::One * 0.3f);
}

WindowM::~WindowM()
{
    delete scene;
}

void WindowM::Update()
{
    scene->Update(0.0);
}

void WindowM::Render()
{
    renderer->Render(scene, renderTarget);
}

void WindowM::show()
{
}

