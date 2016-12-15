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
#include "SOIL.h"

Application::Application() : oPlane() { }

Application::~Application() { }


void Application::initTexture() {

	int imgWidth, imgHeight, rgb;
	unsigned char* img = SOIL_load_image("lenna.png", &imgWidth, &imgHeight, &rgb, 0);
	glGenTextures(1, &oPlane.texture_id);
	glBindTexture(GL_TEXTURE_2D, oPlane.texture_id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
	SOIL_free_image_data(img); //ya no se necesita manejar la imagen

	
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
	

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); 
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Application::setup() {

	sVertex = loadTextFile("Shaders/passThru.v");
	sFragment = loadTextFile("Shaders/passThru.f");

	oPlane.createPlane(1);
	initTexture();

	InitializeProgram(oPlane.shader, sVertex, sFragment);
	
	oPlane.uTexture = glGetUniformLocation(oPlane.shader, "theTexture0");
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
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)oPlane.getVertexSizeInBytes());

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glEnable(GL_DEPTH_TEST); 
	
	oPlane.fAngleY = 0.0;

}

void Application::update() {
	oPlane.fAngleY += 0.005f; 

}


void Application::display() {

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindVertexArray(oPlane.vao);
	look = lookAt(eye, target, up);
	pers = perspective(45.0f, (640.0f / 480.f), 0.1f, 250.0f);
	cam = pers*look;

	rotacionY = glm::rotate(glm::mat4(1.0f), (oPlane.fAngleY * 3.141592f / 180.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	transformaciones = rotacionY;
	cam = glm::lookAt(eye, target, up);
	pers = glm::perspective(45.0f, (640.0f / 480.0f), 0.1f, 180.0f);
	transformaciones = pers * cam * transformaciones;

	glUseProgram(oPlane.shader);
	glUniformMatrix4fv(oPlane.uTransform[0], 1, GL_FALSE, glm::value_ptr(transformaciones));
	glUniform1f(oPlane.uTime[0], oPlane.time);
	glUniform1f(oPlane.uEye[0], oPlane.eye);
	glDrawArrays(GL_TRIANGLES, 0, oPlane.getNumVertex());

	glBindTexture(GL_TEXTURE_2D, oPlane.texture_id);
	glUniform1i(oPlane.uTexture, 0);
	glActiveTexture(GL_TEXTURE0);

	glDrawArrays(GL_TRIANGLES, 0, oPlane.getNumVertex());
}

void Application::reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}