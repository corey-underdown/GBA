#include "CollisionManager.h"

void DetectCollision(GameObject* frogger){
	int i;
	for(i = 0; i < 127; i++)
	{
		if(g_GOFactory.GOList[i].alive == TRUE && i != 0)
		{
			if(g_GOFactory.GOList[i].sprite->x < frogger->sprite->x + 8 &&
			g_GOFactory.GOList[i].sprite->x + 8 > frogger->sprite->x &&
			g_GOFactory.GOList[i].sprite->y < frogger->sprite->y + 8 &&
			g_GOFactory.GOList[i].sprite->y + 8 > frogger->sprite->y)
			{
				ManagerCollision(frogger, &g_GOFactory.GOList[i]);
				return;
			}
		}
	}

	DetectCollisionTiles(frogger);
}

void ManagerCollision(GameObject* frogger, GameObject* collision){
	switch(collision->type)
	{
		case ENUM_GOTYPE_TURTLE_SAFE:
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