#include "stdafx.h"
#include "SceneMgr.h"

#define MAX_OBJECTS_COUNT 10
#define OBJECT_BUILDING 1
#define OBJECT_CHARACTER 2
#define OBJECT_BULLET 3
#define OBJECT_ARROW 4


SceneMgr::SceneMgr(int windowSizeX, int windowSizeY)
{
	// Initialize Renderer
	renderer = new Renderer(windowSizeX, windowSizeY);

	if (!renderer->IsInitialized())
	{
		std::cout << "SceneMgr::Renderer could not be initialized.. \n";
	}

	width = windowSizeX;
	height = windowSizeY;

	for (int i = 0; i < MAX_OBJECTS_COUNT; i++)
	{
		draw_Object[i] = NULL;

	}
}
SceneMgr::~SceneMgr()
{
}
void SceneMgr::setxy(int x, int y)
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		if (draw_Object[i] == NULL)
		{
			draw_Object[i] = new newObject(x,y,10,300.f,10);				
			break;
		}
	}

}

void SceneMgr::AllUpdate(float elapsedTime)
{
	DoCollisionTest();

	for (int i = 0; i < MAX_OBJECTS_COUNT; i++)
	{
		if (draw_Object[i] != NULL)
		{
			if (draw_Object[i]->GetLife() <0 || draw_Object[i]->GetLifeTime() < 0.0001f)
			{
				//kill object
				delete draw_Object[i];
				draw_Object[i] = NULL;
			}
			else
			{
				draw_Object[i]->Update(elapsedTime);
			}
		}
		
	}
}

void SceneMgr::DrawRect()
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		if (draw_Object[i] != NULL)
		{			
			renderer->DrawSolidRect(
				draw_Object[i]->xpos, draw_Object[i]->ypos,
				draw_Object[i]->zpos,
				draw_Object[i]->size,
				draw_Object[i]->r,
				draw_Object[i]->g,
				draw_Object[i]->b,
				draw_Object[i]->a);			
		}
			
	}
	
}


void SceneMgr::DoCollisionTest()
{
	int collisionCount = 0;

	for (int i = 0; i < MAX_OBJECTS_COUNT; i++)
	{
		collisionCount = 0;
		if (draw_Object[i] != NULL)
		{
			for (int j = 0; j < MAX_OBJECTS_COUNT; j++)
			{
				if (i == j)
					continue;

				if (draw_Object[j] != NULL)
				{
					float minX, minY;
					float maxX, maxY;

					float minX1, minY1;
					float maxX1, maxY1;

					minX = draw_Object[i]->xpos - draw_Object[i]->size / 2.f;
					minY = draw_Object[i]->ypos - draw_Object[i]->size / 2.f;
					maxX = draw_Object[i]->xpos + draw_Object[i]->size / 2.f;
					maxY = draw_Object[i]->ypos + draw_Object[i]->size / 2.f;
					minX1 = draw_Object[j]->xpos - draw_Object[j]->size / 2.f;
					minY1 = draw_Object[j]->ypos - draw_Object[j]->size / 2.f;
					maxX1 = draw_Object[j]->xpos + draw_Object[j]->size / 2.f;
					maxY1 = draw_Object[j]->ypos + draw_Object[j]->size / 2.f;
					if (BoxBoxCollisionTest(minX, minY, maxX, maxY, minX1, minY1, maxX1, maxY1))
					{
						collisionCount++;
					}
				}
			}
			if (collisionCount > 0)
			{
				draw_Object[i]->r = 1;
				draw_Object[i]->g = 0;
				draw_Object[i]->b = 0;
				draw_Object[i]->a = 1;
			}
			else
			{
				draw_Object[i]->r = 1;
				draw_Object[i]->g = 1;
				draw_Object[i]->b = 1;
				draw_Object[i]->a = 1;
			}
		}
	}
}

bool SceneMgr::BoxBoxCollisionTest(float minX, float minY, float maxX, float maxY, float minX1, float minY1, float maxX1, float maxY1)
{
	if (minX > maxX1)
		return false;
	if (maxX < minX1)
		return false;

	if (minY > maxY1)
		return false;
	if (maxY < minY1)
		return false;

	return true;
}
