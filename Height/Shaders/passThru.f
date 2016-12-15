#version 430 core

uniform sampler2D textura0;
uniform sampler2D textura1;

out vec4 fColor;
in vec2 texCoord;

void main() {

    //fColor = texture(textura0,texCoord) + texture(textura1,texCoord);
	fColor = mix(texture(textura0,texCoord) , texture(textura1,texCoord), 1.0);

}
