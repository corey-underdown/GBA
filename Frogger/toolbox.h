// toolbox.h: 
//
// === NOTES ===
// * This is a _small_ set of typedefs, #defines and inlines that can 
//   be found in tonclib, and might not represent the 
//   final forms.


#ifndef TOOLBOX_H
#define TOOLBOX_H
#include <stdlib.h>



// === (from tonc_types.h) ============================================

typedef unsigned char   u8;
typedef unsigned short  u16;
typedef unsigned int    u32;


typedef u16 COLOR;

#define SPRITE_OAM 			0x07000000//Sprite object Data
#define SPRITE_BITMAPS	 	0x06010000//Sprite Tiles ie actual sprites
#define SPRITE_PAL_DATA 	0x05000200
#define BG_PAL_DATA			0x05000000
#define BG_TILE_TEXT		0x06000000
#define BG_TILE_GAME		0x06004000
#define BG_MAP_0			0x06006000
#define BG_MAP_1			0x06006800
#define BG_MAP_2			0x06007000
#define BG_MAP_3			0x06007800

#define BG_MAP_PROP_0 		0x04000008
#define BG_MAP_PROP_1 		0x0400000A
#define BG_MAP_PROP_2 		0x0400000C
#define BG_MAP_PROP_3 		0x0400000E

//=======Game object type Enum

#define ENUM_GOTYPE_FROGGER			0
#define ENUM_GOTYPE_TURTLE_SAFE		1
#define ENUM_GOTYPE_TURTLE_TEMP		2
#define ENUM_GOTYPE_LOG_SMALL		3
#define ENUM_GOTYPE_LOG_MED			4
#define ENUM_GOTYPE_LOG_LARGE		5
#define ENUM_GOTYPE_CROC			6
#define ENUM_GOTYPE_CAR_RACE		7
#define ENUM_GOTYPE_CAR 			8
#define ENUM_GOTYPE_TRUCK_TRAILER	9
#define ENUM_GOTYPE_TRUCK_CABIN 	10

#define ENUM_DIR_UP		0
#define ENUM_DIR_DOWN	1
#define ENUM_DIR_LEFT	2
#define ENUM_DIR_RIGHT	3
#define ENUM_DIR_NONE	4

#define ENUM_TILE_BRICK  1
#define ENUM_TILE_ROAD  5
#define ENUM_TILE_WATER  9


#define ENUM_ZONE_ROAD  0
#define ENUM_ZONE_WATER  1


#define BOOL 	u16
#define TRUE 	1
#define FALSE 	0

//#define BG_SCROLL			(void*)0x04000010h


//========================================================================

#define INTERUPT_MODE     *((volatile u16*)(MEM_IO+0x0004))

#define VCOUNT 				0x04000006

#define INLINE static inline

// === (from tonc_memmap.h) ===========================================

#define MEM_IO      0x04000000
#define MEM_VRAM    0x06000000

#define REG_DISPCNT     *((volatile u32*)(MEM_IO+0x0000))

// === (from tonc_memdef.h) ===========================================

// --- REG_DISPCNT defines ---
#define DCNT_MODE0     0x0000
#define DCNT_MODE1      0x0001
#define DCNT_MODE2      0x0002
#define DCNT_MODE3      0x0003
#define DCNT_MODE4      0x0004
#define DCNT_MODE5      0x0005
// layers
#define DCNT_BG0        0x0100
#define DCNT_BG1        0x0200
#define DCNT_BG2        0x0400
#define DCNT_BG3        0x0800
#define DCNT_OBJ        0x1000


// === (from tonc_video.h) ============================================

#define SCREEN_WIDTH   		240
#define SCREEN_HEIGHT  		160
#define SCREEN_WIDTH_TILES	32
#define SCREEN_HEIGHT_TILES	20

#define vid_mem     ((u16*)MEM_VRAM)

INLINE void m3_plot(int x, int y, COLOR clr)
{   vid_mem[y*SCREEN_WIDTH+x]= clr;    }

#define CLR_BLACK   0x0000
#define CLR_RED     0x001F
#define CLR_LIME    0x03E0
#define CLR_YELLOW  0x03FF
#define CLR_BLUE    0x7C00
#define CLR_MAG     0x7C1F
#define CLR_CYAN    0x7FE0
#define CLR_WHITE   0x7FFF


INLINE COLOR RGB15(u32 red, u32 green, u32 blue)
{   return red | (green<<5) | (blue<<10);   }


//=======(Functions)==================================================

INLINE void waitVBlank()
{
	while(*(( volatile u16*)(VCOUNT)) <= 159)
	{}
}

INLINE void waitVDraw()
{
	while(*(( volatile u16*)(VCOUNT)) > 159)
	{}
}

INLINE void shortCopy(volatile u16 *dest, u16 *src, int shortCount)
{
	int i;
	for(i=0;i<shortCount;++i)
	{
		*dest++ = *src++;
	}
}

INLINE int RandomRange(int min, int max)
{
	return  min + (rand() % (max - min));
}

#endif // TOOLBOX_H