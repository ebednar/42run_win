#version 410 core

out vec4 color;

in vec3 vColor;
in vec2 vTexCoord;

uniform sampler2D ourTexture;

void main()
{
	color = texture(ourTexture, vTexCoord) * vec4(vColor, 1.0f);
}