
#include "App.h"
#include "Window.h"

using namespace Judy;

int main(int argc, char *argv[])
{
    App* app = App::Instance();

    JWindow* windowA = JWindow::Create();
    app->Rendere = new Renderer(windowA, true);

    app->StartMainLoop();
}
