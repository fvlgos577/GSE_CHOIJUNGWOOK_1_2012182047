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
	newObject(float x, float y, float lf, float sp, int si, int ty, int i ,int ti);
	~newObject();
	// ������ ������
	
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

	float size;		// ������ 

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

