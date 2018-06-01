#pragma once

#include"GL/glut.h"

class Shape
{
protected:
	float Pos[2];
	int width;
	int height;
	float color[3];
public:
	void setPos(float x, float y);
	void setSize(int w, int h);
	void setColor(float r, float g, float b);
	Shape(float x, float y, int w, int h, float r, float g, float b);
	virtual void draw();

};


class Curser : public Shape
{
public:
	void draw();
	Curser(float x, float y, int w, int h, float r, float g, float b);

};

class Heart : public Shape
{
public:
	void draw();
	Heart(float x, float y, int w, int h);
};