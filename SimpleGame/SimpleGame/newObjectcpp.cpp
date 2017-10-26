#include "stdafx.h"
#include "newObject.h"
#include "Renderer.h"

newObject::newObject()
{

}

newObject::~newObject()
{
}

void newObject::SetPos(float x, float y, float z)
{
	this->xpos = x;
	this->ypos = y;
	this->zpos = z;
}

void newObject::SetSize(float size)
{
	this->size = size;
}

void newObject::SetColor(float r, float g, float b, float a)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

void newObject::SetState(int state)
{
	this->state = state;
}

void newObject::SetRender(Renderer* pRenderer)
{
	renderer = pRenderer;
}

void newObject::SetSpeed(float inputSpeed)
{
	speed = inputSpeed;
}

void newObject::AddSpeed(float addSpeed)
{
	speed += addSpeed;
}

void newObject::DrawnewObject()
{
	renderer->DrawSolidRect(xpos,ypos,zpos, size, r, g, b, a);
}

 
void newObject::Update(float time)
{
}
