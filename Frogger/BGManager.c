#include "BGManager.h"
#include "Images/BG_Tiles.h"
#include "Images/BG_Palette.h"
#include "images/Text_Tiles.h"
#include <stdio.h>




BackgroundManager g_BGManager;


void BGManager_SetLayers(BOOL zero, BOOL one, BOOL two, BOOL three)
{
	u16 temp = REG_DISPCNT;

	temp = temp & 0xF0FF;

	temp = temp | (zero << 8) | (one << 9) | (two << 10) | (three << 11);

	REG_DISPCNT = temp;
}

BOOL BGManager_GetLayerEnabled(int layer)
{
	u16 temp = REG_DISPCNT;

	int shift = layer + 8;

	temp = temp & 0x0F00;

	temp = temp & (1 << 8);

	return temp;
}

void BGManager_Init()
{

	//Set Text Tiles
	shortCopy(((u16*)BG_TILE_TEXT), (u16*)TEXT_TILES, (59 * 16));  
	//Set Background Tiles
	shortCopy(((u16*)(BG_TILE_GAME + 32)), (u16*)BG_TILES, (12 * 16)); 
	//set background palette  
	shortCopy((u16*)BG_PAL_DATA, (u16*)BG_PALETTE, 256);



	//Set Up Text Layer
	MapProperties mp0;
	mp0.priority = 0;
	mp0.startAdressTileData = 0;
	mp0.unused = 0;
	mp0.mosaic = 0;
	mp0.paletteType = 0;
	mp0.startAdressTileMap = 12;
	mp0.areaOverflow = 0;
	mp0.sizeMap = 0; 
	
	//Set up Layer 1
	MapProperties mp1;
	mp1.priority = 3;
	mp1.startAdressTileData = 1;
	mp1.unused = 0;
	mp1.mosaic = 0;
	mp1.paletteType = 0;
	mp1.startAdressTileMap = 13;
	mp1.areaOverflow = 0;
	mp1.sizeMap = 0; 

	//Copy Data
	shortCopy((u16*)BG_MAP_PROP_0, (u16*)&mp0, 1);
	shortCopy((u16*)BG_MAP_PROP_1, (u16*)&mp1, 1);


	BGManager_SetRow(0, SQR_Water);
	BGManager_SetRow(1, SQR_Water);
	BGManager_SetRow(2, SQR_Water);
	BGManager_SetRow(3, SQR_Water);
	BGManager_SetRow(4, SQR_Brick);
	BGManager_SetRow(5, SQR_Road);
	BGManager_SetRow(6, SQR_Road);
	BGManager_SetRow(7, SQR_Road);
	BGManager_SetRow(8, SQR_Road);
	BGManager_SetRow(9, SQR_Brick);

	BGManager_ShiftUp(SQR_Brick);
}

void BGManager_SetSquare(int x, int y, Square sqr)
{
	g_BGManager.ghost_VRAM[(x * 2) + (y * 64)] = sqr[0];
	g_BGManager.ghost_VRAM[(x * 2) + (y * 64) + 1] = sqr[1];
	g_BGManager.ghost_VRAM[(x * 2) + (y * 64) + 32] = sqr[2];
	g_BGManager.ghost_VRAM[(x * 2) + (y * 64) + 33] = sqr[3];
}

void BGManager_SetRow (int y, Square sqr)
{
	int i = 0;

	for (i = 0; i < 16; i ++)
	{
		BGManager_SetSquare(i,y,sqr);

	}
}


void BGManager_ShiftUp(Square sqr)
{
	int i = 15;
	for (i = 15; i > 0; i--)
	{
		shortCopy(((u16*)&(g_BGManager.ghost_VRAM[i * 64])), (u16*)&g_BGManager.ghost_VRAM[(i - 1) * 64], (64)); 
	}

	BGManager_SetRow(0, sqr);
}


void BGManager_CopyVRAM()
{
	shortCopy ((u16*)BG_MAP_1, ((u16*)&(g_BGManager.ghost_VRAM[0])), (sizeof(TileData) * 16 * 32));
}