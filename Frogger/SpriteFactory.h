#ifndef SPRITEFACTORY_H
#define SPRITEFACTORY_H

#include "toolbox.h"


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

SpriteData[128]* Ghost_OAM_Create()
{
	return new SpriteData[128];
}

SpriteData* Ghost_OAM_GetSprite(SpriteData[128]* list, int number)
{

	
}





#endif