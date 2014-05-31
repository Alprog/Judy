
#include "App.h"
#include "Window.h"

int main(int argc, char *argv[])
{
    App* app = App::Instance();

    JWindow* windowA = JWindow::Create();
    app->Rendere = new Renderer(windowA, true);

    app->StartMainLoop();

    while (true)
    {
    }
}
