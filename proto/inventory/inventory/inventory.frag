#version 110

uniform sampler2D tex;

varying vec2 uv0;
varying vec4 color0;

void main (void)
{
    gl_FragColor = texture2D(tex, uv0)*color0;
}

