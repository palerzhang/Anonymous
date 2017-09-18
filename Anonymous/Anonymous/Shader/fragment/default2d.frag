#version 400 core

out vec4 FragColor;
uniform vec4 _Color;

void main()
{
	FragColor = _Color;
}