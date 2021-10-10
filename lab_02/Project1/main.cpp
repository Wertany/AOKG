#include <Windows.h>
#include <WinUser.h>
#include <stdio.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <GL/freeglut.h>
#include "VSL/GLM/GLM/glm.hpp"
#include "VSL/GLM/GLM/gtx/transform.hpp"
#include "VSL/GLM/GLM/gtc/type_ptr.hpp"
#include "GraphicObject.h"

void display();
void reshape(int w, int h);
void simulation();
float getSimulatTime();

const int graphic_objects_count = 4;
GraphicObject graphic_objects[graphic_objects_count];

LARGE_INTEGER freq;
LARGE_INTEGER oldSimTick;
LARGE_INTEGER newSimTick;
LARGE_INTEGER oldDrawTick;
LARGE_INTEGER newDrawTick;

int main(int argc, char** argv)
{
	// устанавливаем камеру
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(15, 15, 7.5, 0, 0, 0, 0, 1, 0);

	// инициализация библиотеки GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
	glutInitWindowPosition(200, 300);
	glutInitWindowSize(800, 500);
	glutCreateWindow("lab_2");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(simulation);

	graphic_objects[0].setPosition(glm::vec3(-2, 0, 0));

	graphic_objects[1].setPosition(glm::vec3(2, 0, 0));
	graphic_objects[1].setAngle(180);
	graphic_objects[1].setСolor(glm::vec3(1, 0, 0));

	graphic_objects[2].setPosition(glm::vec3(0, 0, -2));
	graphic_objects[2].setAngle(-90);
	graphic_objects[2].setСolor(glm::vec3(1, 1, 0));

	graphic_objects[3].setPosition(glm::vec3(0, 0, 2));
	graphic_objects[3].setAngle(90);
	graphic_objects[3].setСolor(glm::vec3(0.4, 0, 0.7));
	
	QueryPerformanceCounter(&newSimTick);
	QueryPerformanceFrequency(&freq);
	newSimTick = newDrawTick;
	glutMainLoop();
}

void display()
{
	glClearColor(0.22, 0.88, 0.11, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(1., 10., 5., 0, 0, 0, 0, 1, 0);
	
	for (int i = 0; i < graphic_objects_count; i++)
		graphic_objects[i].draw();

	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(25.0, (float)w / h, .2, 70.);
};

double getSimulationTime()
{
	oldSimTick = newSimTick;
	QueryPerformanceCounter(&newSimTick);
	return (double(newSimTick.QuadPart - oldSimTick.QuadPart)) / freq.QuadPart;
}

void simulation()
{
	double deltaTime = getSimulationTime();

	glutPostRedisplay();
};


//// Функция обработки нажатия клавиш
//void KeyboardFunc(unsigned char key, int x, int y)
//{
//	printf("Key code is %i\n", (unsigned int)key);
//
//	BufferHelp();
//};

