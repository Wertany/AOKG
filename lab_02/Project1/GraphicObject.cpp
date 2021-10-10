#include "GraphicObject.h"

// Конструктор
GraphicObject::GraphicObject()
{
	position = glm::vec3(0);
	angle = 0;
	color = glm::vec3(0);
	modelMatrix = glm::mat4(0);
}
// задать позицию объекта
void GraphicObject::setPosition(const glm::vec3& pos)
{
	position = pos;
	recalculateModelMat();
}

glm::vec3& GraphicObject::getPosition()
{
	return position;
}
// задать угол поворота в градусах относительно оси OY
void GraphicObject::setAngle(GLfloat arg)
{
	angle = arg;
	recalculateModelMat();
}

GLfloat& GraphicObject::getAngle()
{
	return angle;
}
// Задать цвет модели
void GraphicObject::setСolor(const glm::vec3& color)
{
	this->color = color;
}

glm::vec3& GraphicObject::getColor()
{
	return color;
}
// вывести объект
void GraphicObject::draw(void)
{
	glPushMatrix();
	glColor3fv(glm::value_ptr(color));
	glMultMatrixf(glm::value_ptr(modelMatrix));
	glutWireTeapot(1.);
	glPopMatrix();
}


void GraphicObject::recalculateModelMat()
{
	modelMatrix = translate(position) * glm::rotate(glm::radians(angle), glm::vec3(0, 1, 0));
}