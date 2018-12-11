
#include <PlatformRenderTarget.h>

LinuxRenderTarget::LinuxRenderTarget(Display* display, XWindow window)
    : display{display}
    , window{window}
{
}


Vector2 LinuxRenderTarget::getSize() const
{
    return Vector2(800, 800);
}

void LinuxRenderTarget::onRendering(RendererType type)
{

}
