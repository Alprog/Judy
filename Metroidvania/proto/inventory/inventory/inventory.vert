#version 110

attribute vec2 pos;
attribute vec2 uv;
attribute vec4 color;

uniform mat3 mv;

varying vec2 uv0;
varying vec4 color0;

void main(void)
{
    uv0 = uv;
    color0 = color;

    gl_Position = vec4(vec2(mv*vec3(pos,1.0)),0.0,1.0);
}
