#pragma once

#include "newObject.h"
#include <stdio.h>
#define MAX_OBJECTS_COUNT 100

class SceneMgr
{
public:
	newObject draw_Object[MAX_OBJECTS_COUNT];
	SceneMgr();
	~SceneMgr();
	int num = 0;
	void setxy(int x, int y, int i);
	void AllUpdate();
	void DrawRect();
private:
	
};

