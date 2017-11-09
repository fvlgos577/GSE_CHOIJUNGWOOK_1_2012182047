#pragma once

#include "newObject.h"
#include <stdio.h>
#define MAX_OBJECTS_COUNT 100

class SceneMgr
{
private:
	
	bool BoxBoxCollisionTest(float minX, float minY, float maxX, float maxY, float minX1, float minY1, float maxX1, float maxY1);
	void DoCollisionTest();
	
	Renderer *renderer;

	int width;
	int height;
	
public:
	newObject *draw_Object[MAX_OBJECTS_COUNT];
	SceneMgr(int windowSizeX, int windowSizeY);
	~SceneMgr();
	int num=0;
	void setxy(int x, int y);
	void AllUpdate(float elapsedTime);
	void DrawRect();
	
	
};

