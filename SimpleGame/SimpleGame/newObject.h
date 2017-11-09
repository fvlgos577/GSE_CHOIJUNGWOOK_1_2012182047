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
	newObject(float x, float y, int lf, float sp, int si);
	~newObject();
	// 렌더러 포인터
	void SetState(int state);
	void SetRender(Renderer* pRenderer);
	void SetSpeed(float inputSpeed);
	void AddSpeed(float addSpeed);

	float GetLife();
	float GetLifeTime();

	float xpos;
	float ypos;
	
	float vxpos;
	float vypos;
	float zpos;

	float r;
	float g;
	float b;
	float a;

	float life;
	float lifetime;

	float size;		// 사이즈 

	int		GetState() { return state; }
	float	GetSize() { return size; }
	float	GetSpeed() { return speed; }
	float   GetWeight() { return weight; }


	void	DrawnewObject();
	void	Update(float elapsedTime);
};

