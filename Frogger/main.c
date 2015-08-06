#include <stdio.h>
#include "toolbox.h"
#include "input.h"
#include "images/TestImage.h"

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
	unsigned char size:2;//8 16 32 64 depending on the sprite size
	unsigned short tileIndex:10;//first tile in tile array.
	unsigned char priority:2;
	unsigned char pallet:4;
	unsigned short rotation;//acutal rotation
}SpriteData;

void waitVBlank()
{
	while(*(( volatile u16*)(VCOUNT)) <= 159)
	{}
}

void waitVDraw()
{
	while(*(( volatile u16*)(VCOUNT)) > 159)
	{}
}

void shortCopy(u16 *dest, u16 *src, int shortCount)
{
	int i;
	for(i=0;i<shortCount;++i)
	{
		*dest++ = *src++;
	}
}

int main()
{
	
	//Enable SPtrites
    REG_DISPCNT = 0x1f00;


	waitVBlank();

 
	memcpy((void*)SPRITE_TILEDATA, (void*)Bitmap,32);   
	
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

	shortCopy((u16*)SPRITE_PAL_DATA, (u16*)Palette, 256);

	shortCopy((u16*)SPRITE_OAM, (u16*)&mysp,4);
	
	//set background palette
	((volatile unsigned short*)(0x05000000))[0] = CLR_RED;

	int x = mysp.x;  
	int y = mysp.y;  
	
	while(1)
    {

    	//Logic
    	
    	if(isKeyDown(KEY_UP) == 1)
    	{
    		y--;
    	}else if(isKeyDown(KEY_DOWN) == 1)
    	{
    		y++;
    	}else if(isKeyDown(KEY_RIGHT) == 1)
    	{
    		x++;
    	}else if(isKeyDown(KEY_LEFT) == 1)
    	{
    		x--;
    	}
    	mysp.x = x;
    	mysp.y = y;
		if(x > SCREEN_WIDTH)
			x=0;
		else if(x < 0)
			x = SCREEN_WIDTH - 1;

		if(y < 0)
			y = SCREEN_HEIGHT - 1;
		else if(y > SCREEN_HEIGHT)
			y = 0;
    	

		waitVBlank();
		shortCopy((u16*)SPRITE_OAM, (u16*)&mysp,4);
		waitVDraw();
    }

    return 0;
}
