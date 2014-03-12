
#include "App.h"
#include "Window.h"

int main()
{
    App* app = App::Instance();
    Window* window = new Window();
    app->Renderer = new Renderer(window);

    app->StartMainLoop();

    return 0;
}
