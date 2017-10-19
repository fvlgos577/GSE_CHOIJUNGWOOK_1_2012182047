#include "stdafx.h"
#include "SceneMgr.h"

#define MAX_OBJECTS_COUNT 100



void SceneMgr::setxy(int x, int y,int i) {
	draw_Object[i].xpos = x;
	draw_Object[i].ypos = y;
}

void SceneMgr::AllUpdate()
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		draw_Object[i].update();
	}
}

void SceneMgr::DrawRect()
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		draw_Object[i].DrawSolidRect2();
	}
}