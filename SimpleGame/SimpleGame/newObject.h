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

	float size;		// ������ 
	int state;		// ����

	float speed;		// �̵��ӵ�
	float weight;		// ����

	Renderer* renderer;	// ������ ������

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

