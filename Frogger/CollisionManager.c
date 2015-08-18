#include "CollisionManager.h"

void DetectCollision(GameObject* frogger){
	for(int i = 0; i < 127; i++)
	{
		if(g_GOFactory.GOList[i].alive == TRUE && i != 0)
		{
			if(g_GOFactory.GOList[i].sprite->x < frogger->sprite->x + 8 &&
			g_GOFactory.GOList[i].sprite->x + 8 > frogger->sprite->x &&
			g_GOFactory.GOList[i].sprite->y < frogger->sprite->y + 8 &&
			g_GOFactory.GOList[i].sprite->y + 8 > frogger->sprite->y)
			{
				PrintTextInt(i);	
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