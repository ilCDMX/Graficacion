#include <string>
#include <vector>
#include <stdio.h>
#include <iostream>

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Application.h"

Application app;
bool once=false;
bool switchi = false;
int o = 0, p = 0;
int times = 0;
float theta = 0;
vec3 savedEye = app.eye , savedTarget=app.target, savedUp=app.up;
mat4 savedLook = app.look, savedPerscla = app.pers;

 void keyboard(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	app.keyboard(key, scancode, action, mods);
}
 void mouse(GLFWwindow*window, int button, int action, int mods)
 {
	 app.mouse(button, action, mods);
 }
 void mousePos(GLFWwindow*window, double x, double y)
 {
	 app.mousePos(x, y);
 }

//Se tiene que llamar despues de inicializar la ventana y el OpenGL, pero antes del main loop
void setup()
{
	app.setup();
}

//Se ejecuta siempre que se necesite actualizar la imagen
void display()
{
	app.display();
}

//Se ejecuta cuando la ventana cambia de tamaño. Parámetros en pixeles.
//(ojo: En otros programas se debe ejecutar glViewport)
void reshape(int w, int h)
{
	app.reshape(w, h);
}


int main(int argc, char *argv[])
{

	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	glewInit();
	app.setup();

	// get version info 
	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* version = glGetString(GL_VERSION);
	printf(" Renderer: %s\ n", renderer);
	printf(" OpenGL version supported %s\ n", version);

	// tell GL to only draw onto a pixel if the shape is closer to the viewer 
	//glEnable (GL_DEPTH_TEST); // enable depth-testing 	
	//glDepthFunc (GL_LESS); // depth-testing interprets a smaller value as "closer" 

	glViewport(0, 0, (GLsizei)640, (GLsizei)480);
	glEnable(GL_DEPTH_TEST); // Habilita el z-buffer




	glfwSetKeyCallback(window,keyboard);
	glfwSetMouseButtonCallback(window, mouse);
	glfwSetCursorPosCallback(window, mousePos);


	while (!glfwWindowShouldClose(window))
	{
	//	PlaySound(TEXT("pcChomp.wav"), NULL, SND_FILENAME);
		 //SND_FILENAME or SND_LOOP
		/* update other events like input handling */
		glfwPollEvents();

		// Update de Application
		app.update();


		once = false;
		switchi = false;
		times++;
		if (times >= 60) {
			if (glfwGetKey(window, GLFW_KEY_SPACE)) {
				//p = 20.0 - p; //pos cambiada de camara; inicia en 0 no hay cambio hasta tab
				o = 1 - o; //switch de camara inicia en 0, cambio =1
				// 0 pers 1 orto
				once = true;

				if (o == 0) {
					/*
					app.eye = savedEye;
					app.target = savedTarget;
					app.up = savedUp;

					//app.pers = savedPers;
					//app.look = savedLook;

					app.look = lookAt(app.eye, app.target, app.up);
					app.pers = perspective(45.0f, 640.0f / 480.0f, -20.0f, 50.0f);*/

					//app.cam = app.look*app.pers;
					app.switchi = false; }//al inicio se le resta 0

				else if (o == 1) {
					/*savedEye = app.eye;
					savedTarget = app.target;
					savedUp = app.up;

					savedLook = app.look;
					savedPers = app.pers;

					app.look = ortho(-1.0f, 21.0f, -1.0f, 21.0f)*rotate(mat4(1.0f), (-3.14f / 2.0f), vec3(1.0f, 0.0f, 0.0f));
					app.pers = glm::rotate(mat4(1.0f), (-3.1415f / 2.0f), vec3(1.0f, 0.0f, 0.0f));*/
					//app.eye.x = 10; app.eye.z = 10; app.eye.y = 20.4; 
					//app.target.x = 10; app.target.z = 10.001; app.target.y = 0.4;

					//app.cam = app.look*app.pers;
					//app.cam = ortho(-1.0f, 21.0f, -1.0f, 21.0f)*rotate(mat4(1.0f), (-3.14f / 2.0f), vec3(1.0f, 0.0f, 0.0f));

					app.switchi = true; }
				times = 0;
			}
			else if (glfwGetKey(window, GLFW_KEY_W)) {
				float velocity = 0.01;
				while (!once) {
					app.collisions();
					app.eye.x += (app.target.x-app.eye.x)*velocity;
					app.eye.z += (app.target.z-app.eye.z)*velocity;

					app.target.x += (app.target.x-app.eye.x)*velocity;
					app.target.z += (app.target.z-app.eye.z)*velocity;

					once = true;
				}
			}
		/*	else if (glfwGetKey(window, GLFW_KEY_S)) {
				float velocity = 0.01;
				while (!once) {
					app.eye.x -= (app.target.x - app.eye.x)*velocity;
					app.eye.z -= (app.target.z - app.eye.z)*velocity;

					app.target.x -= (app.target.x - app.eye.x)*velocity;
					app.target.z -= (app.target.z - app.eye.z)*velocity;
					once = true;
				}
			}*/
			else if (glfwGetKey(window, GLFW_KEY_A)) {
				float velocity = 0.001;
				while (!once) {
					//vec3 tempTarget = app.target - app.eye;
			//		app.target.x = -(app.eye.x+((app.target.x - app.eye.x)*cos((theta + 90.0f)*3.1415f / 180.0f)));
			//		app.target.z = -(app.eye.z+((app.target.z - app.eye.z)*cos((theta + 90.0f)*3.1415f / 180.0f)));
					
					if (theta == 0||theta==360)
					{
						app.target.x -= 1;
						app.target.z -= 1;
					}
					else if (theta == 90)
					{
						app.target.x += 1;
						app.target.z -= 1;
					}
					else if (theta == 180)
					{
						app.target.x += 1;
						app.target.z += 1;
					}
					else if (theta == 270)
					{
						app.target.x -= 1;
						app.target.z += 1;
					}
					
					if (theta < 270)
						theta += 90.0f;
					else
						theta = 0;
					/*tempTarget.x = cos(3.1416/2);
					tempTarget.z = sin(3.1416/2);
					app.target.x = app.eye.x + tempTarget.x;
					app.target.z = app.eye.z + tempTarget.z;*/
					//app.target.x *= cos((90.0f*3.1415f / 180.0f));
					//app.target.z *= sin((90.0f*3.1415f / 180.0f));

					once = true;
					times = 0;
				}
			}
			
			else if (glfwGetKey(window, GLFW_KEY_D)) {
				float velocity = 0.001;
				while (!once) {
				//	app.target.x = app.eye.x+((app.target.x - app.eye.x)*cos((theta-90.0f)*3.1415f / 180.0f));
				//	app.target.z = app.eye.z-((app.target.z - app.eye.z)*cos((theta - 90.0f)*3.1415f / 180.0f));
					if (theta == 0)
					{
						app.target.x += 1;
						app.target.z -= 1;
					}
					else if (theta == 90)
					{
						app.target.x += 1;
						app.target.z += 1;
					}
					else if (theta == 180)
					{
						app.target.x -= 1;
						app.target.z += 1;
					}
					else if (theta == 270)
					{
						app.target.x -= 1;
						app.target.z -= 1;
					}

					theta -= 90.0f;
					if (theta < 0)
						theta += 360.0f;
					//	glm::mat4 rotD = glm::rotate(mat4(1.0f), (-90.0f * 3.141592f / 180.0f), vec3(1.0f, 0.0f, 1.0f));
					//	app.eye *= rotD;
					//	app.target *= rotD;
					/*app.eye.x = -app.eye.x;
					app.eye.z = -app.eye.z;

					app.target.x = -app.target.x;
					app.target.z = -app.target.x;*/

					/*vec3 tempTarget = app.target - app.eye;
					tempTarget.x = cos((-90.0f*3.1415f / 180.0f));
					tempTarget.z = sin((-90.0f*3.1415f / 180.0f));
					app.target.x = app.eye.x + tempTarget.x;
					app.target.z = app.eye.z + tempTarget.z;*/
					//app.target.x *= cos((270.0f*3.1415f / 180.0f));
					//app.target.z *= sin((270.0f*3.1415f / 180.0f));
					once = true;
					times = 0;
				}
			}
			
			/* put the stuff we've been drawing onto the display */
		}
		app.display();

		glfwSwapBuffers(window);
	}

	/* close GL context and any other GLFW resources */
	glfwTerminate();
	return 0;

}
