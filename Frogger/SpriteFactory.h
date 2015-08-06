#ifndef SPRITEFACTORY_H
#define SPRITEFACTORY_H

#include <string.h>
#include "toolbox.h"


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