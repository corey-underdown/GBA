#include <stdio.h>
#include "toolbox.h"
#include "images/TestImage.h"
#include "SpriteFactory.h"

typedef struct 
{
	unsigned short tile:10;
	unsigned char horizontalFlip:1;
	unsigned char verticalFlip:1;
	unsigned char palette:4;
}TileData;

int main()
{
	
	//Enable Sprites
    REG_DISPCNT = 0x1f00;

	waitVBlank();

 	//HACK to create temporary tile
	memcpy(((void*)TILE_LOCATION), (void*)BitmapA,32);  

	//HACK create palette
	shortCopy((u16*)SPRITE_PAL_DATA, (u16*)Palette, 256); 

	//set background palette  
	shortCopy((void*)TILE_PAL_DATA, (void*)Palette, 256);

	TileData tData;
	tData.tile = 0;
	tData.horizontalFlip = 0;
	tData.verticalFlip = 0;
	tData.palette = 1;

	shortCopy((u16*)SPRITE_TILEDATA, (u16*)&tData, 32);

	//Sprite Factory Using==================================================
	//SpriteFactory* spf = Ghost_OAM_Create();

	//SpriteData* temp = Ghost_OAM_GetSprite_int(spf, 0); 

	/*temp->x = 30;
    temp->y = 20;
   	temp->enableRotation = 0;
	temp->dubScale = 0;
	temp->alpha = 0;
	temp->mosaic = 0;//off
	temp->colourMode = 0;//16bit
	temp->shape = 0; //square
	temp->special = 0;
	temp->size = 0;// = 8 pixels wide;
	temp->tileIndex = 0;	
	temp->priority = 0;
	temp->pallet = 0;
	temp->rotation = 0;
	
	Ghost_OAM_CopytoOAM(spf);
	*/


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

	int x=0;    
	
	while(1)
    {
    	//Sprite Factory Code================================
    	//temp->x = x;

    	//Ghost_OAM_SetSprite_int(spf, 0, temp);
		x++;
		if(x>240)
			x=0;
		
		waitVBlank();
		//Ghost_OAM_CopytoOAM(spf);
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
