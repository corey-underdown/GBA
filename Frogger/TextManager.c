#include <string.h>
#include "TextManager.h"
#include "toolbox.h"

unsigned int row = 0;
char characterArray[256] = {
/*0*/	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
/*16*/	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
/*32*/	0,	1,	2,	3,	4,	5,	6,	7,	8,	9,	10,	11,	12,	13,	14,	15,
/*48*/	16,	17,	18,	19,	20,	21,	22,	23,	24,	25,	26,	27,	28,	29,	30,	31, 
/*64*/	32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 
/*80*/	48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 
/*96*/	0,  33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 
/*0*/	48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 0,  0,  0,  0,  0,  
/*0*/	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0, 
/*0*/	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0, 
/*0*/	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0, 
/*0*/	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0, 
/*0*/	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0, 
/*0*/	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
/*0*/	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
/*0*/	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0
};
int characterLineIndex = 0;
char* characterLines[20];

void PrintText(const char* s)
{
	characterLines[characterLineIndex] = s;
	characterLineIndex++;
	if(characterLineIndex >= SCREEN_HEIGHT_TILES)
		ShiftTextUp();
	//char* character = &s[0];
	//int len = strlen(character);
	RedrawLine(s);
}

void RedrawLine(const char* s)
{
	char* i;
	int tempCounter;
	for(i = s; *i; i++)
	{
		((volatile u16*)BG_MAP_0)[(row * SCREEN_WIDTH_TILES) + tempCounter]=characterArray[(int)*i];
		tempCounter++; 
	}
	while(tempCounter < SCREEN_WIDTH_TILES)
	{
		((volatile u16*)BG_MAP_0)[(row * SCREEN_WIDTH_TILES) + tempCounter]=0;
		tempCounter++;
	}
	row++;
}

void ShiftTextUp()
{
	characterLineIndex = SCREEN_HEIGHT_TILES - 1;
	int textArrayIndex;
	row = 0;
	for(textArrayIndex = 0; textArrayIndex < SCREEN_HEIGHT_TILES - 1; textArrayIndex++)
	{
		characterLines[textArrayIndex] = characterLines[textArrayIndex + 1];
		RedrawLine(characterLines[textArrayIndex]);
	}
}