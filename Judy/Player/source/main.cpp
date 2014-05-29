
#include "App.h"
#include "Window.h"

int main()
{
    App* app = App::Instance();

    JWindow* windowA = JWindow::Create();
    //JWindow* windowB = JWindow::Create();

    app->Rendere = new Renderer(windowA, true);
    //app->Rendere = new Renderer(windowB, false);

    app->StartMainLoop();

    while (true)
    {
    }
}
