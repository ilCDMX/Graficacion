#pragma once

#include <iostream>
#include "Object3D.h"
//#include "CamPers.h"

#include "glm\mat4x4.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"

#include "GLFW/glfw3.h"



#include "Windows.h"
#pragma comment(lib, "winmm.lib")

using namespace glm;

class Application {
	
public:
	double mouseX, mouseY;
	Application();
	~Application();

	void setup();
	void update();
	void display();
	void reshape(int w, int h);

	void mousePos(double x, double y)
	{
		mouseX = x;
		mouseY = y;
		printf("\n\nmouse X: %i\nmouse Y: %i", (int)mouseX, (int)mouseY);
	}
	void keyboard(int key, int scancode, int action, int mods)
	{
		if (action == GLFW_RELEASE)
		{
			if (key == GLFW_KEY_ESCAPE) { std::exit(0); }
			if (switchi == false) {
				if (key == GLFW_KEY_1) { printf("1\n"); }
				else if (key == GLFW_KEY_Q) {
				}
			}
		}
	
	}
	int contadorCuadro = 0;
	void mouse(int key, int action, int mods)
	{
		if (action == GLFW_RELEASE&&switchi==true)
		{
			if (key == GLFW_MOUSE_BUTTON_LEFT) {
				printf("boton derecho\n");
				float difX = 640 / 11;
				float difY = 480 / 11;
				for (int i = 0; i<11; i++)
				{
					for (int j = 0; j<11; j++)
					{
						if (i*difX < mouseX&&(i+1)*difX>mouseX)
						{
							if (j*difY < mouseY&&(j+1)*difY>mouseY)
							{
								laberinto[i][10-j] = contadorCuadro;
								contadorCuadro++;
								if (contadorCuadro >= 4)
								{
									contadorCuadro = 0;
									// es como nos dijiste pedrito
								}
							}
						}
					}
				}
			}
			else if (key == GLFW_MOUSE_BUTTON_RIGHT) { 
				printf("boton izquierdo\n");
				float difX = 640 / 11;
				float difY = 480 / 11;
				for (int i = 0; i<11; i++)
				{
					for (int j = 0; j<11; j++)
					{
						if (i*difX < mouseX && (i + 1)*difX>mouseX)
						{
							if (j*difY < mouseY && (j + 1)*difY>mouseY)
							{
								if (laberinto[i][10 - j] == 0)
								{
									laberinto[i][10 - j] = 1;
								}
								else if (laberinto[i][10 - j] == 1)
								{
									laberinto[i][10 - j] = 0;
								}
							}
						}
					}
				}
			}

			//640, 480 ....11|11 121
			/*
			int contadorCuadro=0; //application.h
			aqui estaba lo que esta arriba
			*/
		}
	}
	void collisions() {
		for (int i = 0; i < 11; i++)
		{
			for (int j = 0; j < 11; j++)
			{
				//float dist = glm::sqrt(((eye.x - (j * 2))*(eye.x - (j * 2))) + ((eye.z - (i * 2))*(eye.z - (i * 2))));
				float savedX = eye.x, savedZ = eye.z;
				float dist = glm::sqrt(((eye.x - (i * 2))*(eye.x - (i * 2))) + ((eye.z - (j * 2))*(eye.z - (j * 2))));
				if (dist < 0.5)
				{
					if (laberinto[i][j] == 0)//pastilla
					{
						laberinto[i][j] = 3; //vacio
						PlaySound(TEXT("pcChomp.wav"), NULL, SND_FILENAME);
					}
					else if (laberinto[i][j] == 1) //muro
					{
						PlaySound(TEXT("SmashingByYuriSantana.wav"), NULL, SND_FILENAME);
						//printf("\nESTAS COLISIONANDO CONTRA UN MURO CHAVO");
						if (target.x < eye.x) //colision contra izquierda
						{/*tx-1
							tz0
							ex0
							ez0
						 */
							eye.x += 2; // tz=0
							//eye.z -= 1;
							target.x += 2;
						//	target.z -= 1;
						}
						else if (target.x>eye.x) //derecha
						{
							eye.x -= 2;
							target.x -= 2;
						}
						else if (target.z > eye.z)
						{
							target.z -= 2;
							eye.z -= 2;
						}
						else if (target.z < eye.z)
						{
							target.z += 2;
							eye.z += 2;
						}
						
						
						//if (eye.x > eye.z)
						//{
						//	eye.x -= 2;
						//	eye.z -= 2;
						//	target.x -= 2;
						//	target.z -= 2;
						//	/*eye.x = savedX-2; //regresar pos anterior
						//	eye.z = savedZ-2;
						//	target.x=*/
						//}
						//else {
						//	eye.x -= 2;
						//	eye.z -= 2;
						//	target.x -= 2;
						//	target.z -= 3;
						//}

							/*
						else {
							eye.x = savedX-2; //regresar pos anterior
							eye.z = savedZ-2;
						}
							*/
					} 
					else if (laberinto[i][j] == 2)//fantasma
					{
						if (activeGhosts >= 60)
						{
						PlaySound(TEXT("die.wav"), NULL, SND_FILENAME);
						printf("\nYou died, but you can still play");
						activeGhosts = 0;
						}
					}
				}
				//disque se supone que trata de ser una supuesta y miserable inteligencia artificial para fantasma
				/*else if (dist > 0.7&&laberinto[j][i]==2) {
					float difX = eye.x - (j * 2);
					float difY = eye.z - (i * 2);
					if (difX >= difY) {
						if (laberinto[j + 1][i] == 0)
							laberinto[j][i] = 0;
						laberinto[j + 1][i] = 2;
					}
					else {
						if (laberinto[j][i + 1] == 0)
							laberinto[j][i] = 0;
						laberinto[j][i + 1] = 2;
					}
				}
					*/
			}
		}
	}
	bool switchi = false;


	int activeGhosts = 0;
	Object3D wall;
	Object3D pellet;

	

	mat4 transformaciones;
	mat4 rotacionX;
	mat4 rotacionY;
	mat4 rotacionZ;
	mat4 traslacionX;
	mat4 traslacionY;
	mat4 traslacionZ;
	mat4 scalaX;
	mat4 scalaY;
	mat4 scalaZ;

	vec3 eye = vec3(10.0f, 0.4f, 10.0f);
	vec3 target = vec3(10.0f, 0.4f, 11.0f);
	vec3 up=vec3(0.0f,1.0f,0.0f);
	mat4 cam, look, pers;
	int counter = 0;
	char laberinto[11][11]={
	{1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,1},
	{1,0,1,0,0,0,0,0,1,0,1},
	{1,0,0,1,0,0,0,1,0,0,1},
	{1,0,0,0,1,0,1,0,0,0,1},
	{1,0,0,0,2,0,3,3,3,0,1},
	{1,0,0,0,1,0,1,0,0,0,1},
	{1,0,0,1,0,0,0,1,0,0,1},
	{1,0,1,0,0,0,0,0,1,0,1},
	{1,0,0,0,0,0,0,0,0,2,1},
	{1,1,1,1,1,1,1,1,1,1,1}
	};

};

