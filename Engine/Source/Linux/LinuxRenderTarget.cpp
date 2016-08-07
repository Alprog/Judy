
#include "LinuxRenderTarget.h"

LinuxRenderTarget::LinuxRenderTarget(Display* display, XWindow window)
    : display{display}
    , window{window}
{
}


Vector2 LinuxRenderTarget::GetSize() const
{
    return Vector2(100, 100);
}
