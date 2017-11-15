#include "stdafx.h"
#include "SceneMgr.h"

#define MAX_OBJECTS_CHARATER_COUNT 10
#define MAX_OBJECTS_BUILDING_COUNT 10
#define MAX_OBJECTS_BULLET_COUNT 10
#define MAX_OBJECTS_ARROW_COUNT 10
#define MAX_OBJECTS 200
#define OBJECT_CHARACTER 1
#define OBJECT_BUILDING 2
#define OBJECT_BULLET 3
#define OBJECT_ARROW 4

float time = 0;
GLuint textureID = 0;
SceneMgr::SceneMgr(int windowSizeX, int windowSizeY)
{
	// Initialize Renderer
	renderer = new Renderer(windowSizeX, windowSizeY);
	textureID = renderer->CreatePngTexture("./Textures/newbilding.png");
	if (!renderer->IsInitialized())
	{
		std::cout << "SceneMgr::Renderer could not be initialized.. \n";
	}

	width = windowSizeX;
	height = windowSizeY;

	for (int i = 0; i < MAX_OBJECTS; i++)
	{
		draw_Object[i] = NULL;
		
	}	
	AddActorObject(0, 0, OBJECT_BUILDING,0);
}
SceneMgr::~SceneMgr()
{
}
void SceneMgr::setxy(int x, int y)
{
	AddActorObject(x, y, OBJECT_CHARACTER,0);
}

void SceneMgr::AllUpdate(float elapsedTime)
{
	
	DoCollisionTest();
	
	for (int i = 0; i < MAX_OBJECTS; i++)
	{
		if (draw_Object[i] != NULL)
		{
			draw_Object[i]->SetLife();
			draw_Object[i]->CheckTime(elapsedTime);
			if (draw_Object[i]->type <=2 && draw_Object[i]->delay >= 500)
			{
				
				AddActorObject(draw_Object[i]->xpos, draw_Object[i]->ypos, OBJECT_ARROW, i);				
				draw_Object[i]->resetTime();
			}
			if (draw_Object[i]->GetLife() <0.0001f || draw_Object[i]->GetLifeTime() < 0.0001f)
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

void SceneMgr::AddActorObject(int x, int y, int type, int id)
{
	
	if (type == OBJECT_CHARACTER)
	{
		for (int i = 0; i < 10; ++i)
		{
			if (draw_Object[i] == NULL)
			{
				draw_Object[i] = new newObject(x, y, 10.f, 300.f, 10, OBJECT_CHARACTER,i);
				draw_Object[i]->setColor(OBJECT_CHARACTER);
				break;
			}
		}
	}		
	if (type == OBJECT_BUILDING)
	{
		for (int i = 10; i < 20; ++i)
		{
			if (draw_Object[i] == NULL)
			{
				draw_Object[i] = new newObject(x, y, 500.f, 0, 50, OBJECT_BUILDING, i);
				draw_Object[i]->setColor(OBJECT_BUILDING);
				break;
			}
		}
	}
	if (type == OBJECT_ARROW)
	{
		for (int i = 30; i < MAX_OBJECTS; ++i)
		{
			if (draw_Object[i] == NULL)
			{
				draw_Object[i] = new newObject(x, y, 10, 100.f, 2, OBJECT_ARROW,id);
				draw_Object[i]->setColor(OBJECT_ARROW);
				break;
			}
		}
	}

}

void SceneMgr::DrawRect()
{
	for (int i = 0; i < MAX_OBJECTS; ++i)
	{
		
		if (draw_Object[i] != NULL)
		{			
			if (draw_Object[i]->type == OBJECT_BUILDING)
			{
				renderer->DrawTexturedRect(
					draw_Object[i]->xpos,
					draw_Object[i]->ypos,
					draw_Object[i]->zpos,
					draw_Object[i]->size,
					draw_Object[i]->r,
					draw_Object[i]->g,
					draw_Object[i]->b,
					draw_Object[i]->a,
					textureID);
			}
			else
			{
				renderer->DrawSolidRect(
					draw_Object[i]->xpos,
					draw_Object[i]->ypos,
					draw_Object[i]->zpos,
					draw_Object[i]->size,
					draw_Object[i]->r,
					draw_Object[i]->g,
					draw_Object[i]->b,
					draw_Object[i]->a);
			}
			
		}
			
	}
	
}

void SceneMgr::DoCollisionTest()
{
	int collisionCount = 0;

	for (int i = 0; i < MAX_OBJECTS; i++)
	{		
		collisionCount = 0;
		if (draw_Object[i] != NULL)
		{
			for (int j = 0; j < MAX_OBJECTS; j++)
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
						if (draw_Object[i]->id == draw_Object[j]->id)
							continue;
						collisionCount++;
						if (draw_Object[i]->id < 10 && draw_Object[j]->id < 10)
							continue;
						
						draw_Object[i]->damage = draw_Object[j]->life;										
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
				draw_Object[i]->setColor(draw_Object[i]->type);
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
