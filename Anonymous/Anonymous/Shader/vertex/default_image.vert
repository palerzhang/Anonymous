#version 400 core
layout (location = 0) in vec3 POSITION;
layout (location = 2) in vec2 TEXCOORD;

out vec2 texCoord;

void main()
{
	gl_Position = vec4(POSITION, 1.0f);
	texCoord = vec2(TEXCOORD.x, TEXCOORD.y);
}