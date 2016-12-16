#pragma once

#include <iostream>
#include "glm\mat4x4.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"
#include "Plane.h"
using namespace glm;
using namespace std;

class Application {
public:
	Application();
	~Application();

	void setup();
	void update();
	void display();
	void reshape(int w, int h);
	void loadShaders();
	GLuint initTexture(const std::string name);


private:
	string sVertex, sFragment;

	Plane oPlane;
	mat4 transformaciones;
	mat4 rotacionX, rotacionY, rotacionZ;

	mat4 look;
	mat4 cam;
	mat4 pers;
	mat4 orto;

	vec3 eye = vec3(0.0f, 40.0f, 110.0f);
	vec3 target = vec3(0.0f, 10.5f, -25.5f);
	vec3 up = vec3(0.0f, 1.0f, 0.0f);

	vec3 uMyLightPosition;
	mat3 mProyectionsMatrix;
};

