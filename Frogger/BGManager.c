#include "BGManager.h"
#include "Images/BGTiles.h"
#include "images/Text_Tiles.h"
#include <stdio.h>
#include "toolbox.h"


BackgroundManager g_BGManager;




void BGManager_Init()
{
	shortCopy(((u16*)BG_TILE_TEXT), (u16*)TEXT_TILES, (59 * 16));  
	//shortCopy(((u16*)BG_TILE_TEXT), (u16*)BG_Bitmap, (12 * 32));  
	shortCopy(((u16*)(BG_TILE_GAME + 32)), (u16*)BG_Bitmap, (12 * 16)); 
	//memcpy ((char*)BG_TILE_TEXT, ((char*)&(TEXT_TILES), (59 * 32));
	//memcpy ((char*)BG_TILE_GAME, ((char*)&(BG_Bitmap), (12 * 32));

	//set background palette  
	shortCopy((u16*)BG_PAL_DATA, (u16*)TEXT_BG_PALETTE, 256);




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