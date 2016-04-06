
#pragma once

#if MAC
    #include <OpenGL/gl.h>
#else
    #define GLEW_STATIC
    #include <GL/glew.h>
    #include <GL/gl.h>
#endif
