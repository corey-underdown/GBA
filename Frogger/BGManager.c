#include "BGManager.h"
#include "GOFactory.h"
#include "Images/BG_Tiles.h"
#include "Images/BG_Palette.h"
#include "images/Text_Tiles.h"
#include <stdio.h>


BackgroundManager g_BGManager;

ZONEManager g_ZManager;

GameSquares g_gameSquares;

int turtleArray[] = {0,16,64,96,128,192,208,224,304,320,368,384,432,464};
int logArray[] = {0,48,128,224,320,384,464};
int raceCarArray[] = {0,256};
int carArray[] = {0,256};
int truckArray[] = {0,256};

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

	// ZManager_ShiftUp();
	// ZManager_ShiftUp();
	// ZManager_ShiftUp();
	// ZManager_ShiftUp();
	// ZManager_ShiftUp();
	// ZManager_ShiftUp();
	// ZManager_ShiftUp();
	// ZManager_ShiftUp();
	// ZManager_ShiftUp();
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

	ZManager_CreateGOLine(1,0);
	ZManager_CreateGOLine(1,16);
	ZManager_CreateGOLine(1,32);
	ZManager_CreateGOLine(1,48);

	ZManager_CreateGOLine(0,80);
	ZManager_CreateGOLine(0,96);
	ZManager_CreateGOLine(0,112);
	ZManager_CreateGOLine(0,128);


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




//race = 3, turtle/log = 1
void ZManager_CreateGOLine(int gameZone, int y)
{
	int direction = ((g_BGManager.lineCreated % 2) + 2);//will be either 2 or 3. ENUM_DIR_LEFT or ENUM_DIR_RIGHT
	int randOffset = RandomRange(0, 256);
	if (gameZone == 0)//Road
	{
		int randObject = RandomRange(0,3);
		if (randObject == 0)//Spawn Race Car
		{
			int i = 0;
			for (i = 0; i < 2; i ++)
			{
				GOFactory_New(ENUM_GOTYPE_CAR_RACE, randOffset + raceCarArray[i], y, direction, 3);
			}
		}
		if (randObject == 1)//Spawn Car
		{
			int i = 0;
			for (i = 0; i < 2; i ++)
			{
				GOFactory_New(ENUM_GOTYPE_CAR, randOffset + carArray[i], y, direction, 2);
			}
		}
		if (randObject == 2)//Spawn truck
		{
			int i = 0;
			for (i = 0; i < 2; i ++)
			{
				GOFactory_New(ENUM_GOTYPE_TRUCK_CABIN, randOffset + carArray[i], y, direction, 1);
				if (direction = ENUM_DIR_RIGHT)
				{
					GOFactory_New(ENUM_GOTYPE_TRUCK_TRAILER, randOffset + carArray[i] + 16, y, direction, 1);
				}
				else
				{
					GOFactory_New(ENUM_GOTYPE_TRUCK_TRAILER, randOffset + truckArray[i] -32, y, direction, 1);
				}
			}
		}

	}
	else if (gameZone == 1)//water
	{
		int randObject = RandomRange(0,2);
		if (randObject == 0)//Spawn Turtles
		{
			int i = 0;
			for (i = 0; i < 14; i ++)
			{
				GOFactory_New(ENUM_GOTYPE_TURTLE_SAFE, randOffset + turtleArray[i], y, direction, 1);
			}
		}
		else if (randObject == 1)//Spawn Logs
		{
			int i = 0;
			for (i = 0; i < 7; i ++)
			{
				GOFactory_New(ENUM_GOTYPE_LOG_MED, randOffset + logArray[i], y, direction, 1);
			}
		}

	}

	g_BGManager.lineCreated ++;
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
 			g_ZManager.enumCurZone = ENUM_ZONE_ROAD;
 		}
 		else if (randZone == 1)
 		{
 			shortCopy(((u16*)(g_ZManager.curZone)), (u16*)g_gameSquares.water, (4)); 
 			g_ZManager.enumCurZone = ENUM_ZONE_WATER;
 		}

 		BGManager_ShiftUp(g_gameSquares.brick);
 	}
 	else
 	{
 		BGManager_ShiftUp(g_ZManager.curZone);
 		ZManager_CreateGOLine(g_ZManager.enumCurZone, -16);
		g_ZManager.rowsRemain --;
 	}

 }

 int BGManager_GetTile(int x, int y)
 { 	
 	int convertX = ((x - (x % 16)) / 8);
 	int convertY = ((y - (y % 16)) / 8);
 	return g_BGManager.ghost_VRAM[convertX + (convertY * 32)].tile;
 }