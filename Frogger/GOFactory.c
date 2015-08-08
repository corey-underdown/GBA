#include "GOFactory.h"

GOFactory g_GOFactory;




void GOFactory_Init()
{
	int i = 0;

	for (i = 0; i < 128; i++)
	{
	//set all index numbers to 200
		g_GOFactory.indexList[i] = 200;
	//Set all Sprite data to not display
		g_GOFactory.ghostOAM[i].y = 200;
	//Set all game objects z to 1000;
		g_GOFactory.GOList[i].alive = FALSE;
	//
	//Zero the goCount
	//
	}

}

GameObject* GOFactory_New(int enum_type, int posX, int posY, int enum_dir, float speed)
{
	int i = 0;
	//Find First Available GameObject Spot
	for (i = 0; i < 128; i++)
	{
		if (g_GOFactory.GOList[i].alive == FALSE)
		{
			//Spot is Available.
			g_GOFactory.indexList[g_GOFactory.goCount] = i;
			//Set as Active or Alive
			g_GOFactory.GOList[i].alive = TRUE;
			//Set Sprite
			g_GOFactory.GOList[i].sprite = &(g_GOFactory.ghostOAM[g_GOFactory.goCount]);
			//Set Index
			g_GOFactory.GOList[i].index = &(g_GOFactory.indexList[g_GOFactory.goCount]);
			//Set all default Properties
			g_GOFactory.GOList[i].sprite->y = posY;//Set Init Position
			g_GOFactory.GOList[i].sprite->enableRotation = 0;//Do not allow rotation
			g_GOFactory.GOList[i].sprite->dubScale = 0;//off
			g_GOFactory.GOList[i].sprite->alpha = 0;//?????????????????????????????????????
			g_GOFactory.GOList[i].sprite->mosaic = 0;//Off
			g_GOFactory.GOList[i].sprite->colourMode = 0;//16 colour
			g_GOFactory.GOList[i].sprite->x = posX;//Set Init Position
			g_GOFactory.GOList[i].sprite->priority = 2;//Allows 1 BG layer behind
			g_GOFactory.GOList[i].sprite->rotation = 0;//actual rotation
			g_GOFactory.GOList[i].sprite->vertFlip = 0;//IF enabelRotation = 1, Do not set this value

			//Set Flip to direction of type.
			if (enum_dir == ENUM_DIR_LEFT)
				g_GOFactory.GOList[i].sprite->horzFlip = 0;//IF enabelRotation = 1, Do not set this value
			else if (enum_dir == ENUM_DIR_RIGHT)
				g_GOFactory.GOList[i].sprite->horzFlip = 1;//IF enabelRotation = 1, Do not set this value
			


			if (enum_type == ENUM_GOTYPE_FROGGER)
			{
			g_GOFactory.GOList[i].sprite->shape = 0;//Square or Rect
			g_GOFactory.GOList[i].sprite->spcRotation = 0;//DEpending on prvious values this will change.
			g_GOFactory.GOList[i].sprite->size = 0;//0, 1, 2 ,3 ,4  0 = 8 pixels, 1 = 16 pixels, 2 = 32 pixels, 3 = 64 pixels depending on the sprite size
			g_GOFactory.GOList[i].sprite->tileIndex = 0;//first tile in tile array.
			g_GOFactory.GOList[i].sprite->pallet = 0;

			}


			g_GOFactory.goCount ++;
			return &g_GOFactory.GOList[i];
		}



	}

	
	//Run a sort 
	//SOMTHING WENT WRONG
	return &g_GOFactory.GOList[i];
}

void GOFactory_Delete(GameObject* gameobject)
{
	//GOFactor.goCount --;
	//set game object to not alive, set z value to be 1000,
	//Set sprite data to be not displayed move to back of array.
	//set index to be 200 move to back of array

}

void GOFactory_CopytoOAM()
{
	memcpy ((char*)SPRITE_OAM, ((char*)&(g_GOFactory.ghostOAM[0])), (sizeof(SpriteData) * 128));
}

