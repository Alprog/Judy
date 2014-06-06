
#include "App.h"
#include "Window.h"

using namespace Judy;

int main(int argc, char *argv[])
{
    App* app = App::Instance();

    Window* windowA = Window::Create();
    app->Rendere = new Renderer(windowA, true);

    app->StartMainLoop();
}
