#ifndef GRAPHICOBJECT_H
#define GRAPHICOBJECT_H

#include <windows.h>
#include "GL/freeglut.h"
#include "VSL/GLM/GLM/glm.hpp"
#include "VSL/GLM/GLM/gtx/transform.hpp"
#include "VSL/GLM/GLM/gtc/type_ptr.hpp"

class GraphicObject
{
	// Позиция и угол поворота для объекта
	glm::vec3 position;
	GLfloat angle;
	// Матрица модели (расположение объекта) ‐ чтоб не вычислять каждый раз
	glm::mat4 modelMatrix;
	// Цвет модели
	glm::vec3 color;
	void recalculateModelMat();
public:
	// Конструктор
	GraphicObject();
	// Задать позицию объекта
	void setPosition(const glm::vec3&);
	glm::vec3& getPosition();
	// Задать угол поворота в градусах относительно оси OY
	void setAngle(GLfloat);
	GLfloat& getAngle();
	// Задать цвет модели
	void setСolor(const glm::vec3&);
	glm::vec3& getColor();
	// Вывести объект
	void draw(void);
};
#endif