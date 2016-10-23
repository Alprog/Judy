
attribute vec4 a_position;
attribute vec2 a_texCoord;
attribute vec4 a_color;

varying vec2 v_texCoord;
varying vec4 v_color;
varying vec3 pos;

uniform mat4 MVP;

void main()    
{
    gl_Position = a_position * transpose(MVP);
	pos = gl_Position.xyz / gl_Position.w;
    v_texCoord = a_texCoord;
	v_color = a_color;
}
