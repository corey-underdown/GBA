#include "GOUpdates.h"
#include "GOFactory.h"
#include "Input.h"

void GO_Update_Default(int this)
{

}


void GO_Update_Frogger(int num)
{
	
	GameObject* this = &g_GOFactory.GOList[num];

	
		if(isKeyDown(KEY_RIGHT))
			this->sprite->x += 16;
		if(isKeyDown(KEY_LEFT))
			this->sprite->x -= 16;
		if(isKeyDown(KEY_UP))
		{
			if(this->sprite->y > 80)
				this->sprite->y -= 16;
			else
				GOFactory_ShiftGOsDown();
		}	
		if(isKeyDown(KEY_DOWN))
			this->sprite->y += 16;
}

void GO_Update_RacingCar(int num)
{
	GameObject* this = &g_GOFactory.GOList[num];
	
	if(this->enum_dir == ENUM_DIR_LEFT)
	{
		this->sprite->x += this->speed;
		if(this->sprite->x >= SCREEN_WIDTH + 16 && this->sprite->x <= SCREEN_WIDTH + 32)
			this->sprite->x = 504;
	}
	else
	{
		this->sprite->x -= this->speed;
		if(this->sprite->x == 0) this->sprite->x--;
		PrintTextInt(this->sprite->x);
		if(this->sprite->x >= 500 && this->sprite->x <= 508)
		{
			this->sprite->x = SCREEN_WIDTH + 8;
		}
	}
}