#include "stdafx.h"
#include "SceneMgr.h"


GLuint team1BuildingTexture = 0;
GLuint team2BuildingTexture = 0;
GLuint team1CharaterTexture = 0;
GLuint team2CharaterTexture = 0;
GLuint background = 0;
GLuint bullet = 0;
GLuint weather = 0;
float collDownTime = 0;
float collDownTime2 = 0;
float ranXpos = 0;
float ranYpos = 0;

int team1_character = 0;
int team2_character = 0;

int soundBullet = 0;
int soundArrow = 0;
int soundBG = 0;

SceneMgr::SceneMgr(int windowSizeX, int windowSizeY)
{
	// Initialize Renderer
	renderer = new Renderer(windowSizeX, windowSizeY);
	sound = new Sound();
	team1BuildingTexture = renderer->CreatePngTexture("./Textures/team1_building.png");
	team2BuildingTexture = renderer->CreatePngTexture("./Textures/team2_building.png");
	team1CharaterTexture = renderer->CreatePngTexture("./Textures/character1.png");
	team2CharaterTexture = renderer->CreatePngTexture("./Textures/character2.png");
	background = renderer->CreatePngTexture("./Textures/background.png");
	bullet = renderer->CreatePngTexture("./Textures/bullet.png");
	weather = renderer->CreatePngTexture("./Textures/fire_rain.png");
	soundBG = sound->CreateSound("./Dependencies/SoundSamples/MF-W-90.XM");
	soundBullet = sound->CreateSound("./Dependencies/SoundSamples/FX061.mp3");
	soundArrow = sound->CreateSound("./Dependencies/SoundSamples/FX063.mp3");
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
	AddActorObject(0,0, OBJECT_WEATHER, 0);
	for (int i = 0; i < 3; ++i)
	{
		AddActorObject((i*200) -200, -300, OBJECT_BUILDING, 0);
		AddActorObject((i * 200) - 200, +300, OBJECT_BUILDING, 0);
	}	
	
	sound->PlaySound(soundBG, true, 0.2f);
}
SceneMgr::~SceneMgr()
{
	delete renderer;
	delete[] draw_Object;
	delete sound;
}
void SceneMgr::setxy(int x, int y)
{
	
	if (collDownTime >= 1000 && y <0)
	{
		AddActorObject(x, y, OBJECT_CHARACTER, 0);
		collDownTime = 0;
	}
	
}

void SceneMgr::AllUpdate(float elapsedTime)
{
	collDownTime += elapsedTime;
	DoCollisionTest();
	collDownTime2 += elapsedTime;
	
	if (team1_character == 8)
		team1_character = 0;
	team1_character++;
	if (team2_character == 7)
		team2_character = 0;
	team2_character++;
	//srand(100);
	ranXpos = (rand() % 751) - 250;
	ranYpos = (rand() % 401);
	if (collDownTime2 >= 3000)
	{
		AddActorObject(ranXpos, ranYpos, OBJECT_CHARACTER, 0);
		collDownTime2 = 0;
	}
	
	for (int i = 0; i < MAX_OBJECTS; i++)
	{
		if (draw_Object[i] != NULL)
		{
			draw_Object[i]->SetLife();
			if(draw_Object[i]->type== OBJECT_BULLET || draw_Object[i]->type == OBJECT_WEATHER)
				draw_Object[i]->CheckTime(0.001);
			else
				draw_Object[i]->CheckTime(elapsedTime);
			if (draw_Object[i]->type == OBJECT_BUILDING && draw_Object[i]->GetTime() >= 5000)
			{
				
				AddActorObject(draw_Object[i]->xpos, draw_Object[i]->ypos, OBJECT_BULLET, i);				
				draw_Object[i]->resetTime();
				sound->PlaySound(soundBullet, false, 0.4f);
				

			}
			if (draw_Object[i]->type == OBJECT_CHARACTER && draw_Object[i]->GetTime() >= 500)
			{

				AddActorObject(draw_Object[i]->xpos, draw_Object[i]->ypos, OBJECT_ARROW, i);
				draw_Object[i]->resetTime();
				sound->PlaySound(soundArrow, false, 0.4f);
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
		for (int i = 0; i < 100; ++i)
		{
			if (draw_Object[i] == NULL)
			{
				if (y > 0)
				{
					draw_Object[i] = new newObject(x, y, 50.f, 100.f, 30, OBJECT_CHARACTER, i, TEAM_1);				
					draw_Object[i]->setColor(OBJECT_CHARACTER);
					break;
				}
				else
				{
					draw_Object[i] = new newObject(x, y, 50.f, 100.f, 30, OBJECT_CHARACTER, i, TEAM_2);					
					draw_Object[i]->setColor(OBJECT_CHARACTER);
					break;
				}
			}
		}
	}		
	if (type == OBJECT_BUILDING)
	{
		for (int i = 100; i < 120; ++i)
		{
			if (draw_Object[i] == NULL)
			{
				if (y > 0)
				{
					draw_Object[i] = new newObject(x, y, 500.f, 0, 100, OBJECT_BUILDING, i, TEAM_1);					
					draw_Object[i]->setColor(OBJECT_BUILDING);
					break;
				}
				else
				{
					draw_Object[i] = new newObject(x, y, 500.f, 0, 100, OBJECT_BUILDING, i, TEAM_2);				
					draw_Object[i]->setColor(OBJECT_BUILDING);
					break;
				}
				
			}
		}
	}
	if (type == OBJECT_BULLET)
	{
		for (int i = 120; i < 250; ++i)
		{
			if (draw_Object[i] == NULL)
			{
				draw_Object[i] = new newObject(x, y, 15, 80.f, 10, OBJECT_BULLET, id, draw_Object[id]->team);			
				draw_Object[i]->setColor(OBJECT_BULLET);
				break;
			}
		}
	}
	if (type == OBJECT_ARROW)
	{
		for (int i = 300; i < MAX_OBJECTS; ++i)
		{
			if (draw_Object[i] == NULL)
			{
				draw_Object[i] = new newObject(x, y, 10, 70.f, 4, OBJECT_ARROW,id, draw_Object[id]->team);				
				draw_Object[i]->setColor(OBJECT_ARROW);
				break;
			}
		}
	}
	if (type == OBJECT_WEATHER)
	{
		for (int i = 250; i < 300; ++i)
		{
			if (draw_Object[i] == NULL)
			{
				draw_Object[i] = new newObject(x, y, 10, 1.0f, 3, OBJECT_WEATHER, id,0);
				draw_Object[i]->setColor(OBJECT_WEATHER);
				break;
			}
		}
	}

}

void SceneMgr::DrawRect()
{
	renderer->DrawTexturedRect(
		0,
		0,
		0,
		800,
		1,
		1,
		1,
		1,
		background,
		BACKGOURND);
	for (int i = 0; i < MAX_OBJECTS; ++i)
	{
		
		if (draw_Object[i] != NULL)
		{			
			if (draw_Object[i]->type == OBJECT_BUILDING && draw_Object[i]->team == TEAM_1)
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
					team1BuildingTexture,
					BULDING);
				renderer->DrawSolidRectGauge(
					draw_Object[i]->xpos,
					draw_Object[i]->ypos+60,
					draw_Object[i]->zpos,
					80,10,
					1,
					0,
					0,
					1,
					1,
					BULDING);
			}
			else if(draw_Object[i]->type == OBJECT_BUILDING && draw_Object[i]->team == TEAM_2)
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
					team2BuildingTexture,
					BULDING);
				renderer->DrawSolidRectGauge(
					draw_Object[i]->xpos,
					draw_Object[i]->ypos + 60,
					draw_Object[i]->zpos,
					80, 10,
					0,
					0,
					1,
					1,
					1,
					BULDING);
			}
			else if(draw_Object[i]->type == OBJECT_CHARACTER && draw_Object[i]->team == TEAM_1)
			{
				renderer->DrawTexturedRectSeq(
					draw_Object[i]->xpos,
					draw_Object[i]->ypos,
					draw_Object[i]->zpos,
					draw_Object[i]->size,
					draw_Object[i]->r,
					draw_Object[i]->g,
					draw_Object[i]->b,
					draw_Object[i]->a,
					team1CharaterTexture,
					team1_character,
					0,
					9,
					2,
					CHARACTER);
				renderer->DrawSolidRectGauge(
					draw_Object[i]->xpos,
					draw_Object[i]->ypos + 40,
					draw_Object[i]->zpos,
					20, 2,
					1,
					0,
					0,
					1,
					1,
					CHARACTER);
			}
			else if (draw_Object[i]->type == OBJECT_CHARACTER && draw_Object[i]->team == TEAM_2)
			{
				renderer->DrawTexturedRectSeq(
					draw_Object[i]->xpos,
					draw_Object[i]->ypos,
					draw_Object[i]->zpos,
					draw_Object[i]->size,
					draw_Object[i]->r,
					draw_Object[i]->g,
					draw_Object[i]->b,
					draw_Object[i]->a,
					team2CharaterTexture,
					team2_character,
					0,
					8,
					2,
					CHARACTER);
				renderer->DrawSolidRectGauge(
					draw_Object[i]->xpos,
					draw_Object[i]->ypos + 40,
					draw_Object[i]->zpos,
					20, 2,
					0,
					0,
					1,
					1,
					1,
					CHARACTER);
			}
			else if (draw_Object[i]->type == OBJECT_ARROW)
			{
				renderer->DrawSolidRect(
					draw_Object[i]->xpos,
					draw_Object[i]->ypos,
					draw_Object[i]->zpos,
					draw_Object[i]->size,
					draw_Object[i]->r,
					draw_Object[i]->g,
					draw_Object[i]->b,
					draw_Object[i]->a,
					ARROW);
			}
			else if (draw_Object[i]->type == OBJECT_BULLET)
			{				
				renderer->DrawParticle(
					draw_Object[i]->xpos,
					draw_Object[i]->ypos,
					draw_Object[i]->zpos,
					draw_Object[i]->size,
					draw_Object[i]->r,
					draw_Object[i]->g,
					draw_Object[i]->b,
					draw_Object[i]->a,
					-draw_Object[i]->vxpos,
					-draw_Object[i]->vypos,
					bullet,
					draw_Object[i]->GetTime(),
					BULLET - 0.01
				);
			}

			else if (draw_Object[i]->type == OBJECT_WEATHER)
			{
				renderer->DrawParticleClimate(
					draw_Object[i]->xpos,
					draw_Object[i]->ypos,
					draw_Object[i]->zpos,
					draw_Object[i]->size,
					draw_Object[i]->r,
					draw_Object[i]->g,
					draw_Object[i]->b,
					draw_Object[i]->a,
					-draw_Object[i]->vxpos,
					-draw_Object[i]->vypos,
					weather,
					draw_Object[i]->GetTime(),
					BULLET - 0.01
				);
			}
			
			
		}
			
	}

	renderer->DrawTextW(-25, 200, GLUT_BITMAP_HELVETICA_18, 0, 0, 1, "TEAM RED");
	renderer->DrawTextW(-35, -200, GLUT_BITMAP_HELVETICA_18, 1, 0, 0, "TEAM BLUE");
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
						if (draw_Object[i]->team == draw_Object[j]->team)
							continue;
						collisionCount++;
						if (draw_Object[i]->type==1 && draw_Object[j]->type ==1)
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
