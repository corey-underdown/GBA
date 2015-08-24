#include "GOUpdates.h"
#include "GOFactory.h"
#include "Input.h"
#include "CollisionManager.h"

void GO_Update_Default(int this)
{

}

void GO_Update_Frogger(int num)
{
	GameObject* this = &g_GOFactory.GOList[num];

	DetectCollision(this);
	
	if(isKeyDown(KEY_RIGHT))
		this->sprite->x += 16;
	if(isKeyDown(KEY_LEFT))
		this->sprite->x -= 16;
	if(isKeyDown(KEY_UP))
	{
		if(this->sprite->y > 80)
			this->sprite->y -= 16;
		else
		{
			ZManager_ShiftUp();
			GOFactory_ShiftGOsDown();
		}
	}	
	if(isKeyDown(KEY_DOWN))
		this->sprite->y += 16;

 	PrintTextInt(BGManager_GetTile(this->sprite->x, this->sprite->y));
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
		if(this->sprite->x >= 500 && this->sprite->x <= 508)
		{
			this->sprite->x = SCREEN_WIDTH + 8;
		}
	}
}

void GO_Update_Turtle(int num)
{
	GameObject* this = &g_GOFactory.GOList[num];

	this->counter ++;
	if(this->counter >= this->timer)
	{
		if(this->type == ENUM_GOTYPE_TURTLE_SAFE)
		{
			this->sprite->tileIndex = 36;
			this->type = ENUM_GOTYPE_TURTLE_TEMP;
		} 
		else
		{
			this->sprite->tileIndex = 32;
			this->type = ENUM_GOTYPE_TURTLE_SAFE;
		}

		this->counter = 0;
	}

	GO_Update_RacingCar(num);
}