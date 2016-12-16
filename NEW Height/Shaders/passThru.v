#version 430 core

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec2 vTextCoord;


uniform mat4 mTransform;
uniform sampler2D textura0;


out vec2 texCoord;

float heightMap (vec3 color) {
	return(0.35*color.r + 0.15*color.g + 0.50*color.b);
}

void main()
{
	vec4 newPos = vPosition;
	newPos.y = 4.0 * heightMap(texture(textura0, vTextCoord).rgb);
	texCoord = vTextCoord;
	gl_Position = mTransform * newPos;
}
