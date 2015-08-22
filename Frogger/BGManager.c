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
	mp1.priority = 0;
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





	BGManager_SetRow((u16*)ROW_Brick, 0);
	BGManager_SetRow((u16*)ROW_Brick, 1);
	BGManager_SetRow((u16*)ROW_Brick, 2);
	BGManager_SetRow((u16*)ROW_Brick, 3);

	//((volatile u16*)BG_MAP_0)[500]=1;
	//((volatile u16*)BG_MAP_0)[501]=1;
	//((volatile u16*)BG_MAP_1)[200]=12;
	//((volatile u16*)BG_MAP_1)[201]=12;
}

void BGManager_SetRow(u16* newRow, int rowNum)
{
	//u16* bgspot = 
	shortCopy(((u16*)&(g_BGManager.ghost_VRAM[rowNum * 64])), newRow, (64)); 

	TileData ff = {1,0,0,0};
	TileData gg = {2,0,0,0};
	TileData hh = {3,0,0,0};
	TileData jj = {4,0,0,0};

	int start = 0 * 64;

	//g_BGManager.ghost_VRAM[start] = ff;
	//g_BGManager.ghost_VRAM[start + 1] = gg;
	//g_BGManager.ghost_VRAM[start + 32] = hh;
	//g_BGManager.ghost_VRAM[start + 33] = jj;
}

void BGManager_CopyVRAM()
{
	shortCopy ((u16*)BG_MAP_1, ((u16*)&(g_BGManager.ghost_VRAM[0])), (sizeof(TileData) * 16 * 32));
}