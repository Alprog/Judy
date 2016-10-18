
#include "Window.h"
#include <PlatformWindow.h>

#ifdef WIN
#include "Render/GL/GLRenderer.h"
#include "Render/DX/DXRenderer.h"
#endif

#include "Quad.h"
#include "Model.h"
#include "Meta/Serializer.h"

Window* Window::create()
{
    return new PlatformWindow();
}

Window::Window()
{
    auto node = new Node();

    auto c1 = new Model();
    auto c2 = new Model();

//auto quad = new Quad();
//quad->Size = Vector2(0.3f, 0.3f);

    scene = node;
    scene->transform.setScaling(Vector3::One * 0.3f);

    scene->addChild(c1);
    scene->addChild(c2);

    c1->transform.setTranslation(Vector3(0.9f, 0.0f, -1.0f));
    c1->transform.setScaling(Vector3::One * 0.3f);
    c1->name = "child1";

    c2->transform.setTranslation(Vector3(-0.2f, 0.0f, 1.0f));
    c2->transform.setScaling(Vector3::One * 0.4f);
    c2->name = "child2";

    auto serializer = new Serializer();
    auto text = serializer->serialize(scene);
    printf(text.c_str());
    fflush(stdout);

    Node* obj = serializer->deserialize<Node*>(text);
    text = serializer->serialize(obj);
    printf(text.c_str());
    fflush(stdout);

    retain();
}

Window::~Window()
{
}

void Window::update()
{
    scene->update(0.0);

    static float a = 0;
    a += 0.003f;

    auto rotation = Quaternion::yawPitchRoll(0, 0, a);
    scene->transform.setRotation(rotation);

    //auto translation = Vector3(0, 0, 0);
    //scene->transform.setTranslation(translation);

    /*auto c = Vector3(1, 1, 1);
    auto b = c * Matrix::RotationZ(a);
    printf("%f %f %f\n", b.x, b.y, b.z);
    fflush(stdout);*/

    //scene->transform.setTranslation(Vector3(0, a, 0));
}

void Window::render()
{
    renderer->render(scene, renderTarget);
}

void Window::show()
{
}

