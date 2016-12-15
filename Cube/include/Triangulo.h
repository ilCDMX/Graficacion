#pragma once
#include "Object3D.h"
#include"CamPers.h"

class Triangulo
{
public:

	Triangulo() {}
	~Triangulo() {}

	Object3D triangle;
	CamPers cam;

	mat4 rotacion;
	mat4 rotacionX;
	mat4 rotacionY;
	mat4 rotacionZ;

	mat4 trianguloTransformado;

	void update() { rotar(); }

	mat4 TransformacionesTriangulo() {
		float ang = triangle.fAngleX;

		rotacionX = rotate(glm::mat4(1.0f), (triangle.fAngleX * 3.141592f / 180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		rotacionY = rotate(glm::mat4(1.0f), (triangle.fAngleY * 3.141592f / 180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		rotacionZ = rotate(glm::mat4(1.0f), (triangle.fAngleZ * 3.141592f / 180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		rotacion = rotacionX * rotacionY * rotacionZ;

		trianguloTransformado = cam.CEP(cam.eye, cam.target, cam.up, 1024, 720)*rotacion;

		return trianguloTransformado;
	}
	
	void rotar() {
		triangle.fAngleX = triangle.fAngleX + 0.016f;
		triangle.fAngleY = triangle.fAngleY + 0.016f;
		triangle.fAngleZ = triangle.fAngleZ + 0.016f;
	}

//private:


};

