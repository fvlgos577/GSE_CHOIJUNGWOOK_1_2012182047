#pragma once

#include "newObject.h"
#include <stdio.h>
#define MAX_OBJECTS_COUNT 100

class SceneMgr
{
private:
	int num;
public:
	newObject *draw_Object[MAX_OBJECTS_COUNT];
	SceneMgr(int windowSizeX, int windowSizeY);
	~SceneMgr();
	
	void setxy(int x, int y, int i);
	void AllUpdate();
	void DrawRect();
	void setNum(int num);
	int getNum();

	
};

