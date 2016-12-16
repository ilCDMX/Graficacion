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


private:
	string sVertex, sFragment;
	string strVertexShader, strFragmentShader;

	Plane oPlane;
	mat4 transformaciones;
	mat4 rotacionY;
	mat4 rotacionX;


	mat4 look;
	mat4 pers;
	mat4 cam;

	vec3 eye=vec3(0.0f,2.0f,100.0f);
	vec3 target=vec3(0.0f,1.0f,-5.0f);
	vec3 up=vec3(0.0f, 1.0f, 0.0f);
	vec3 uMyLightPosition;

};

