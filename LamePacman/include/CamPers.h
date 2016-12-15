#pragma once
#include "glm\mat4x4.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"
#include "glm\vec3.hpp"
#include "glm\vec4.hpp"

using namespace glm;

class CamPers
{
public:
	CamPers();
	~CamPers();

	vec3 eye, target, up, cubePos;

	void setup() {
		cubePos = vec3(0, 0, 0);
		eye = vec3(0, 0, 3);
		target = vec3(cubePos);
		up = vec3(0, 1, 0);
	}

	mat4 CEP(vec3 eye, vec3 target, vec3 up, float w, float h) {

		camara = lookAt(eye, target, up);

		perspectiva = perspective(45.0f, w / h, 0.1f, 50.0f); //fov en y°, aspect=w/h, zNear, zFar

		camaraEnPerspectiva = perspectiva*camara;

		return camaraEnPerspectiva;
	}

private:
	mat4 camara;
	mat4 perspectiva;
	mat4 camaraEnPerspectiva;
};

