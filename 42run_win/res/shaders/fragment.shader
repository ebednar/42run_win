#version 410 core

out vec4 color;

in vec2 vTexCoord;

uniform sampler2D ourTexture;

void main()
{
	color = texture(ourTexture, vTexCoord);
	//color = vec4( 1.0, 0.5, 0.5, 1.0 );
}