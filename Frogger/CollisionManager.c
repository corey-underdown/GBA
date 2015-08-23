#include "CollisionManager.h"



void DetectCollision(GameObject* frogger){
	int i;
	for(i = 0; i < 127; i++)
	{
		if(g_GOFactory.GOList[i].alive == TRUE && i != 0)
		{
			int offset = 4;
			Bounds size1;
			size1 = DetermineBounding(g_GOFactory.GOList[i].sprite->shape, g_GOFactory.GOList[i].sprite->size);
			Bounds size2;
			size2 = DetermineBounding(frogger->sprite->shape, frogger->sprite->size);
			if(g_GOFactory.GOList[i].sprite->x + offset < frogger->sprite->x + size2.x - offset &&
			g_GOFactory.GOList[i].sprite->x + size1.x - offset > frogger->sprite->x + offset &&
			g_GOFactory.GOList[i].sprite->y + offset < frogger->sprite->y + size2.y - offset &&
			g_GOFactory.GOList[i].sprite->y + size1.y - offset > frogger->sprite->y + offset)
			{
				ManagerCollision(frogger, &g_GOFactory.GOList[i]);
				return;
			}
		}
	}

	DetectCollisionTiles(frogger);
}

Bounds DetermineBounding(int shape, int size)
{
	Bounds temp;
	if (shape == 0)
	{
		if(size == 0)
		{
			temp.x = 8;
			temp.y = 8;
		}
		else if(size == 1)
		{
			temp.x = 16;
			temp.y = 16;
		}
		else if(size == 2)
		{
			temp.x = 32;
			temp.y = 32;
		}
		else if(size == 3)
		{
			temp.x = 64;
			temp.y = 64;
		}
	}
	else if (shape == 1)
	{
		if(size == 0)
		{
			temp.x = 16;
			temp.y = 8;
		}
		else if(size == 1)
		{
			temp.x = 32;
			temp.y = 8;
		}
		else if(size == 2)
		{
			temp.x = 32;
			temp.y = 16;
		}
		else if(size == 3)
		{
			temp.x = 64;
			temp.y = 32;
		}
	}
	else if (shape == 2)
	{
		if(size == 0)
		{
			temp.x = 8;
			temp.y = 16;
		}
		else if(size == 1)
		{
			temp.x = 8;
			temp.y = 32;
		}
		else if(size == 2)
		{
			temp.x = 16;
			temp.y = 32;
		}
		else if(size == 3)
		{
			temp.x = 32;
			temp.y = 64;
		}
	}
	return temp;
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