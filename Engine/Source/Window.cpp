
#include "Window.h"
#include "Platforms.h"

#ifdef WIN
#include "GLRenderer.h"
#include "DXRenderer.h"
#endif

#include "Quad.h"
#include "Model.h"
#include "Meta/Serializer.h"

WindowM* WindowM::Create()
{
    return new PlatformWindow();
}

WindowM::WindowM()
{
    auto model = new Model();

    auto c1 = new Model();
    auto c2 = new Model();

//auto quad = new Quad();
//quad->Size = Vector2(0.3f, 0.3f);

    scene = model;
    scene->transform.setScaling(Vector3::One * 0.3f);

    scene->AddChild(c1);
    scene->AddChild(c2);

    c1->transform.setTranslation(Vector3(2, 0, 0));
    c1->transform.setScaling(Vector3::One * 0.3f);
    c1->name = "child1";

    c2->transform.setTranslation(Vector3(-2, 0, 0));
    c2->transform.setScaling(Vector3::One * 0.4f);
    c2->name = "child2";

    auto serializer = new Serializer();
    auto text = serializer->Serialize(scene);
    //printf(text.c_str());
    //fflush(stdout);

    Node* obj = serializer->Deserialize<Node*>(text);
    text = serializer->Serialize(obj);
    //printf(text.c_str());
    //fflush(stdout);
}

WindowM::~WindowM()
{
    delete scene;
}

void WindowM::Update()
{
    scene->Update(0.0);

    static float a = 0;
    a += 0.003f;
    auto rotation = Quaternion::YawPitchRoll(a / 2, a, a / 2);
    scene->transform.setRotation(rotation);

}

void WindowM::Render()
{
    renderer->Render(scene, renderTarget);
}

void WindowM::show()
{
}

