#ifndef SPRITEFACTORY_H
#define SPRITEFACTORY_H

#include <string.h>
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



typedef struct
{
	SpriteData ghostOAM[128];
}SpriteFactory;


SpriteFactory* Ghost_OAM_Create()
{
	SpriteFactory* temp;
	return temp;
}

SpriteData* Ghost_OAM_GetSprite_int(SpriteFactory* factory, int number)//0 -> 127
{
	return &factory->ghostOAM[number];
}

void Ghost_OAM_SetSprite_int(SpriteFactory* factory, int number, SpriteData* spriteD)
{
	factory->ghostOAM[number] = *spriteD;
}

void Ghost_OAM_CopytoOAM(SpriteFactory* factory)
{
	//memcpy ((char*)SPRITE_OAM, ((char*)factory->ghostOAM[0]), (sizeof(SpriteData) * 128));


	shortCopy((u16*)SPRITE_OAM, (u16*)&(factory->ghostOAM[0]),4);
}






#endif