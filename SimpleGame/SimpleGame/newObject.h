#pragma once
#include "Renderer.h"

class newObject
{
private:
	float xpos;
	float ypos;
	float zpos;

	float r;
	float g;
	float b;
	float a;

	float life;
	float lifetime;

	float size;		// 사이즈 
	int state;		// 상태

	float speed;		// 이동속도
	float weight;		// 무게

	Renderer* renderer;	// 렌더러 포인터

public:
	newObject();
	//newObject(float xpos, float ypos, float zpos, float size) : xpos(xpos), ypos(ypos), zpos(zpos), size(size) {}
	
	~newObject();

	void SetPos(float x, float y, float z);
	
	void SetSize(float size);
	void SetColor(float r, float g, float b, float a);
	void SetState(int state);
	void SetRender(Renderer* pRenderer);
	void SetSpeed(float inputSpeed);
	void AddSpeed(float addSpeed);

	int		GetState() { return state; }
	float	GetSize() { return size; }
	float	GetSpeed() { return speed; }
	float   GetWeight() { return weight; }
	
	void	DrawnewObject();
	void	Update(float time);
};

