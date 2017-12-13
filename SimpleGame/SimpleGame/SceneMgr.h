#pragma once

#include "newObject.h"
#include "Sound.h"
#include <stdio.h>
#define MAX_OBJECTS_COUNT 500

class SceneMgr
{
private:
	
	bool BoxBoxCollisionTest(float minX, float minY, float maxX, float maxY, float minX1, float minY1, float maxX1, float maxY1);
	void DoCollisionTest();
	
	Renderer *renderer;
	Sound *sound;
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
	void AddActorObject(int x, int y, int type, int id);

	void makeArrow(int x, int y, int id);

	
	
};

