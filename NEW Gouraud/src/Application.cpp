#include "Application.h"
#include <iostream>
#include <vector>

#include "GL\glew.h"
#include <gl/GL.h>
#include <gl/GLU.h>

#include "glm\matrix.hpp"
#include "glm\gtc\type_ptr.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "ShaderFuncs.h"
#include "glm\vec3.hpp"

Application::Application() : plane()
							 
{

}

Application::~Application() 
{}

void Application::loadShaders() {
	sVertex = loadTextFile("Shaders/gouradPlane.v");
	sFragment = loadTextFile("Shaders/passThru.f");
}

void Application::setup() {
	eye = glm::vec3(0.0f, 50.0f, 100.0f);
	target = glm::vec3(0.0f, -50.0f, -10.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);

	plane.fAngleX = 0.0;
	plane.fAngleY = 0.0;
	plane.fAngleZ = 0.0;

	plane.createPlane(20);
	vEye = glm::vec3(0.0f, 100.0f, 100.0f);
	loadShaders();
	InitializeProgram(plane.shader, sVertex, sFragment);
	//InitializeProgram(plane.shader[1], sVertex, sFragment);

	plane.uTransform[0] = glGetUniformLocation(plane.shader, "mTransform");
	plane.uTime[0] = glGetUniformLocation(plane.shader, "fTime");
	plane.uEye[0] = glGetUniformLocation(plane.shader, "vEye");
	uMyLightPosition[0] = glGetUniformLocation(plane.shader, "myLightPosition");

	//plane.uTransform[1] = glGetUniformLocation(plane.shader[1], "mTransform");
	//plane.uTime[1] = glGetUniformLocation(plane.shader[1], "fTime");
	//plane.uEye[1] = glGetUniformLocation(plane.shader[1], "vEye");
	//uMyLightPosition[1] = glGetUniformLocation(plane.shader[1], "myLightPosition");

	glGenVertexArrays(1, &plane.vao);
	glBindVertexArray(plane.vao);
	glGenBuffers(1, &plane.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, plane.vbo);

	glBufferData(GL_ARRAY_BUFFER, plane.getVertexSizeInBytes() + plane.getTextureCoordsSizeInBytes(), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, plane.getVertexSizeInBytes(), plane.plane);
	glBufferSubData(GL_ARRAY_BUFFER, plane.getVertexSizeInBytes(), plane.getTextureCoordsSizeInBytes(), plane.textureCoords);
	plane.cleanMemory();

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glDrawArrays(GL_TRIANGLES, 0, plane.getNumVertex());
}

void Application::update() {
	//plane.fAngleX = plane.fAngleX + 0.011f;
	plane.fAngleY = plane.fAngleY + 0.011f;
	//plane.fAngleZ = plane.fAngleZ + 0.011f;
	plane.time = plane.time + 0.001f;
}


void Application::display() {
	//Borramos el buffer de color
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPolygonMode(GL_BACK, GL_LINE);
	//glPolygonMode(GL_FRONT, GL_LINE);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glUseProgram(plane.shader);
	glBindVertexArray(plane.vao);

	glm::mat4 myAllTransformations;
	rotationX = glm::rotate(glm::mat4(1.0f), (plane.fAngleX * 3.141592f / 180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	rotationY = glm::rotate(glm::mat4(1.0f), (plane.fAngleY * 3.141592f / 180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	rotationZ = glm::rotate(glm::mat4(1.0f), (plane.fAngleZ * 3.141592f / 180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	rotation = rotationX * rotationY * rotationZ;
	cam = glm::lookAt(eye, target, up);
	pers = glm::perspective(45.0f, (640.0f / 480.0f), 0.1f, 180.0f);
	rotation = pers * cam * rotation;

	glUniformMatrix4fv(plane.uTransform[0], 1, GL_FALSE, glm::value_ptr(rotation));
	glUniform1f(plane.uTime[0], plane.time);
	glUniform1f(plane.uEye[0], plane.eye);
	glDrawArrays(GL_TRIANGLES, 0, plane.getNumVertex());
}

void Application::reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

//myAllTransformations = glm::lookAt(vEye, glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0)) * myAllTransformations;

// Calculo de la proyección
//int heigth, width;
//glfwGetWindowSize(window, &width, &heigth);
//mProyectionsMatrix = glm::perspective(45.0f, (float)width / (float)heigth, 1.0f, 200.f);

// Acumulación de todas las transformaciones
//myAllTransformations = mProyectionsMatrix * myAllTransformations;