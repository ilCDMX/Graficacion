
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
	-1.0f, 1.0f, 1.0f, 1.0f, //v1
	-1.0f, -1.0f, 1.0f, 1.0f, //v2
	1.0f, 1.0f, 1.0f, 1.0f, //v3

	//  /|
	//  --
	-1.0f, -1.0f, 1.0f, 1.0f, //v2
	1.0f, -1.0f, 1.0f, 1.0f, //v4
	1.0f, 1.0f, 1.0f, 1.0f, //v3

	//v1, v4 opuestos \  :  v2, v3 opuestos /

//ARRIBA
	-1.0f, 1.0f, 1.0f, 1.0f, //v1
	1.0f, 1.0f, -1.0f, 1.0f, //v5
	-1.0f, 1.0f, -1.0f, 1.0f, //v6

	- 1.0f, 1.0f, 1.0f, 1.0f, //v1
	1.0f, 1.0f, 1.0f, 1.0f, //v3
	1.0f, 1.0f, -1.0f, 1.0f, //v5

//ABAJO y=-1.0 EIF = v2 :  EDF=v4
	-1.0f, -1.0f, 1.0f, 1.0f, //v2
	1.0f, -1.0f, -1.0f, 1.0f, //v7
	-1.0f, -1.0f, -1.0f, 1.0f, //v8

	-1.0f, -1.0f, 1.0f, 1.0f, //v2
	1.0f, -1.0f, 1.0f, 1.0f, //v4
	1.0f, -1.0f, -1.0f, 1.0f, //v7

//ATRAS
	-1.0f, 1.0f, -1.0f, 1.0f, //v6
	-1.0f, -1.0f, -1.0f, 1.0f, //v8
	1.0f, 1.0f, -1.0f, 1.0f, //v5

	-1.0f, -1.0f, -1.0f, 1.0f, //v8
	1.0f, -1.0f, -1.0f, 1.0f, //v7
	1.0f, 1.0f, -1.0f, 1.0f, //v5

//DERECHA
	1.0f, 1.0f, 1.0f, 1.0f, //v3
	1.0f, -1.0f, 1.0f, 1.0f, //v4
	1.0f, 1.0f, -1.0f, 1.0f, //v5

	1.0f, -1.0f, 1.0f, 1.0f, //v4
	1.0f, -1.0f, -1.0f, 1.0f, //v7
	1.0f, 1.0f, -1.0f, 1.0f,//v5

//IZQUIERDA
	-1.0f, 1.0f, 1.0f, 1.0f, //v1
	-1.0f, -1.0f, 1.0f, 1.0f, //v2
	-1.0f, 1.0f, -1.0f, 1.0f, //v6

	-1.0f, -1.0f, 1.0f, 1.0f, //v2
	-1.0f, -1.0f, -1.0f, 1.0f,//v8
	-1.0f, 1.0f, -1.0f, 1.0f, //v6

};


GLfloat vertexColors[] = {

	/*
	v1,4,5,8= 0.0, 0.0, 0.0, 1.0,
	v2,3,6,7 = 1.0, 1.0, 1.0, 1.0,
	*/
	0.1, 0.1, 0.1, 1.0,/*v1*/	0.6, 0.6, 0.6, 1.0,/*v2*/	0.6, 0.6, 0.6, 1.0,/*v3*/

	0.6, 0.6, 0.6, 1.0,/*v2*/	0.1, 0.1, 0.1, 1.0,/*v4*/	0.6, 0.6, 0.6, 1.0,/*v3*/

	0.1, 0.1, 0.1, 1.0,/*v1*/	0.1, 0.1, 0.1, 1.0,/*v5*/	0.6, 0.6, 0.6, 1.0,/*v6*/

	0.1, 0.1, 0.1, 1.0,/*v1*/	0.6, 0.6, 0.6, 1.0,/*v3*/	0.1, 0.1, 0.1, 1.0,/*v5*/

	0.6, 0.6, 0.6, 1.0,/*v2*/	0.6, 0.6, 0.6, 1.0,/*v7*/	0.1, 0.1, 0.1, 1.0,/*v8*/

	0.6, 0.6, 0.6, 1.0,/*v2*/	0.1, 0.1, 0.1, 1.0,/*v4*/	0.6, 0.6, 0.6, 1.0,/*v7*/

	0.6, 0.6, 0.6, 1.0,/*v6*/	0.1, 0.1, 0.1, 1.0,/*v8*/	0.1, 0.1, 0.1, 1.0,/*v5*/

	0.1, 0.1, 0.1, 1.0,/*v8*/	0.6, 0.6, 0.6, 1.0,/*v7*/	0.1, 0.1, 0.1, 1.0,/*v5*/

	0.6, 0.6, 0.6, 1.0,/*v3*/	0.1, 0.1, 0.1, 1.0,/*v4*/	0.1, 0.1, 0.1, 1.0,/*v5*/

	0.1, 0.1, 0.1, 1.0,/*v4*/	0.6, 0.6, 0.6, 1.0,/*v7*/	0.1, 0.1, 0.1, 1.0,/*v5*/

	0.1, 0.1, 0.1, 1.0,/*v1*/	0.6, 0.6, 0.6, 1.0,/*v2*/	0.6, 0.6, 0.6, 1.0,/*v6*/

	0.6, 0.6, 0.6, 1.0,/*v2*/	0.1, 0.1, 0.1, 1.0,/*v8*/	0.6, 0.6, 0.6, 1.0,/*v6*/
};

GLfloat pellets[] = {
	1.0,1.0,0.0,1.0,	1.0,1.0,0.0,1.0,	1.0,1.0,0.0,1.0,	1.0,1.0,0.0,1.0,	1.0,1.0,0.0,1.0,	1.0,1.0,0.0,1.0,

	1.0,1.0,0.0,1.0,	1.0,1.0,0.0,1.0,	1.0,1.0,0.0,1.0,	1.0,1.0,0.0,1.0,	1.0,1.0,0.0,1.0,	1.0,1.0,0.0,1.0,

	1.0,1.0,0.0,1.0,	1.0,1.0,0.0,1.0,	1.0,1.0,0.0,1.0,	1.0,1.0,0.0,1.0,	1.0,1.0,0.0,1.0,	1.0,1.0,0.0,1.0,

	1.0,1.0,0.0,1.0,	1.0,1.0,0.0,1.0,	1.0,1.0,0.0,1.0,	1.0,1.0,0.0,1.0,	1.0,1.0,0.0,1.0,	1.0,1.0,0.0,1.0,

	1.0,1.0,0.0,1.0,	1.0,1.0,0.0,1.0,	1.0,1.0,0.0,1.0,	1.0,1.0,0.0,1.0,	1.0,1.0,0.0,1.0,	1.0,1.0,0.0,1.0,

	1.0,1.0,0.0,1.0,	1.0,1.0,0.0,1.0,	1.0,1.0,0.0,1.0,	1.0,1.0,0.0,1.0,	1.0,1.0,0.0,1.0,	1.0,1.0,0.0,1.0,

};
GLfloat walls[] = {
	0.0, 0.3,0.3,1.0,	0.0, 0.3,0.3,1.0,	0.0, 0.3,0.3,1.0,	0.0, 0.3,0.3,1.0,	0.0, 0.3,0.3,1.0,	0.0, 0.3,0.3,1.0,

	0.0, 0.3,0.3,1.0,	0.0, 0.3,0.3,1.0,	0.0, 0.3,0.3,1.0,	0.0, 0.3,0.3,1.0,	0.0, 0.3,0.3,1.0,	0.0, 0.3,0.3,1.0,

	0.0, 0.3,0.3,1.0,	0.0, 0.3,0.3,1.0,	0.0, 0.3,0.3,1.0,	0.0, 0.3,0.3,1.0,	0.0, 0.3,0.3,1.0,	0.0, 0.3,0.3,1.0,
	
	0.0, 0.3,0.3,1.0,	0.0, 0.3,0.3,1.0,	0.0, 0.3,0.3,1.0,	0.0, 0.3,0.3,1.0,	0.0, 0.3,0.3,1.0,	0.0, 0.3,0.3,1.0,
	
	0.0, 0.3,0.3,1.0,	0.0, 0.3,0.3,1.0,	0.0, 0.3,0.3,1.0,	0.0, 0.3,0.3,1.0,	0.0, 0.3,0.3,1.0,	0.0, 0.3,0.3,1.0,
	
	0.0, 0.3,0.3,1.0,	0.0, 0.3,0.3,1.0,	0.0, 0.3,0.3,1.0,	0.0, 0.3,0.3,1.0,	0.0, 0.3,0.3,1.0,	0.0, 0.3,0.3,1.0,
};

Application::Application() 
{}

Application::~Application() 
{}

void Application::setup()
{
	std::string strVertexShader = loadTextFile("Shaders/passThru.vs");
	std::string strFragmentShader = loadTextFile("Shaders/passThru.fs");
	

	InitializeProgram(wall.shader, strVertexShader, strFragmentShader);
	wall.uniform = glGetUniformLocation(wall.shader, "transform");
	wall.uTheColor = glGetUniformLocation(wall.shader, "theColor");
	InitializeProgram(pellet.shader, strVertexShader, strFragmentShader);
	pellet.uniform = glGetUniformLocation(pellet.shader, "transform");
	
	//grados
	wall.fAngleX = 0.0;
	wall.fAngleY = 0.0;
	wall.fAngleZ = 0.0;

	wall.numVertex = 36;

	glGenVertexArrays(1, &wall.vao);
	glBindVertexArray(wall.vao);
	glGenBuffers(1, &wall.vbo);

	glBindBuffer(GL_ARRAY_BUFFER, wall.vbo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions)+sizeof(walls), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0/*offset*/, sizeof(vertexPositions), vertexPositions);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertexPositions), sizeof(walls), walls);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)sizeof(vertexPositions));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);


}

void Application::update()
{
	pellet.fAngleX += 10.011;
	pellet.fAngleY += 10.011;
	pellet.fAngleZ += 10.011;
	activeGhosts++;

}

//NO DESPLEGAR ESTO

void Application::display() {//i=x, j=y
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (!switchi)//false = perse
	{
	look = lookAt(eye, target, up);
	pers = perspective(45.0f, 640.0f / 480.0f, 0.1f, 100.0f);
	cam = pers*look;
	}
	else if (switchi)
	{
		cam = ortho(-1.0f, 21.0f, -1.0f, 21.0f)*rotate(mat4(1.0f), (-3.14f / 2.0f), vec3(1.0f, 0.0f, 0.0f));
	}


	/*
	counter++;
	if (counter >= 200)
	{
		mat4 camrot = rotate(mat4(1.0f), (90.0f * 3.141592f / 180.0f), vec3(0.0f, 1.0f, 0.0f));
		cam = camrot*cam;
		counter = 0;
	}*/

				glUseProgram(wall.shader);
				glBindVertexArray(wall.vao);
		for (int i = 11; i >=0; i--) {
	for (int j =11; j >= 0; j--) {

			if (laberinto[i][j] == 1) {
				traslacionX = glm::translate(glm::mat4(1.0f), glm::vec3(2.0f*i, 0.0f, 2.0f*j));
				

				transformaciones = cam* traslacionX;


				glUniform4fv(wall.uTheColor, 1, glm::value_ptr(glm::vec4(0.0f, 0.2f, 0.2f, 1.0f)));
				glUniformMatrix4fv(wall.uniform, 1, false, glm::value_ptr(transformaciones));
				glDrawArrays(GL_TRIANGLES, 0, wall.numVertex);

			}
			else if (laberinto[i][j] == 0)
			{
				traslacionX = glm::translate(glm::mat4(1.0f), glm::vec3(2.0f*i, 0.0f, 2.0f*j));
				
				rotacionX = glm::rotate(glm::mat4(1.0f), (pellet.fAngleX * 3.141592f / 180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
				rotacionY = glm::rotate(glm::mat4(1.0f), (pellet.fAngleY * 3.141592f / 180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
				rotacionZ = glm::rotate(glm::mat4(1.0f), (pellet.fAngleZ * 3.141592f / 180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
				transformaciones = rotacionX * rotacionY * rotacionZ;
				
				scalaX = glm::scale(glm::mat4(1.0f), glm::vec3(0.15, 0.15, 0.15));


				transformaciones = cam* traslacionX*transformaciones* scalaX;


				glUniform4fv(wall.uTheColor, 1, glm::value_ptr(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f)));

				glUniformMatrix4fv(wall.uniform, 1, false, glm::value_ptr(transformaciones));
				glDrawArrays(GL_TRIANGLES, 0, wall.numVertex);
			}
			else if (laberinto[i][j] == 2)
			{
				traslacionX = glm::translate(glm::mat4(1.0f), glm::vec3(2.0f*i, 0.0f, 2.0f*j));
				scalaX = glm::scale(glm::mat4(1.0f), glm::vec3(0.4, 0.8, 0.4));
				transformaciones = cam* traslacionX* scalaX;

				glUniform4fv(wall.uTheColor, 1, glm::value_ptr(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)));

				glUniformMatrix4fv(wall.uniform, 1, false, glm::value_ptr(transformaciones));
				glDrawArrays(GL_TRIANGLES, 0, wall.numVertex);
			}
		}
	}
}


void Application::reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}


