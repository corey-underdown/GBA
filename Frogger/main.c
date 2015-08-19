#include <stdio.h>
#include "toolbox.h"
#include "images/TestImage.h"
#include "images/TextBitmap.h"
#include "GOFactory.h"
#include "TextManager.h"
#include "input.h"
#include "CollisionManager.h"
//#include "images/Text_Tiles.h"



typedef struct 
{
	unsigned short tile:10;
	unsigned char horizontalFlip:1;
	unsigned char verticalFlip:1;
	unsigned char palette:4;
}TileData;

typedef struct 
{
	unsigned char priority:2;
	unsigned char startAdressTileData:2;
	unsigned char unused:2;
	unsigned char mosaic:1;
	unsigned char paletteType:1;
	unsigned char startAdressTileMap:5;
	unsigned char areaOverflow:1;
	unsigned char sizeMap:2;
}MapProperties;

int debug = 1;

/*Frogger "Class"*/
int froggerCooldown = 10;
int froggerCounter = 0;
void FroggerUpdate(GameObject* frogger)
{
	froggerCounter += 1;
	DetectCollision(frogger);

	if(froggerCounter >= froggerCooldown)
	{
		BOOL moved = FALSE;
		if (! ((*KEYS) & KEY_RIGHT))
		{
			frogger->sprite->x += 16;
			moved = TRUE;
		}
		if (! ((*KEYS) & KEY_LEFT))
		{
			frogger->sprite->x -= 16;
			moved = TRUE;
		}
		if (! ((*KEYS) & KEY_UP))
		{
			frogger->sprite->y -= 16;
			moved = TRUE;
		}
		if (! ((*KEYS) & KEY_DOWN))
		{
			frogger->sprite->y += 16;
			moved = TRUE;
		}

		if(moved == TRUE)
			froggerCounter = 0;
	}	
}

int main()
{
	//Enable Sprites
	REG_DISPCNT = 0x1100;
	//REG_DISPCNT = REG_DISPCNT - 0x0100;

	waitVBlank();

	BGManager_Init();
	BGManager_CopyVRAM();

	//HACK create palette
	shortCopy((u16*)SPRITE_PAL_DATA, (u16*)Palette, 256);
	shortCopy((u16*)SPRITE_BITMAPS, (u16*)Bitmap, 80);

	TileData tData; 
	tData.tile = 1;
	tData.horizontalFlip = 0;
	tData.verticalFlip = 0;
	tData.palette = 0;

	//shortCopy((u16*)BG_MAP_0, (u16*)&tData, 1);
	//Set the first tile to 0 so it won't render any of them
	((u16*)BG_MAP_0)[0]=0;

	PrintText("abcdefghijklmnopqrstuvwxyz");
	PrintText("0123456789");
	PrintText(" !@#$^&*()");



	MapProperties mp0;
	MapProperties mp1;
	MapProperties mp2;
	MapProperties mp3;

	mp0.priority = 0;
	mp0.startAdressTileData = 0;
	mp0.unused = 0;
	mp0.mosaic = 0;
	mp0.paletteType = 0;
	mp0.startAdressTileMap = 12;
	mp0.areaOverflow = 0;
	mp0.sizeMap = 0; 
	
	mp1.priority = 0;
	mp1.startAdressTileData = 1;
	mp1.unused = 0;
	mp1.mosaic = 0;
	mp1.paletteType = 0;
	mp1.startAdressTileMap = 12;
	mp1.areaOverflow = 0;
	mp1.sizeMap = 0; 

	shortCopy((u16*)BG_MAP_PROP_0, (u16*)&mp0, 1);
	shortCopy((u16*)BG_MAP_PROP_1, (u16*)&mp1, 1);

	//Game Object Factory Using==================================================
	
	//Setting Up Sprites
	GOFactory_Init();

	GameObject* player = GOFactory_New(ENUM_GOTYPE_FROGGER, 100, 20,ENUM_DIR_LEFT, 20);

	//GameObject* other = GOFactory_New(ENUM_GOTYPE_FROGGER, 80,80,ENUM_DIR_LEFT, 20);



	//Testy for z Depth
	GameObject* other1 = GOFactory_New(1, 80,80,ENUM_DIR_LEFT, 20);
	GameObject* other2 = GOFactory_New(2, 76,84,ENUM_DIR_LEFT, 20);
	GameObject* other3 = GOFactory_New(3, 84,84,ENUM_DIR_LEFT, 20);
	GameObject* other4 = GOFactory_New(4, 80,76,ENUM_DIR_LEFT, 20);

	other1->z_Depth = 0;
	other2->z_Depth = 10;
	other3->z_Depth = 20;
	other4->z_Depth = 30;


	GameObject* other5 = GOFactory_New(4, 100,100,ENUM_DIR_LEFT, 20);
	other5->z_Depth = 0;




	GOFactory_CopytoOAM();

	//Gregs Program ===============================================
	/*
	SpriteData mysp;
	mysp.x = 30;
	mysp.y = 20;
	mysp.enableRotation = 0;
	mysp.dubScale = 0;
	mysp.alpha = 0;
	mysp.mosaic = 0;//off
	mysp.colourMode = 0;//16bit
	mysp.shape = 0; //square
	mysp.special = 0;
	mysp.size = 0;// = 8 pixels wide;
	mysp.tileIndex = 0;	
	mysp.priority = 0;
	mysp.pallet = 0;
	mysp.rotation = 0;

	shortCopy((u16*)SPRITE_OAM, (u16*)&mysp,4);

	*/

  

	int y = 0;
	int z = 1;
	
	while(1)
	{
		//Update keys
		//PollKeys();
		//Gmae Object Factory Code================================
		other5->sprite->x += 1;
		//other->sprite->y = x;
		if(other5->sprite->x > 240)
			other5->sprite->x=0;

		//Test for z depth
		y += z;
		if (y > 40)
		{
			GOFactory_Delete(other5);
			other5 = GOFactory_New(4, 150,30,ENUM_DIR_LEFT, 20);
			y = 40;
			z = -1;
			//PrintText("a");
		}
		else if (y < 0)
		{
			GOFactory_Delete(other5);
			other5 = GOFactory_New(3, 150,38,ENUM_DIR_LEFT, 20);
			y = 0;
			z = 1;
			//PrintText("b");
		}

		other1->z_Depth = y;

		//Toggle Debug Text===================================
		/*if(WasKeyDown(KEY_L))
		{
			if(debug == 1)
			{
				REG_DISPCNT = REG_DISPCNT - 0x0100;
				debug = 0;
			}
			else
			{
				REG_DISPCNT = REG_DISPCNT + 0x0100;
				debug = 1;	
			}
		}*/

		FroggerUpdate(player);

		waitVBlank();
		GOFactory_CopytoOAM();
		waitVDraw();

		//Gregs Code==========================================
		/*
		mysp.x = x;
		x++;
		if(x>240)
			x=0;
		
		waitVBlank();
		shortCopy((u16*)SPRITE_OAM, (u16*)&mysp,4);
		waitVDraw();
		*/
	}

	return 0;
}
