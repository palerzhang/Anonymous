#version 400 core

out vec4 FragColor;

in vec2 texCoord;

uniform vec4 _Color;
uniform sampler2D mainTexture;

void main()
{
	FragColor = texture(mainTexture, texCoord) * _Color;
}