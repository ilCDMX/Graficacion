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

Application::Application() : oPlane() { }

Application::~Application() { }

void Application::loadShaders() {
	sVertex = loadTextFile("Shaders/gouradPlane.v");
	sFragment = loadTextFile("Shaders/passThru.f");
}

void Application::setup() {


	oPlane.fAngleX = 0.0;
	oPlane.fAngleY = 0.0;
	oPlane.fAngleZ = 0.0;

	oPlane.createPlane(30);

	sVertex = loadTextFile("Shaders/gouradPlane.v");
	sFragment = loadTextFile("Shaders/passThru.f");

	InitializeProgram(oPlane.shader, sVertex, sFragment);

	oPlane.uTransform[0] = glGetUniformLocation(oPlane.shader, "mTransform");
	oPlane.uTheColor = glGetUniformLocation(oPlane.shader, "theColor");
	oPlane.uTime[0] = glGetUniformLocation(oPlane.shader, "fTime");
	oPlane.uEye[0] = glGetUniformLocation(oPlane.shader, "vEye");
//	uMyLightPosition[0] = glGetUniformLocation(oPlane.shader, "myLightPosition");

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

	glEnable(GL_DEPTH_TEST); // Field of view
}

void Application::update() {

	oPlane.fAngleY += 0.01f;
	oPlane.time += 0.001f;

}


void Application::display() {

	glClearColor(0.01f, 0.01f, 0.01f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (col > 0.8 || col < 0.007)
	{
		secBul = 1 - secBul;
	}

	if (secBul == 0)
		col += 0.0001f;
	else if (secBul == 1)
		col -= 0.0001f;

	glPolygonMode(GL_FRONT, GL_LINE);
	glUniform4fv(oPlane.uTheColor, 1, glm::value_ptr(glm::vec4(col, col, col, 1.0f)));
	/*if (oPlane.time >= 12)
	{
		bul = 1 - bul;
		oPlane.time = 0;
	}
	if (bul == 0)
	{
		//glPolygonMode(GL_FRONT, GL_FILL);
		glPolygonMode(GL_FRONT, GL_LINE);
		glUniform4fv(oPlane.uTheColor, 1, glm::value_ptr(glm::vec4(col, col,col, 1.0f)));
		//glUniform4fv(oPlane.uTheColor, 1, glm::value_ptr(glm::vec4(0.27f, 0.76f, 0.39f, 1.0f)));
	}
	else if (bul == 1)
	{
		glPolygonMode(GL_FRONT, GL_LINE);
		glUniform4fv(oPlane.uTheColor, 1, glm::value_ptr(glm::vec4(col, col, col, 1.0f)));
		//glUniform4fv(oPlane.uTheColor, 1, glm::value_ptr(glm::vec4(0.2f, 0.71f, 0.84f, 0.0f)));
	}*/


	glUseProgram(oPlane.shader);
	glBindVertexArray(oPlane.vao);


	look = glm::lookAt(eye, target, up);
	pers = glm::perspective(45.0f, (640.0f / 480.0f), 0.1f, 250.0f);
	cam = pers*look;

	rotacionY = glm::rotate(glm::mat4(1.0f), (oPlane.fAngleY * 3.141592f / 180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	transformaciones = rotacionX * rotacionY * rotacionZ;
	transformaciones = cam* transformaciones;

	glUniformMatrix4fv(oPlane.uTransform[0], 1, GL_FALSE, glm::value_ptr(transformaciones));
	glUniform1f(oPlane.uTime[0], oPlane.time);
	glUniform1f(oPlane.uEye[0], oPlane.eye);
	glDrawArrays(GL_TRIANGLES, 0, oPlane.getNumVertex());
}

void Application::reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}