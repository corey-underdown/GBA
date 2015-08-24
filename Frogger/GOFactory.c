#include "GOFactory.h"
#include "images/GO_Palette.h"
#include "images/GO_Tiles.h"
#include "GOUpdates.h"
#include "TextManager.h"


GOFactory g_GOFactory;


void GOFactory_ToggleSpritesIsActive(BOOL toggle)
{
	u16 temp = REG_DISPCNT;

	temp = temp & 0x0FFF;

	temp = temp | (toggle << 12);

	REG_DISPCNT = temp;  
}

BOOL GOFactory_GetSpritesIsActive()
{
	u16 temp = REG_DISPCNT;

	temp = temp & 0xF000;

	temp = temp & (1 << 12);

	return temp;
}

void GOFactory_Init()
{
	//create palette
	shortCopy((u16*)SPRITE_PAL_DATA, (u16*)GO_PALETTE, 256);
	//Copy Sprites
	shortCopy((u16*)SPRITE_BITMAPS, (u16*)GO_TILES, 16 * 64);

	int i = 0;

	for (i = 0; i < 128; i++)
	{
	//set all index numbers to 200
		g_GOFactory.indexList[i] = 200;
	//Set all Sprite data to not display
		g_GOFactory.ghostOAM[i].y = 500;
	//Set all game objects z to 1000;
		g_GOFactory.GOList[i].alive = FALSE;
		g_GOFactory.GOList[i].Update = &GO_Update_Default;
	//
	//Zero the goCount
	//
	}

}

void GOFactory_Update()
{
	int i = 0;
	for (i = 0; i < 128; i ++)
	{
		g_GOFactory.GOList[i].Update(i);
	}
}

GameObject* GOFactory_New(int enum_type, int posX, int posY, int enum_dir, int speed)
{
	int i = 0;
	//Find First Available GameObject Spot
	for (i = 0; i < 128; i++)
	{
		if (g_GOFactory.GOList[i].alive == FALSE)
		{
			GOFactory_Sort();
			//Spot is Available.
			g_GOFactory.indexList[g_GOFactory.goCount] = i;
			//Set as Active or Alive
			g_GOFactory.GOList[i].alive = TRUE;
			//Set Sprite
			g_GOFactory.GOList[i].sprite = &(g_GOFactory.ghostOAM[g_GOFactory.goCount]);
			//Set Index
			g_GOFactory.GOList[i].index = &(g_GOFactory.indexList[g_GOFactory.goCount]);
			//Set Default Update
			g_GOFactory.GOList[i].Update = &GO_Update_Default;
			//Set the facing Dir
			g_GOFactory.GOList[i].enum_dir = enum_dir;
			//Set the gameobject type 
			g_GOFactory.GOList[i].type = enum_type; 
			//set the gameobject speed
			g_GOFactory.GOList[i].speed = speed;
			g_GOFactory.GOList[i].counter = 0;
			g_GOFactory.GOList[i].timer = 120;
			//Set all default Properties
			g_GOFactory.GOList[i].sprite->y = posY;//Set Init Position
			g_GOFactory.GOList[i].sprite->enableRotation = 0;//Do not allow rotation
			g_GOFactory.GOList[i].sprite->dubScale = 0;//off
			g_GOFactory.GOList[i].sprite->alpha = 0;//?????????????????????????????????????
			g_GOFactory.GOList[i].sprite->mosaic = 0;//Off
			g_GOFactory.GOList[i].sprite->colourMode = 0;//16 colour
			g_GOFactory.GOList[i].sprite->x = posX;//Set Init Position
			g_GOFactory.GOList[i].sprite->priority = 1;//Allows 1 BG layer behind
			g_GOFactory.GOList[i].sprite->rotation = 0;//actual rotation
			g_GOFactory.GOList[i].sprite->vertFlip = 0;//IF enabelRotation = 1, Do not set this value
			g_GOFactory.GOList[i].z_Depth = 10;

			//Set Flip to direction of type.
			if (enum_dir == ENUM_DIR_LEFT)
				g_GOFactory.GOList[i].sprite->horzFlip = 0;//IF enabelRotation = 1, Do not set this value
			else if (enum_dir == ENUM_DIR_RIGHT)
				g_GOFactory.GOList[i].sprite->horzFlip = 1;//IF enabelRotation = 1, Do not set this value
			


			if (enum_type == ENUM_GOTYPE_FROGGER)
			{
			g_GOFactory.GOList[i].sprite->shape = 0;//0 = Square, 1 = Wide, 2 = Tall
			g_GOFactory.GOList[i].sprite->spcRotation = 0;//DEpending on prvious values this will change.
			g_GOFactory.GOList[i].sprite->size = 1;//0, 1, 2 ,3 ,4  0 = 8 pixels, 1 = 16 pixels, 2 = 32 pixels, 3 = 64 pixels depending on the sprite size
			g_GOFactory.GOList[i].sprite->tileIndex = 0;//first tile in tile array.
			g_GOFactory.GOList[i].sprite->pallet = 3;
			g_GOFactory.GOList[i].Update = &GO_Update_Frogger;
			g_GOFactory.GOList[i].z_Depth = 0;
			}
			else if (enum_type == ENUM_GOTYPE_CAR_RACE)
			{
			g_GOFactory.GOList[i].sprite->shape = 0;//0 = Square, 1 = Wide, 2 = Tall
			g_GOFactory.GOList[i].sprite->spcRotation = 0;//DEpending on prvious values this will change.
			g_GOFactory.GOList[i].sprite->size = 1;//0, 1, 2 ,3 ,4  0 = 8 pixels, 1 = 16 pixels, 2 = 32 pixels, 3 = 64 pixels depending on the sprite size
			g_GOFactory.GOList[i].sprite->tileIndex = 4;//first tile in tile array.
			g_GOFactory.GOList[i].sprite->pallet = 0;
			g_GOFactory.GOList[i].Update = &GO_Update_RacingCar;
			g_GOFactory.GOList[i].sprite->horzFlip = !g_GOFactory.GOList[i].sprite->horzFlip;
			}
			else if (enum_type == ENUM_GOTYPE_CAR)
			{
			g_GOFactory.GOList[i].sprite->shape = 0;//0 = Square, 1 = Wide, 2 = Tall
			g_GOFactory.GOList[i].sprite->spcRotation = 0;//DEpending on prvious values this will change.
			g_GOFactory.GOList[i].sprite->size = 1;//0, 1, 2 ,3 ,4  0 = 8 pixels, 1 = 16 pixels, 2 = 32 pixels, 3 = 64 pixels depending on the sprite size
			g_GOFactory.GOList[i].sprite->tileIndex = 48;//first tile in tile array.
			g_GOFactory.GOList[i].sprite->pallet = 8;
			g_GOFactory.GOList[i].Update = &GO_Update_RacingCar;
			}
			else if (enum_type == ENUM_GOTYPE_TRUCK_TRAILER)
			{
			g_GOFactory.GOList[i].sprite->shape = 1;//0 = Square, 1 = Wide, 2 = Tall
			g_GOFactory.GOList[i].sprite->spcRotation = 0;//DEpending on prvious values this will change.
			g_GOFactory.GOList[i].sprite->size = 2;//0, 1, 2 ,3 ,4  0 = 8 pixels, 1 = 16 pixels, 2 = 32 pixels, 3 = 64 pixels depending on the sprite size
			g_GOFactory.GOList[i].sprite->tileIndex = 52;//first tile in tile array.
			g_GOFactory.GOList[i].sprite->pallet = 8;
			g_GOFactory.GOList[i].Update = &GO_Update_RacingCar;
			}
			else if (enum_type == ENUM_GOTYPE_TRUCK_CABIN)
			{
			g_GOFactory.GOList[i].sprite->shape = 0;//0 = Square, 1 = Wide, 2 = Tall
			g_GOFactory.GOList[i].sprite->spcRotation = 0;//DEpending on prvious values this will change.
			g_GOFactory.GOList[i].sprite->size = 1;//0, 1, 2 ,3 ,4  0 = 8 pixels, 1 = 16 pixels, 2 = 32 pixels, 3 = 64 pixels depending on the sprite size
			g_GOFactory.GOList[i].sprite->tileIndex = 60;//first tile in tile array.
			g_GOFactory.GOList[i].sprite->pallet = 8;
			g_GOFactory.GOList[i].Update = &GO_Update_RacingCar;
			g_GOFactory.GOList[i].sprite->horzFlip = !g_GOFactory.GOList[i].sprite->horzFlip;
			}
			else if(enum_type == ENUM_GOTYPE_LOG_SMALL)
			{
			//Extra checks because corey can't draw sprites the right way
			//Set Flip to direction of type.
			if (enum_dir == ENUM_DIR_LEFT)
				g_GOFactory.GOList[i].sprite->horzFlip = 1;//IF enabelRotation = 1, Do not set this value
			else if (enum_dir == ENUM_DIR_RIGHT)
				g_GOFactory.GOList[i].sprite->horzFlip = 0;//IF enabelRotation = 1, Do not set this value
			g_GOFactory.GOList[i].sprite->shape = 0;//0 = Square, 1 = Wide, 2 = Tall
			g_GOFactory.GOList[i].sprite->spcRotation = 0;//DEpending on prvious values this will change.
			g_GOFactory.GOList[i].sprite->size = 1;//0, 1, 2 ,3 ,4  0 = 8 pixels, 1 = 16 pixels, 2 = 32 pixels, 3 = 64 pixels depending on the sprite size
			g_GOFactory.GOList[i].sprite->tileIndex = 8;//first tile in tile array.
			g_GOFactory.GOList[i].sprite->pallet = 5;
			g_GOFactory.GOList[i].Update = &GO_Update_RacingCar;
			}
			else if(enum_type == ENUM_GOTYPE_LOG_MED)
			{
			//Extra checks because corey can't draw sprites the right way
			//Set Flip to direction of type.
			if (enum_dir == ENUM_DIR_LEFT)
				g_GOFactory.GOList[i].sprite->horzFlip = 1;//IF enabelRotation = 1, Do not set this value
			else if (enum_dir == ENUM_DIR_RIGHT)
				g_GOFactory.GOList[i].sprite->horzFlip = 0;//IF enabelRotation = 1, Do not set this value
			g_GOFactory.GOList[i].sprite->shape = 1;//0 = Square, 1 = Wide, 2 = Tall
			g_GOFactory.GOList[i].sprite->spcRotation = 0;//DEpending on prvious values this will change.
			g_GOFactory.GOList[i].sprite->size = 2;//0, 1, 2 ,3 ,4  0 = 8 pixels, 1 = 16 pixels, 2 = 32 pixels, 3 = 64 pixels depending on the sprite size
			g_GOFactory.GOList[i].sprite->tileIndex = 12;//first tile in tile array.
			g_GOFactory.GOList[i].sprite->pallet = 8;
			g_GOFactory.GOList[i].Update = &GO_Update_RacingCar;
			}
			else if(enum_type == ENUM_GOTYPE_LOG_LARGE)
			{
			//Extra checks because corey can't draw sprites the right way
			//Set Flip to direction of type.
			if (enum_dir == ENUM_DIR_LEFT)
				g_GOFactory.GOList[i].sprite->horzFlip = 1;//IF enabelRotation = 1, Do not set this value
			else if (enum_dir == ENUM_DIR_RIGHT)
				g_GOFactory.GOList[i].sprite->horzFlip = 0;//IF enabelRotation = 1, Do not set this value
			g_GOFactory.GOList[i].sprite->shape = 1;//0 = Square, 1 = Wide, 2 = Tall
			g_GOFactory.GOList[i].sprite->spcRotation = 0;//DEpending on prvious values this will change.
			g_GOFactory.GOList[i].sprite->size = 2;//0, 1, 2 ,3 ,4  0 = 8 pixels, 1 = 16 pixels, 2 = 32 pixels, 3 = 64 pixels depending on the sprite size
			g_GOFactory.GOList[i].sprite->tileIndex = 20;//first tile in tile array.
			g_GOFactory.GOList[i].sprite->pallet = 5;
			g_GOFactory.GOList[i].Update = &GO_Update_RacingCar;
			}
			else if (enum_type == ENUM_GOTYPE_TURTLE_SAFE)
			{
			g_GOFactory.GOList[i].timer = 240;
			//Extra checks because corey can't draw sprites the right way
			//Set Flip to direction of type.
			if (enum_dir == ENUM_DIR_LEFT)
				g_GOFactory.GOList[i].sprite->horzFlip = 1;//IF enabelRotation = 1, Do not set this value
			else if (enum_dir == ENUM_DIR_RIGHT)
				g_GOFactory.GOList[i].sprite->horzFlip = 0;//IF enabelRotation = 1, Do not set this value
			g_GOFactory.GOList[i].sprite->shape = 0;//0 = Square, 1 = Wide, 2 = Tall
			g_GOFactory.GOList[i].sprite->spcRotation = 0;//DEpending on prvious values this will change.
			g_GOFactory.GOList[i].sprite->size = 1;//0, 1, 2 ,3 ,4  0 = 8 pixels, 1 = 16 pixels, 2 = 32 pixels, 3 = 64 pixels depending on the sprite size
			g_GOFactory.GOList[i].sprite->tileIndex = 32;//first tile in tile array.
			g_GOFactory.GOList[i].sprite->pallet = 8;
			//g_GOFactory.GOList[i].counter = 0;
			//g_GOFactory.GOList[i].timer = 120;
			g_GOFactory.GOList[i].Update = &GO_Update_Turtle;
			}
			else 
			{
			g_GOFactory.GOList[i].sprite->shape = 0;//Square or Rect
			g_GOFactory.GOList[i].sprite->spcRotation = 0;//DEpending on prvious values this will change.
			g_GOFactory.GOList[i].sprite->size = 0;//0, 1, 2 ,3 ,4  0 = 8 pixels, 1 = 16 pixels, 2 = 32 pixels, 3 = 64 pixels depending on the sprite size
			g_GOFactory.GOList[i].sprite->tileIndex = 0;//first tile in tile array.
			g_GOFactory.GOList[i].sprite->pallet = 8;
			}




			g_GOFactory.goCount ++;
			GOFactory_Sort();
			return &g_GOFactory.GOList[i];
		}



	}

	
	//Run a sort 
	//SOMTHING WENT WRONG
	return &g_GOFactory.GOList[i];
}

void GOFactory_Delete(GameObject* gameobject)
{
	if (gameobject->alive == TRUE)
	{
		g_GOFactory.goCount -= 1;
		//set game object to not alive, set z value to be 1000,
		gameobject->alive = FALSE;
		gameobject->sprite = 0;
		//set index to be 200 
		*(gameobject->index) = 200;
		//Set sprite data to be not displayed 
		gameobject->sprite->y = 500;
		gameobject->sprite->tileIndex = 0;

		GOFactory_Sort();
	}
}

void GOFactory_CopytoOAM()
{
	GOFactory_Sort();
	memcpy ((char*)SPRITE_OAM, ((char*)&(g_GOFactory.ghostOAM[0])), (sizeof(SpriteData) * 128));
}

void GOFactory_Swap(int i, int j)
{
	//Swap items
	//Swap Pointers
	//Point to new Index and Spritedata
	g_GOFactory.GOList[g_GOFactory.indexList[i]].sprite = &g_GOFactory.ghostOAM[j];
	g_GOFactory.GOList[g_GOFactory.indexList[i]].index = &g_GOFactory.indexList[j];

	g_GOFactory.GOList[g_GOFactory.indexList[j]].sprite = &g_GOFactory.ghostOAM[i];
	g_GOFactory.GOList[g_GOFactory.indexList[j]].index = &g_GOFactory.indexList[i];
	//Swap Memory
	//Ghost OAM
	SpriteData temp = g_GOFactory.ghostOAM[i];
	g_GOFactory.ghostOAM[i] = g_GOFactory.ghostOAM[j];
	g_GOFactory.ghostOAM[j] = temp;
	//Index Data
	int tempInt = g_GOFactory.indexList[i];
	g_GOFactory.indexList[i] = g_GOFactory.indexList[j];
	g_GOFactory.indexList[j] = tempInt;
}

void GOFactory_Sort()
{
	int i = 0;

	int finished = FALSE;

	while (!finished)
	{
		finished = TRUE;

		for (i = 0; i < 127; i++)
		{
			if (g_GOFactory.indexList[i] == 200)
			{
				if (g_GOFactory.indexList[i + 1] != 200)
				{
					finished = FALSE;
					GOFactory_Swap(i, i+1);
				}
			}
			else if (g_GOFactory.indexList[i + 1] == 200)
			{
				//Do Nothing 
			}
			else if (g_GOFactory.GOList[g_GOFactory.indexList[i]].z_Depth > g_GOFactory.GOList[g_GOFactory.indexList[i + 1]].z_Depth)
			{
				finished = FALSE;

				GOFactory_Swap(i, i+1);
			}
		}
	}
}

void GOFactory_ShiftGOsDown()
{
	int i;
	for (i = 0; i < 128; i++)
	{
		if (g_GOFactory.GOList[i].alive == TRUE)
		{
			if(g_GOFactory.GOList[i].type != ENUM_GOTYPE_FROGGER)
			{
				g_GOFactory.GOList[i].sprite->y += 16;
				if(g_GOFactory.GOList[i].sprite->y >= 164 && g_GOFactory.GOList[i].sprite->y <= 180)
					GOFactory_Delete(&g_GOFactory.GOList[i]);
			}
		}
	}
}


