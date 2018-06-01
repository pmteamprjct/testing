#include "Shape.h"

Shape::Shape(float x, float y, int w, int h, float r, float g, float b)
{
	Pos[0] = x;
	Pos[1] = y;
	width = w;
	height = h;
	color[0] = r;
	color[1] = g;
	color[2] = b;
}


void Shape::setPos(float x, float y)
{
	Pos[0] = x;
	Pos[1] = y;
}

void Shape::setSize(int w, int h)
{
	width = w;
	height = h;
}

void Shape::setColor(float r, float g, float b)
{
	color[0] = r;
	color[1] = g;
	color[2] = b;
}

void Shape::draw()
{

}


Curser::Curser(float x, float y, int w, int h, float r, float g, float b) : Shape(x, y, w, h, r, g, b)
{
	
}


void Curser::draw()
{
	glColor3f(color[0], color[1], color[2]);
	glBegin(GL_TRIANGLES);
	glVertex3f(Pos[0] + width / 2.0, Pos[1], 0);
	glVertex3f(Pos[0] - width / 2.0, Pos[1] + height / 2.0, 0);
	glVertex3f(Pos[0] - width / 2.0, Pos[1] - height / 2.0, 0);
	glVertex3f(Pos[0] + width / 2.0, Pos[1], 0);
	glEnd();
}

void Heart::draw()
{
	glColor3f(color[0], color[1], color[2]);
	glBegin(GL_POLYGON);
	glVertex3f(Pos[0] + width / 2.0, Pos[1] + height / 2.0, 0);
	glVertex3f(Pos[0] - width / 2.0, Pos[1] + height / 2.0, 0);
	glVertex3f(Pos[0] - width / 2.0, Pos[1] - height / 2.0, 0);
	glVertex3f(Pos[0] + width / 2.0, Pos[1] - height / 2.0, 0);
	glVertex3f(Pos[0] + width / 2.0, Pos[1] + height / 2.0, 0);
	glEnd();
}


Heart::Heart(float x, float y, int w, int h) : Shape(x, y, w, h, 1.0, 0, 0)
{

}
