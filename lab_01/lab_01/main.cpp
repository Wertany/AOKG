#include <Windows.h>
#include <WinUser.h>
#include <stdio.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <GL/freeglut.h>

extern float arr_color[5][3] = {
		{ 0.0, 0.0, 0.0 },
		{ 1.0, 1.0, 0.0 },
		{ 0.0, 0.0, 1.0 },
		{ 1.0, 0.0, 0.0 }
};

int buffer = 0;
const int time = 20;
int buffer_time = 0;

void Reshape(int w, int h);
void Display(void);
void BufferHelp();
void Simulation(int value);
void KeyboardFunc(unsigned char key, int x, int y);

int main(int argc, char** argv)
{
	// устанавливаем камеру
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(15, 15, 7.5, 0, 0, 0, 0, 1, 0);

	// инициализация библиотеки GLUT
	glutInit(&argc, argv);
	// инициализация дисплея (формат вывода)
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

	// создание окна:
	// 1. устанавливаем верхний левый угол окна
	glutInitWindowPosition(200, 25);
	// 2. устанавливаем размер окна
	glutInitWindowSize(800, 500);
	// 3. создаем окно
	glutCreateWindow("lab_1");

	// устанавливаем функцию, которая будет вызываться для перерисовки окна
	glutDisplayFunc(Display);
	// устанавливаем функцию, которая будет вызываться при изменении размеров окна
	glutReshapeFunc(Reshape);
	// устанавливаем функцию которая будет вызвана через 20 мс
	glutTimerFunc(20, Simulation, 0);
	// устанавливаем функцию, которая будет вызываться при нажатии на клавишу
	glutKeyboardFunc(KeyboardFunc);

	// основной цикл обработки сообщений ОС
	glutMainLoop();
}


// функция, вызываемая при изменении размеров окна
void Reshape(int w, int h)
{
	// установить новую область просмотра, равную всей области окна
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	// установить матрицу проекции с правильным аспектом
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(25.0, (float)w / h, 0.2, 70.0);
};

// функция вызывается при перерисовке окна
// в том числе и принудительно, по командам glutPostRedisplay
void Display(void)
{
	// отчищаем буфер цвета
	glClearColor(0.22, 0.88, 0.11, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// включаем тест глубины
	glEnable(GL_DEPTH_TEST);
	// устанавливаем камеру
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(5, 5, 7.5, 0, 0, 0, 0, 1, 0);
	// выводим объект ‐ красный (1,0,0) чайник
	glColor3f(arr_color[buffer][0], arr_color[buffer][1], arr_color[buffer][2]);
	glutWireTeapot(1.0);
	// смена переднего и заднего буферов
	glutSwapBuffers();
};

void BufferHelp()
{
	if (buffer > 4)
		buffer = 0;

	buffer++;
}

// функция вызывается каждые n мс
void Simulation(int value)
{
	// устанавливаем признак того, что окно нуждается в перерисовке
	glutPostRedisplay();
	// эта же функция будет вызвана еще раз через 20 мс
	glutTimerFunc(time, Simulation, 0);

	buffer_time++;

	if (buffer_time >= 50)
	{
		BufferHelp();
		buffer_time = 0;
	}
};

// Функция обработки нажатия клавиш
void KeyboardFunc(unsigned char key, int x, int y)
{
	printf("Key code is %i\n", (unsigned int)key);

	BufferHelp();
};

