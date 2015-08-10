#ifndef INPUT_H
#define INPUT_H

extern unsigned short currentKey = 0, previousKey = 0;

#define KEY_A 		1
#define KEY_B 		2
#define KEY_SELECT 	4
#define KEY_START 	8
#define KEY_RIGHT 	16
#define KEY_LEFT 	32
#define KEY_UP 		64
#define KEY_DOWN 	128
#define KEY_R 		256
#define KEY_L 		512
#define KEY_MASK 	0x03FF
int* KEYS = (int*)	0x04000130;

void PollKeys()
{
	previousKey = currentKey;
	currentKey = ~*KEYS & KEY_MASK;
}

unsigned int CurrentKeyState() { return currentKey; }
unsigned int PreviousKeyState() { return previousKey; }
unsigned int IsKeyDown(unsigned int key) { return currentKey & key; }
unsigned int IsKeyUp(unsigned int key) { return ~currentKey & key; }
unsigned int WasKeyDown(unsigned int key) { return previousKey & key; }
unsigned int WasKeyUp(unsigned int key) { return ~previousKey & key; }

/*char isKeyDown(unsigned short key)
{
	if(!((*KEYS) & key))
    	return 1;

    return 0;
}*/

#endif