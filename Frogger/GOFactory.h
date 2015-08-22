#ifndef GOFACTORY_H
#define GOFACTORY_H

#include <string.h>
#include "toolbox.h"

//typedef enum {Frogger, Turtle, Turtle_Temp, Croc} GOType;
//typedef enum {UP, DOWN, LEFT, RIGHT, NONE} GODirection;

typedef struct 
{
	unsigned char 	y;
	unsigned char 	enableRotation:1;
	unsigned char 	dubScale:1;
	unsigned char 	alpha:2;
	unsigned char 	mosaic:1;
	unsigned char 	colourMode:1;//16 or 256 colour
	unsigned char 	shape:2;//Square or Rect
	unsigned short 	x:9;
	unsigned char 	spcRotation:3;//DEpending on prvious values this will change.
	unsigned char 	horzFlip:1;//IF enabelRotation = 1, Do not set this value
	unsigned char 	vertFlip:1;//IF enabelRotation = 1, Do not set this value
	unsigned char 	size:2;//0, 1, 2 ,3 ,4  0 = 8 pixels, 1 = 16 pixels, 2 = 32 pixels, 3 = 64 pixels depending on the sprite size
	unsigned short 	tileIndex:10;//first tile in tile array.
	unsigned char 	priority:2;
	unsigned char 	pallet:4;
	unsigned short 	rotation;//actual rotation
}SpriteData;

//typedef struct go GameObject;

typedef void (*GO_Update)(int);

typedef struct 
{
	int alive;
	int type;
	SpriteData* sprite;//points to its sprite in shostOAM
	int* index;//Points to its index in indexList
	float z_Depth;
	float speed;
	int enum_dir;
	int counter;
	int timer;
	GO_Update Update;
}GameObject;

typedef struct
{
	int goCount;
	SpriteData ghostOAM[128];
	GameObject GOList[128];
	int indexList[128];
}GOFactory;


extern GOFactory g_GOFactory;

void GOFactory_Init();

void GOFactory_Update();

void GOFactory_ToggleSpritesIsActive(BOOL toggle);

BOOL GOFactory_GetSpritesIsActive();

GameObject* GOFactory_New(int enum_type, int posX, int posY, int enum_dir, int speed);//Default

void GOFactory_Delete(GameObject* gameobject);

void GOFactory_CopytoOAM();

void GOFactory_Sort();

void GOFactory_Swap(int i, int j);

void GOFactory_ShiftGOsDown();

#endif