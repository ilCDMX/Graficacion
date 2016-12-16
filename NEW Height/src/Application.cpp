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


GLuint Application::initTexture(const std::string nameTexture) {
	// Soil pone la imagen de cabeza 
	GLuint id = 0;
	int imgWidth, imgHeight, rgb;
	unsigned char* img = NULL;
	img = SOIL_load_image(nameTexture.c_str(), &imgWidth, &imgHeight, &rgb, 0);

	glGenTextures(0, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
	SOIL_free_image_data(img); //hasta aqui se usa se requiere la imagen, se libera

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //se ve mejor, smooth //cercani
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);						//lejania

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); //s=x
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); //t=y

	glBindTexture(GL_TEXTURE_2D, 0);
	return id;
}

void Application::setup() {
	
	oPlane.fAngleY = 0.0;

	oPlane.createPlane(300);
	sVertex = loadTextFile("Shaders/passThru.v");
	sFragment = loadTextFile("Shaders/passThru.f");

	oPlane.texture_id[0] = initTexture("Lenna.png");
	oPlane.texture_id[1] = initTexture("Lenna.png");

	InitializeProgram(oPlane.shader, sVertex, sFragment);

	oPlane.uTransform[0] = glGetUniformLocation(oPlane.shader, "mTransform");
	oPlane.uTime[0] = glGetUniformLocation(oPlane.shader, "fTime");
	oPlane.uEye[0] = glGetUniformLocation(oPlane.shader, "vEye");
	uMyLightPosition[0] = glGetUniformLocation(oPlane.shader, "myLightPosition");

	oPlane.uTexture[0] = glGetUniformLocation(oPlane.shader, "textura0");
	oPlane.uTexture[1] = glGetUniformLocation(oPlane.shader, "textura1");

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
}

void Application::update() {
	oPlane.fAngleY += 0.06f;
}

void Application::display() {
	glClearColor(0.01f, 0.01f, 0.0f, 0.01f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	look = lookAt(eye, target, up);
	pers = perspective(45.0f, (640.0f / 480.0f), 0.1f, 250.0f);
	cam = pers*look;

	glBindVertexArray(oPlane.vao);

	rotacionY = rotate(glm::mat4(1.0f), (oPlane.fAngleY * 3.141592f / 180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	transformaciones = rotacionY;
	transformaciones = cam* transformaciones;

	glUseProgram(oPlane.shader);
	glUniformMatrix4fv(oPlane.uTransform[0], 1, GL_FALSE, glm::value_ptr(transformaciones));
	glUniform1f(oPlane.uTime[0], oPlane.time);
	glUniform1f(oPlane.uEye[0], oPlane.eye);
	glDrawArrays(GL_TRIANGLES, 0, oPlane.getNumVertex());

	glBindTexture(GL_TEXTURE_2D, oPlane.texture_id[0]);
	glUniform1i(oPlane.uTexture[0], 0);
	glActiveTexture(GL_TEXTURE0);


	glDrawArrays(GL_TRIANGLES, 0, oPlane.getNumVertex());
}

void Application::reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}