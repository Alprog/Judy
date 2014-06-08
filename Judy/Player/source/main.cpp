
#include "App.h"
#include "Window.h"

int main(int argc, char *argv[])
{
    App* app = App::Instance();

    Window* windowA = Window::Create();
    //app->Renderer = new Renderer(windowA, true);

    app->StartMainLoop();
}
