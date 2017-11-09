#include "stdafx.h"
#include "newObject.h"
#include "Renderer.h"

newObject::newObject(float x, float y, int lf, float sp,int si)
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

	life = lf;
	lifetime = 10000000.f;
}

newObject::~newObject()
{
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

	if (life > 0.f)
	{
		
	}

	if (lifetime > 0.f)
	{
		//		m_lifeTime -= elapsedTimeInSecond;
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
