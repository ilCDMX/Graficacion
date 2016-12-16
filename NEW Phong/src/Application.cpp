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

Application::Application() : oPlane()
							 
{

}

Application::~Application() 
{}


void Application::setup() {


	oPlane.fAngleY = 0.0;
	oPlane.createPlane(20);

	sVertex = loadTextFile("Shaders/gouradPlane.v");
	sFragment = loadTextFile("Shaders/passThru.f");

	InitializeProgram(oPlane.shader, sVertex, sFragment);


	oPlane.uTransform[0] = glGetUniformLocation(oPlane.shader, "mTransform");
	oPlane.uTime[0] = glGetUniformLocation(oPlane.shader, "fTime");
	oPlane.uEye[0] = glGetUniformLocation(oPlane.shader, "vEye");
	uMyLightPosition[0] = glGetUniformLocation(oPlane.shader, "myLightPosition");

	

	glGenVertexArrays(1, &oPlane.vao);
	glBindVertexArray(oPlane.vao);
	glGenBuffers(1, &oPlane.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, oPlane.vbo);

	glBufferData(GL_ARRAY_BUFFER, oPlane.getVertexSizeInBytes() + oPlane.getTextureCoordsSizeInBytes(), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, oPlane.getVertexSizeInBytes(), oPlane.plane);
	glBufferSubData(GL_ARRAY_BUFFER, oPlane.getVertexSizeInBytes(), oPlane.getTextureCoordsSizeInBytes(), oPlane.textureCoords);
	oPlane.cleanMemory();

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);


	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glDrawArrays(GL_TRIANGLES, 0, oPlane.getNumVertex());
}

void Application::update() {
	
	oPlane.fAngleY += 0.011f;
	oPlane.time += 0.001f;
}


void Application::display() {

	glClearColor(0.01f, 0.01f, 0.01f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glPolygonMode(GL_BACK, GL_LINE);
	//glPolygonMode(GL_FRONT, GL_LINE);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glUseProgram(oPlane.shader);
	glBindVertexArray(oPlane.vao);

	pers = perspective(45.0f, (640.0f, 480.0f), 0.1f, 250.0f);
	look = lookAt(eye, target, up);
	cam = pers*look;

	rotacionY = rotate(mat4(1.0f), (oPlane.fAngleY * 3.141592f / 180.0f), glm::vec3(1.0f, 1.0f, 1.0f));
//	rotacionX= rotate(mat4(1.0f), (90 * 3.141592f / 180.0f), glm::vec3(0.0f, 0.0f, 1.0f));

	transformaciones = cam*rotacionX*rotacionY;
	
	glUniformMatrix4fv(oPlane.uTransform[0], 1, GL_FALSE, glm::value_ptr(transformaciones));
	glUniform1f(oPlane.uTime[0], oPlane.time);
	glUniform1f(oPlane.uEye[0], oPlane.eye);
	glDrawArrays(GL_TRIANGLES, 0, oPlane.getNumVertex());
}

void Application::reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}
