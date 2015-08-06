#include <stdio.h>
#include "toolbox.h"
#include "images/TestImage.h"
//#include "SpriteFactory.h"
 
typedef struct 
{
	unsigned char y;
	unsigned char enableRotation:1;
	unsigned char dubScale:1;
	unsigned char alpha:2;
	unsigned char mosaic:1;
	unsigned char colourMode:1;//16 or 256 colour
	unsigned char shape:2;//Square or Rect
	unsigned short x:9;
	unsigned char special:5;//DEpending on prvious values this will change.
	unsigned char size:2;//0 8 16 32 64 depending on the sprite size
	unsigned short tileIndex:10;//first tile in tile array.
	unsigned char priority:2;
	unsigned char pallet:4;
	unsigned short rotation;//actual rotation
}SpriteData;

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
	//REG_DISPCNT = DCNT_MODE3 | DCNT_BG2;

	waitVBlank();

 	//HACK to create temporary tile
	memcpy(((void*)SPRITE_TILEDATA), (void*)Bitmap,32);  

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

	//HACK create palette
	shortCopy((u16*)SPRITE_PAL_DATA, (u16*)Palette, 256); 

	//set background palette  
	//shortCopy((void*)TILE_PAL_DATA, (void*)Palette, 256);

	/*TileData tData;
	tData.tile = 0;
	tData.horizontalFlip = 0;
	tData.verticalFlip = 0;
	tData.palette = 0;*/

	//shortCopy((u16*)MEM_VRAM, (u16*)&tData, 32);

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

	((unsigned short*)TILE_LOCATION)[120+80*240] = 0x001F;

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
		//shortCopy((u16*)SPRITE_TILEDATA, (u16*)&tData, 32);
		
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
