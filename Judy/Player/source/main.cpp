
#include "App.h"
#include "Window.h"

int WinMain()
{
    App* app = App::Instance();
    Window* window = Window::Create();
    app->Rendere = new Renderer(window);

    app->StartMainLoop();

    return 0;
}
