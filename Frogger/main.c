#include <stdio.h>
#include "toolbox.h"

int main()
{
    *(unsigned int*)MEM_IO = 0x0403;

    while(1)
    {
		int i;
	    int j;
	    for(i = 0; i < SCREEN_WIDTH; i++)
	    {
	    	for(j = 0; j < SCREEN_HEIGHT; j++)
	    	{
	    		((unsigned short*)MEM_VRAM)[j+i*SCREEN_HEIGHT] = CLR_WHITE;
	    	}
	    }
    }

    return 0;
}
