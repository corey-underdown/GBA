#include "CollisionManager.h"

void DetectCollision(GameObject* frogger){
	for(int i = 0; i < 127; i++)
	{
		if(g_GOFactory.GOList[i].alive == TRUE)
		{
			if(g_GOFactory.GOList[i].sprite->x < frogger->sprite->x + 16 &&
			g_GOFactory.GOList[i].sprite->x + 16 > frogger->sprite->x &&
			g_GOFactory.GOList[i].sprite->y < frogger->sprite->y + 16 &&
			g_GOFactory.GOList[i].sprite->y + 16 > frogger->sprite->y)
			{
				//PrintText("Collision");	
			}
		}
	}
}

int abs(int value)
{
	if(value >= 0)
		return value;
	else
		return -1 * value;
}


void ManagerCollision(GameObject* frogger, GameObject* collision){}
void DetectCollisionTiles(GameObject* frogger){} 