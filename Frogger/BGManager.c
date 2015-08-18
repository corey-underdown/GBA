#include "BGManager.h"
#include "Images/BGTiles.h"
#include "images/Text_Tiles.h"


BackgroundManager g_BGManager;



void BGManager_Init()
{
	memcpy(((void*)BG_TILE_TEXT), (void*)TEXT_TILES, (59 * 32));  
	memcpy(((void*)BG_TILE_GAME), (void*)BG_Bitmap, (12 * 32)); 

	//set background palette  
	shortCopy((void*)BG_PAL_DATA, (void*)TEXT_BG_PALETTE, 256);



	g_BGManager.ghost_VRAM[0] = ROW_Brick;
	g_BGManager.ghost_VRAM[64] = ROW_Brick;
	g_BGManager.ghost_VRAM[128] = ROW_Brick;
	g_BGManager.ghost_VRAM[256] = ROW_Brick;
	g_BGManager.ghost_VRAM[512] = ROW_Brick;
	g_BGManager.ghost_VRAM[1028] = ROW_Brick;
	g_BGManager.ghost_VRAM[2056] = ROW_Brick;
}

void BGManager_CopyVRAM()
{
	memcpy ((char*)BG_TILE_GAME, ((char*)&(g_BGManager.ghost_VRAM[0])), (sizeof(TileData) * 32 * 32));
}