#ifndef BACKGROUND_MANAGER_H
#define BACKGROUND_MANAGER_H

#include "toolbox.h"

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


typedef TileData Square[4];

typedef struct
{
	Square brick;
	Square road;
	Square water;
} GameSquares;

typedef struct
{
	MapProperties mapProperties[4];
	TileData ghost_VRAM[32 * 32];//Squares
} BackgroundManager;

typedef struct 
{
	int rowsRemain;
	Square curZone;
}ZONEManager;


extern BackgroundManager g_BGManager;

extern ZONEManager g_ZManager;

extern GameSquares g_gameSquares;

void BGManager_SetLayers(BOOL zero, BOOL one, BOOL two, BOOL three);

void BGManager_SetSquare(int x, int y, Square sqr);

void BGManager_SetRow (int y, Square sqr);

BOOL BGManager_GetLayerEnabled(int layer);

void BGManager_ShiftUp(Square sqr);

void BGManager_Init();

void BGManager_InitMap( int map[32 * 32]);

//void BGManager_SetRow(u16* newRow, int rowNum);

void BGManager_CopyVRAM();


void ZManager_ShiftUp();


#endif

