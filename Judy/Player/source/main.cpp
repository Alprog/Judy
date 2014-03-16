
#include "App.h"
#include "Window.h"

int main()
{
    App* app = App::Instance();
    Window* window = Window::Create();
    app->Rendere = new Renderer(window);

    app->StartMainLoop();

    return 0;
}
