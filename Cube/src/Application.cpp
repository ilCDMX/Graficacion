
#include "Application.h"
#include <iostream>
#include <vector>

#include "GL\glew.h"
#include <gl/GL.h>
#include <gl/GLU.h>

#include "ShaderFuncs.h"
#include "glm\vec3.hpp"

GLfloat vertexPositions[] = {
//FRENTE
	//   --
	//   |/
	-0.4f, 0.4f, 0.4f, 1.0f, //v1
	-0.4f, -0.4f, 0.4f, 1.0f, //v2
	0.4f, 0.4f, 0.4f, 1.0f, //v3

	//  /|
	//  --
	-0.4f, -0.4f, 0.4f, 1.0f, //v2
	0.4f, -0.4f, 0.4f, 1.0f, //v4
	0.4f, 0.4f, 0.4f, 1.0f, //v3

	//v1, v4 opuestos \  :  v2, v3 opuestos /

//ARRIBA
	-0.4f, 0.4f, 0.4f, 1.0f, //v1
	0.4f, 0.4f, -0.4f, 1.0f, //v5
	-0.4f, 0.4f, -0.4f, 1.0f, //v6

	- 0.4f, 0.4f, 0.4f, 1.0f, //v1
	0.4f, 0.4f, 0.4f, 1.0f, //v3
	0.4f, 0.4f, -0.4f, 1.0f, //v5

//ABAJO y=-0.4 EIF = v2 :  EDF=v4
	-0.4f, -0.4f, 0.4f, 1.0f, //v2
	0.4f, -0.4f, -0.4f, 1.0f, //v7
	-0.4f, -0.4f, -0.4f, 1.0f, //v8

	-0.4f, -0.4f, 0.4f, 1.0f, //v2
	0.4f, -0.4f, 0.4f, 1.0f, //v4
	0.4f, -0.4f, -0.4f, 1.0f, //v7

//ATRAS
	-0.4f, 0.4f, -0.4f, 1.0f, //v6
	-0.4f, -0.4f, -0.4f, 1.0f, //v8
	0.4f, 0.4f, -0.4f, 1.0f, //v5

	-0.4f, -0.4f, -0.4f, 1.0f, //v8
	0.4f, -0.4f, -0.4f, 1.0f, //v7
	0.4f, 0.4f, -0.4f, 1.0f, //v5

//DERECHA
	0.4f, 0.4f, 0.4f, 1.0f, //v3
	0.4f, -0.4f, 0.4f, 1.0f, //v4
	0.4f, 0.4f, -0.4f, 1.0f, //v5

	0.4f, -0.4f, 0.4f, 1.0f, //v4
	0.4f, -0.4f, -0.4f, 1.0f, //v7
	0.4f, 0.4f, -0.4f, 1.0f,//v5

//IZQUIERDA
	-0.4f, 0.4f, 0.4f, 1.0f, //v1
	-0.4f, -0.4f, 0.4f, 1.0f, //v2
	-0.4f, 0.4f, -0.4f, 1.0f, //v6

	-0.4f, -0.4f, 0.4f, 1.0f, //v2
	-0.4f, -0.4f, -0.4f, 1.0f,//v8
	-0.4f, 0.4f, -0.4f, 1.0f, //v6

};


GLfloat vertexColors[] = {

	/*
	v1,4,5,8= 0.0, 0.0, 0.0, 1.0,
	v2,3,6,7 = 1.0, 1.0, 1.0, 1.0,
	*/
	0.2, 0.2, 0.2, 1.0,//v1
	1.0, 1.0, 1.0, 1.0,//v2
	1.0, 1.0, 1.0, 1.0,//v3

	1.0, 1.0, 1.0, 1.0,//v2
	0.2, 0.2, 0.2, 1.0,//v4
	1.0, 1.0, 1.0, 1.0,//v3

	0.2, 0.2, 0.2, 1.0,//v1
	0.2, 0.2, 0.2, 1.0,//v5
	1.0, 1.0, 1.0, 1.0,//v6

	0.2, 0.2, 0.2, 1.0,//v1
	1.0, 1.0, 1.0, 1.0,//v3
	0.2, 0.2, 0.2, 1.0,//v5

	1.0, 1.0, 1.0, 1.0,//v2
	1.0, 1.0, 1.0, 1.0,//v7
	0.2, 0.2, 0.2, 1.0,//v8

	1.0, 1.0, 1.0, 1.0,//v2
	0.2, 0.2, 0.2, 1.0,//v4
	1.0, 1.0, 1.0, 1.0,//v7

	1.0, 1.0, 1.0, 1.0,//v6
	0.2, 0.2, 0.2, 1.0,//v8
	0.2, 0.2, 0.2, 1.0,//v5

	0.2, 0.2, 0.2, 1.0,//v8
	1.0, 1.0, 1.0, 1.0,//v7
	0.2, 0.2, 0.2, 1.0,//v5

	1.0, 1.0, 1.0, 1.0,//v3
	0.2, 0.2, 0.2, 1.0,//v4
	0.2, 0.2, 0.2, 1.0,//v5

	0.2, 0.2, 0.2, 1.0,//v4
	1.0, 1.0, 1.0, 1.0,//v7
	0.2, 0.2, 0.2, 1.0,//v5

	0.2, 0.2, 0.2, 1.0,//v1
	1.0, 1.0, 1.0, 1.0,//v2
	1.0, 1.0, 1.0, 1.0,//v6

	1.0, 1.0, 1.0, 1.0,//v2
	0.2, 0.2, 0.2, 1.0,//v8
	1.0, 1.0, 1.0, 1.0,//v6
};

Application::Application() 
{}

Application::~Application() 
{}

void Application::setup()
{
	std::string strVertexShader = loadTextFile("Shaders/passThru.vs");
	std::string strFragmentShader = loadTextFile("Shaders/passThru.fs");
	
	cam.setup();

	InitializeProgram(triangle.shader, strVertexShader, strFragmentShader);
	triangle.uniform = glGetUniformLocation(triangle.shader, "transform");
	//triangle.fAngle = 0.0;
	triangle.fAngleX = 0.0;
	triangle.fAngleY = 0.0;
	triangle.fAngleZ = 0.0;

	triangle.numVertex = 36;
	glGenVertexArrays(1, &triangle.vao);
	glBindVertexArray(triangle.vao);
	glGenBuffers(1, &triangle.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, triangle.vbo);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions)+sizeof(vertexColors), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0/*offset*/, sizeof(vertexPositions), vertexPositions);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertexPositions), sizeof(vertexColors), vertexColors);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)sizeof(vertexPositions));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
}

void Application::update()
{
	//triangulo.rotar();
	triangle.fAngleX += 1.016f;
	triangle.fAngleY += 1.016f;
	triangle.fAngleZ += 1.016f;

}


void Application::display()
{

	//Borramos el buffer de color
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//trianguloTransformado = TransformacionesTriangulo();
	
	//Seleccionamos los shaders a usar
	glUseProgram(triangle.shader);	
	
	//activamos el vertex array object y dibujamos
	glBindVertexArray(triangle.vao);

	//rotation = glm::rotate(glm::mat4(1.0f), (triangle.fAngle * 3.141592f / 180.0f), glm::vec3(1.0f, 1.0f, 1.0f));

	// Pasamos variables a variables uniform
	//glUniform1f(triangle.uniform, triangle.fAngle);
	glUniformMatrix4fv(triangle.uniform, // Variable Uniform que corresponde a la matriz
								1, // El arreglo de matrices solo tiene una matriz
								false, // No queremos que saque la transpuesta
								glm::value_ptr(TransformacionesTriangulo())); // Obtenemos el apuntador a los datos de la matriz

	glDrawArrays(GL_TRIANGLES, 0, triangle.numVertex);
}

void Application::reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}


mat4 Application::TransformacionesTriangulo()
{

	//mat4 ort = ortho(0.0f, 640.0f, 480.0f, 0.0f, 0.0f, 50.0f);
	rotacionX = glm::rotate(glm::mat4(1.0f), (triangle.fAngleX * 3.141592f / 180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	rotacionY = glm::rotate(glm::mat4(1.0f), (triangle.fAngleY * 3.141592f / 180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	rotacionZ = glm::rotate(glm::mat4(1.0f), (triangle.fAngleZ * 3.141592f / 180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	rotacion = rotacionX * rotacionY * rotacionZ;
	//mat4 orthogo = ortho(-2.0f, 2.0f, -2.0f, 2.0f);
	trianguloTransformado = cam.CEP(cam.eye,cam.target,cam.up,640,480)*rotacion;
	//trianguloTransformado = orthogo*rotacion;

	return trianguloTransformado;
}
