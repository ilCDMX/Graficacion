#pragma once

#include <iostream>
#include "Object3D.h"
#include "glm\mat4x4.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"
#include "Plane.h"
using namespace glm;

class Application {
public:
	Application();
	~Application();

	void setup();
	void update();
	void display();
	void reshape(int w, int h);
	void initTexture();
	
private:
	std::string sVertex, sFragment, vGourad;

	Plane oPlane;
	mat4 rotacionX, rotacionY, rotacionZ;
	mat4 transformaciones;
	mat4 look;
	mat4 cam;
	mat4 pers;

	vec3 eye=vec3(0.0f,30.0f,90.0f);
	vec3 target=vec3(0.0f,0.0f,-20.0f);
	vec3 up=vec3(0.0f,1.0f,0.0f);
	vec3 vEye;
	vec3 uMyLightPosition;
	mat3 mProyectionsMatrix;
};

