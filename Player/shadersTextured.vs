
#version 330

attribute vec4 a_position;
attribute vec2 a_texCoord;
attribute vec4 a_color;

varying vec2 v_texCoord;
varying vec4 v_color;

uniform mat4 MVP;

void main()    
{                            
    gl_Position = MVP * a_position;
    v_texCoord = a_texCoord;
	v_color = a_color;
}