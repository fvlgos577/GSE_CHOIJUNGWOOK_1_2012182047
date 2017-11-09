#pragma once
#include "Renderer.h"

class newObject
{
private:
	
	int state;		// ����

	float speed;		// �̵��ӵ�
	float weight;		// ����
	Renderer *renderer;
	

public:
	newObject(float x, float y, int lf, float sp, int si);
	~newObject();
	// ������ ������
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

	float size;		// ������ 

	int		GetState() { return state; }
	float	GetSize() { return size; }
	float	GetSpeed() { return speed; }
	float   GetWeight() { return weight; }


	void	DrawnewObject();
	void	Update(float elapsedTime);
};

