#include "BGManager.h"
#include "GOFactory.h"
#include "Images/BG_Tiles.h"
#include "Images/BG_Palette.h"
#include "images/Text_Tiles.h"
#include <stdio.h>


BackgroundManager g_BGManager;

ZONEManager g_ZManager;

GameSquares g_gameSquares;

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



	Square SQR_Brick = {
		{1,0,0,0}, {2,0,0,0},
		{3,0,0,0}, {4,0,0,0}
	};

	Square SQR_Road = {
		{5,0,0,0}, {6,0,0,0},
		{7,0,0,0}, {8,0,0,0}
	};

	Square SQR_Water = {
		{9,0,0,0}, {10,0,0,0},
		{11,0,0,0}, {12,0,0,0}
	};
	shortCopy(((u16*)(g_gameSquares.brick)), (u16*)SQR_Brick, (4)); 
	shortCopy(((u16*)(g_gameSquares.road)), (u16*)SQR_Road, (4)); 
	shortCopy(((u16*)(g_gameSquares.water)), (u16*)SQR_Water, (4)); 

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


	BGManager_SetRow(0, g_gameSquares.water);
	BGManager_SetRow(1, g_gameSquares.water);
	BGManager_SetRow(2, g_gameSquares.water);
	BGManager_SetRow(3, g_gameSquares.water);
	BGManager_SetRow(4, g_gameSquares.brick);
	BGManager_SetRow(5, g_gameSquares.road);
	BGManager_SetRow(6, g_gameSquares.road);
	BGManager_SetRow(7, g_gameSquares.road);
	BGManager_SetRow(8, g_gameSquares.road);
	BGManager_SetRow(9, g_gameSquares.brick);

	//BGManager_ShiftUp(SQR_Brick);
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

void ZManager_ShiftUp()
 {
 	if (g_ZManager.rowsRemain <= 0)
 	{
 		g_ZManager.rowsRemain = RandomRange(3,7);

 		int randZone = RandomRange(0,2);

 		if (randZone == 0)
 		{
 			shortCopy(((u16*)(g_ZManager.curZone)), (u16*)g_gameSquares.road, (4)); 
 			int i;
 			for(i = 0; i < g_ZManager.rowsRemain; i++)
 			{
 				GOFactory_New(ENUM_GOTYPE_CAR_RACE, RandomRange(10, SCREEN_WIDTH), -32 - (16 * i + 1), ENUM_DIR_RIGHT, 20);
 			}
 		}
 		else if (randZone == 1)
 		{
 			shortCopy(((u16*)(g_ZManager.curZone)), (u16*)g_gameSquares.water, (4)); 
 			int i;
 			for(i = 0; i < g_ZManager.rowsRemain; i++)
 			{
 				int randGO = RandomRange(0, 3);
 				if(randGO == 0)
 					GOFactory_New(ENUM_GOTYPE_TURTLE_SAFE, RandomRange(10, SCREEN_WIDTH), -31 - (16 * i + 1), ENUM_DIR_RIGHT, 20);
 				else if(randGO == 1)
 					GOFactory_New(ENUM_GOTYPE_LOG_MED, RandomRange(10, SCREEN_WIDTH), -31 - (16 * i + 1), ENUM_DIR_RIGHT, 20);
 			}
 		}

 		BGManager_ShiftUp(g_gameSquares.brick);
 	}
 	else
 	{
 		BGManager_ShiftUp(g_ZManager.curZone);
		g_ZManager.rowsRemain --;
 	}

 }

 int BGManager_GetTile(int x, int y)
 { 	
 	int convertX = (x/8) - ((x/8) % 2);
 	int convertY = (y/8) - ((y/8) % 2);
 	return g_BGManager.ghost_VRAM[convertX + (convertY * 32)].tile;
 }