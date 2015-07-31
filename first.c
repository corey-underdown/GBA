#include "toolbox.h"

int main()
{
    *(unsigned int*)MEM_IO = 0x0403;

    ((unsigned short*)MEM_VRAM)[120+80*240] = 0x001F;
    ((unsigned short*)MEM_VRAM)[136+80*240] = 0x03E0;
    ((unsigned short*)MEM_VRAM)[120+96*240] = 0x7C00;

    

    while(1);





    return 0;
}
