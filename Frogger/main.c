#include <stdio.h>
#include "toolbox.h"
#include "images/TestImage.h"
#include "SpriteFactory.h"


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

	int i;
	
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

	int x=0;    
	
	while(1)
    {


		mysp.x = x;
		x++;
		if(x>240)
			x=0;
		
		waitVBlank();
		shortCopy((u16*)SPRITE_OAM, (u16*)&mysp,4);
		waitVDraw();
    }

    return 0;
}
