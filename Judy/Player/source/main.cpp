
#include "App.h"
#include "Window.h"

int main(int argc, char *argv[])
{
    App* app = App::Instance();

    //auto renderer = new DX11Renderer();

    Window* window = Window::Create();




    app->StartMainLoop();
}
