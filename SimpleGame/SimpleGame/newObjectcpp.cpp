#include "stdafx.h"
#include "newObject.h"
#include "Renderer.h"

newObject::newObject(float x, float y, float lf, float sp,int si, int ty,int i)
{
	xpos = x;
	ypos = y;
	zpos = 0;
	vxpos = sp *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
	vypos = sp *(((float)std::rand() / (float)RAND_MAX) - 0.5f);

	size = si;
	r = 1;
	g = 1;
	b = 1;
	a = 1;

	type = ty;
	id = i;
	life = lf;
	lifetime = 10000000.f;
}

newObject::~newObject()
{
}

void newObject::Update(float elapsedTime)
{
	float elapsedTimeInSecond = elapsedTime / 1000.f;

	xpos = xpos + vxpos * elapsedTimeInSecond;
	ypos = ypos + vypos * elapsedTimeInSecond;	
	if (xpos > 250)
	{
		vxpos = -vxpos;
	}

	if (xpos < -250)
	{
		vxpos = -vxpos;
	}

	if (ypos > 250)
	{
		vypos = -vypos;
	}

	if (ypos < -250)
	{
		vypos = -vypos;
	}	
}


float newObject::GetLife()
{
	return life;
}

float newObject::GetLifeTime()
{
	return lifetime;
}
float newObject::SetLife()
{
	life = life - damage;
	damage = 0;
	return life;
}

void newObject::setColor(int type)
{
	if (type == 1)
	{
		r = 1;
		g = 1;
		b = 1;
	}
	else if (type == 2)
	{
		r = 0;
		g = 0.5;
		b = 1;
	}
	else if (type == 4)
	{
		if (id < 10)
		{
			r = 1;
			g = 0;
			b = 1;
		}
		else
		{
			r = 0.2;
			g = 0;
			b = 1;
		}
	}
	else
	{
		r = 0;
		g = 0;
		b = 0;
	}
}

void newObject::CheckTime(float elapsedTime)
{
	delay += elapsedTime;	
}
void newObject::resetTime()
{
	delay = 0;
}