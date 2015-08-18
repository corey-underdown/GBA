//#include "input.h" 

/*unsigned short currentKey = 0, previousKey = 0;

typedef struct
{
	unsigned short Last;
	unsigned short Current;
}KeyInput;

KeyInput Keys;

unsigned char delay		= 60;
unsigned char repeat 	= 30;
unsigned char count		= 60;*/

/*void PollKeys()
{
	Keys.Last = Keys.Held;
	Keys.Held = (0x04000130 & 0x03FF) ^ 0x03FF;

	unsigned short pressed = Keys.Held & (Keys.Last ^ 0x03FF);

	Keys.DownRepeat	|=	pressed;
	Keys.Down |= pressed;

	unsigned short released = ((Keys.Held ^ 0x03FF) & Keys.Last);

	Keys.Up		|=	released;

	Keys.Down	&= ~released;
	Keys.DownRepeat	&= ~released;

	Keys.Up &= ~pressed;

	if ( Keys.Last != Keys.Held) count = delay;


	if ( delay != 0)
	{
		count--;
		if (count == 0)
		{
			count = repeat;
			Keys.DownRepeat |= Keys.Held;
		}
	}
} */

/*void PollKeys()
{
	Keys.Last = Keys.Current;
	Keys.Current = ~(KEYS_LOC & KEY_MASK);
}*/

/*unsigned short isKeyDown(unsigned short key)
{
	return (!((*KEYS) & key));
} */