#include "input.h" 

unsigned short currentKey = 0, previousKey = 0;

KeyInput g_Keys;

void PollKeys()
{
	g_Keys.Last = g_Keys.Current;
	g_Keys.Current = ~(*KEYS & KEY_MASK);
}

unsigned short isKeyPressed(unsigned short key)
{
	return (((g_Keys.Current) & key));
} 

unsigned short isKeyDown(unsigned short key)
{
	unsigned short tempCur = ((g_Keys.Current) & key);
	unsigned short tempLast = ((g_Keys.Last) & key);
	if (tempCur != 0 && tempLast == 0)
		return 1;
	else
		return 0;
} 

unsigned short isKeyUp(unsigned short key)
{
	unsigned short tempCur = ((g_Keys.Current) & key);
	unsigned short tempLast = ((g_Keys.Last) & key);
	if (tempCur == 0 && tempLast != 0)
		return 1;
	else
		return 0;
} 


