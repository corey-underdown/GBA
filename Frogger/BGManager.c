#include "BGManager.h"
#include "Images/BGTiles.h"
#include "images/Text_Tiles.h"
#include <stdio.h>
#include "toolbox.h"


BackgroundManager g_BGManager;




void BGManager_Init()
{
	shortCopy(((u16*)BG_TILE_TEXT), (u16*)TEXT_TILES, (59 * 32));  
	shortCopy(((u16*)BG_TILE_GAME), (u16*)BG_Bitmap, (12 * 32)); 
	//memcpy ((char*)BG_TILE_TEXT, ((char*)&(TEXT_TILES), (59 * 32));
	//memcpy ((char*)BG_TILE_GAME, ((char*)&(BG_Bitmap), (12 * 32));

	//set background palette  
	shortCopy((u16*)BG_PAL_DATA, (u16*)TEXT_BG_PALETTE, 256);



	BGManager_SetRow((u16*)ROW_Brick, 0);
}

void BGManager_SetRow(u16* newRow, int rowNum)
{
	//u16* bgspot = 
	shortCopy(((u16*)&(g_BGManager.ghost_VRAM[100])), newRow, (64)); 
}

void BGManager_CopyVRAM()
{
	shortCopy ((u16*)BG_TILE_GAME, ((u16*)&(g_BGManager.ghost_VRAM[0])), (sizeof(TileData) * 32 * 32));
}