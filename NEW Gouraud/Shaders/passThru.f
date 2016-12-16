#version 430 core

out vec4 fColor; // Salida
in vec4 color;	 // Entrada

void main() {
	// Solo se maneja de 1 a 0

    fColor = color;
	//fColor = vec4(0.2, 0.2, 0.2, 0); 
}
