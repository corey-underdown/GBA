#include "CollisionManager.h"

void DetectCollision(GameObject* frogger){
	int i;
	for(i = 0; i < 127; i++)
	{
		if(g_GOFactory.GOList[i].alive == TRUE && i != 0)
		{
			int size1 = DetermineBounding(g_GOFactory.GOList[i].sprite->size);
			int size2 = DetermineBounding(frogger->sprite->size);
			if(g_GOFactory.GOList[i].sprite->x < frogger->sprite->x + size2  &&
			g_GOFactory.GOList[i].sprite->x + size1 > frogger->sprite->x &&
			g_GOFactory.GOList[i].sprite->y < frogger->sprite->y + size2 &&
			g_GOFactory.GOList[i].sprite->y + size1 > frogger->sprite->y)
			{
				ManagerCollision(frogger, &g_GOFactory.GOList[i]);
				return;
			}
		}
	}

	DetectCollisionTiles(frogger);
}

int DetermineBounding(int size)
{
	if(size == 0)
		return 8;
	if(size == 1)
		return 16;
	if(size == 2)
		return 32;
	if(size == 3)
		return 64;
}

void ManagerCollision(GameObject* frogger, GameObject* collision){
	switch(collision->type)
	{ 
		case ENUM_GOTYPE_TURTLE_SAFE:
		case ENUM_GOTYPE_LOG_MED:
			if(collision->enum_dir == ENUM_DIR_LEFT)
				frogger->sprite->x += collision->speed;
			else
				frogger->sprite->x -= collision->speed;
		break;
		case ENUM_GOTYPE_TURTLE_TEMP:	
			DetectCollisionTiles(frogger);
		break;
	}
}

void DetectCollisionTiles(GameObject* frogger){

} 