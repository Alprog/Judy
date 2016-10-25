
varying vec2 v_texCoord;
varying vec3 pos;

uniform sampler2D mainTexture;

void main()
{	
	gl_FragColor = texture2D(mainTexture, v_texCoord);
}
