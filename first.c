#include <stdio.h>
#include "toolbox.h"

int a = 0x7FFF;

int main()
{
    *(unsigned int*)MEM_IO = 0x0403;

    while(1)
    {
		setPixel(100, 100, RGB15(31, 0, 0));
    }

    return 0;
}
