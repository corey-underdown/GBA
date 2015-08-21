#ifndef BACKGROUND_MANAGER_H
#define BACKGROUND_MANAGER_H

#include "toolbox.h"

const unsigned int InitMap[] = {
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

typedef struct 
{
	unsigned short tile:10;
	unsigned char horizontalFlip:1;
	unsigned char verticalFlip:1;
	unsigned char palette:4;
}TileData;

typedef struct 
{
	unsigned char priority:2;
	unsigned char startAdressTileData:2;
	unsigned char unused:2;
	unsigned char mosaic:1;
	unsigned char paletteType:1;
	unsigned char startAdressTileMap:5;
	unsigned char areaOverflow:1;
	unsigned char sizeMap:2;
}MapProperties;


TileData ROW_Brick[] = {

	{1,0,0,0}, {2,0,0,0}, {1,0,0,0}, {2,0,0,0}, {1,0,0,0}, {2,0,0,0}, {1,0,0,0}, {2,0,0,0}, {1,0,0,0}, {2,0,0,0}, {1,0,0,0}, {2,0,0,0}, {1,0,0,0}, {2,0,0,0}, {1,0,0,0}, {2,0,0,0}, {1,0,0,0}, {2,0,0,0}, {1,0,0,0}, {2,0,0,0}, {1,0,0,0}, {2,0,0,0}, {1,0,0,0}, {2,0,0,0}, {1,0,0,0}, {2,0,0,0}, {1,0,0,0}, {2,0,0,0}, {1,0,0,0}, {2,0,0,0}, {1,0,0,0}, {2,0,0,0},
	{3,0,0,0}, {4,0,0,0}, {3,0,0,0}, {4,0,0,0}, {3,0,0,0}, {4,0,0,0}, {3,0,0,0}, {4,0,0,0}, {3,0,0,0}, {4,0,0,0}, {3,0,0,0}, {4,0,0,0}, {3,0,0,0}, {4,0,0,0}, {3,0,0,0}, {4,0,0,0}, {3,0,0,0}, {4,0,0,0}, {3,0,0,0}, {4,0,0,0}, {3,0,0,0}, {4,0,0,0}, {3,0,0,0}, {4,0,0,0}, {3,0,0,0}, {4,0,0,0}, {3,0,0,0}, {4,0,0,0}, {3,0,0,0}, {4,0,0,0}, {3,0,0,0}, {4,0,0,0}

};



typedef struct
{
	MapProperties mapProperties[4];
	TileData ghost_VRAM[32 * 32];//Squares
} BackgroundManager;

extern BackgroundManager g_BGManager;

void BGManager_SetLayers(BOOL zero, BOOL one, BOOL two, BOOL three);

BOOL BGManager_GetLayerEnabled(int layer);

void BGManager_ShiftUp(int zone);

void BGManager_Init();

void BGManager_InitMap( int map[32 * 32]);

void BGManager_SetRow(u16* newRow, int rowNum);

void BGManager_CopyVRAM();


#endif

