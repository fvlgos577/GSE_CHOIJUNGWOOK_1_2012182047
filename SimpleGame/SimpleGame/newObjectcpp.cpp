#include "stdafx.h"
#include "newObject.h"
#include "Renderer.h"

newObject::newObject(float x, float y, float lf, float sp,int si, int ty,int i , int ti)
{
	xpos = x;
	ypos = y;
	zpos = 0;
	speed = sp;
	vxpos = ((float)std::rand() / (float)RAND_MAX - 0.5f);
	vypos = (float)sqrt(1 - (vxpos * vxpos));
	
	size = si;
	r = 1;
	g = 1;
	b = 1;
	a = 1;
	id = i;
	type = ty;
	team = ti;

	if (team == 1)
		vypos *= -1;
	life = lf;
	lifetime = 10000000.f;
}

newObject::~newObject()
{
}

void newObject::Update(float elapsedTime)
{
	float elapsedTimeInSecond = elapsedTime / 1000.f;

	xpos = xpos + vxpos * elapsedTimeInSecond * speed;
	ypos = ypos + vypos * elapsedTimeInSecond * speed;	
	if (type == 1)
	{
		if (xpos >= 250)
		{
			vxpos = -vxpos;
		}

		if (xpos <= -250)
		{
			vxpos = -vxpos;
		}

		if (ypos >= 400)
		{
			vypos = -vypos;
		}

		if (ypos <= -400)
		{
			vypos = -vypos;
		}
	}
	else
	{
		if (xpos > 250)
		{
			life = 0;
		}

		if (xpos < -250)
		{
			life = 0;
		}

		if (ypos > 400)
		{
			life = 0;
		}

		if (ypos < -400)
		{
			life = 0;
		}
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

void newObject::setColor(int ty)
{
	switch (ty)
	{
	case 1:
		if (team == 1)
		{
			r = 1.0f;
			g = 0.0f;
			b = 0.0f;
		}
		else
		{
			r = 0.0f;
			g = 0.0f;
			b = 1.0f;
		}
		
		break;
	case 2:
		r = 1.0f;
		g = 1.0f;
		b = 1.0f;
		break;
	case 3:
		if (team == 1)
		{
			r = 1.0f;
			g = 0.0f;
			b = 0.0f;
		}
		else
		{
			r = 0.0f;
			g = 0.0f;
			b = 1.0f;
		}
		break;
	case 4:
		if (team == 1)
		{
			r = 0.5f;
			g = 0.2f;
			b = 0.7f;
		}
		else
		{
			r = 1.0f;
			g = 1.0f;
			b = 0.0f;
		}
		break;
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