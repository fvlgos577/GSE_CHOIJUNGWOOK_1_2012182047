#pragma once
#include "Renderer.h"

class newObject
{
private:
	
	int state;		// 상태

	float speed;		// 이동속도
	float weight;		// 무게
	
	Renderer *renderer;
	

public:
	newObject(float x, float y, float lf, float sp, int si, int ty, int i ,int ti);
	~newObject();
	// 렌더러 포인터
	
	float delay = 0;
	float GetLife();
	float GetLifeTime();
	float SetLife();

	float xpos;
	float ypos;
	
	float vxpos;
	float vypos;
	float zpos;

	float r;
	float g;
	float b;
	float a;

	int type;
	float life;
	float lifetime;
	
	float damage;
	int team;
	int id;

	float size;		// 사이즈 

	int		GetState() { return state; }
	float	GetSize() { return size; }
	float	GetSpeed() { return speed; }
	float   GetWeight() { return weight; }
	void	setColor(int type);

	void	CheckTime(float elapsedTime);
	float	GetTime();
	void	resetTime();
	void	Update(float elapsedTime);
};

