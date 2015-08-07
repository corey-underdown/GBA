#include "SpriteFactory.h"

SpriteFactory g_SpriteFactory;


SpriteFactory* Ghost_OAM_Create()
{
	SpriteFactory* temp;
	return temp;
}

SpriteData* Ghost_OAM_GetSprite_int( int number)//0 -> 127
{
	return &g_SpriteFactory.ghostOAM[number];
}

void Ghost_OAM_SetSprite_int(int number, SpriteData* spriteD)
{
	g_SpriteFactory.ghostOAM[number] = *spriteD;
}

void Ghost_OAM_CopytoOAM()
{
	memcpy ((char*)SPRITE_OAM, ((char*)&(g_SpriteFactory.ghostOAM[0])), (sizeof(SpriteData) * 128));
	//shortCopy((u16*)SPRITE_OAM, (u16*)&(factory->ghostOAM[0]),4);
}