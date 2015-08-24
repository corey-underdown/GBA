#include "GOUpdates.h"
#include "GOFactory.h"
#include "Input.h"
#include "CollisionManager.h"

void GO_Update_Default(int num)
{

}

void GO_Update_Frogger(int num)
{
	GameObject* this = &g_GOFactory.GOList[num];

	DetectCollision(this);
	
	if(isKeyDown(KEY_RIGHT))
	{
		if(this->sprite->x <= 208)
			this->sprite->x += 16;
	}
	if(isKeyDown(KEY_LEFT))
	{
		if(this->sprite->x >= 16)
			this->sprite->x -= 16;
	}
		
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
	{
		if(this->sprite->y <= 128)
			this->sprite->y += 16;

	}
}

void GO_Update_RacingCar(int num)
{
	GameObject* this = &g_GOFactory.GOList[num];
	
	if(this->enum_dir == ENUM_DIR_LEFT)
	{
		this->sprite->x += this->speed;
		//if(this->sprite->x >= SCREEN_WIDTH + 16 && this->sprite->x <= SCREEN_WIDTH + 32)
		//	this->sprite->x = 504;
	}
	else
	{
		this->sprite->x -= this->speed;
		if(this->sprite->x == 0) this->sprite->x--;
		//if(this->sprite->x >= 500 && this->sprite->x <= 508)
		//{
		//	this->sprite->x = SCREEN_WIDTH + 8;
		//}
	}
	//GO_Wrap(num);
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
			this->timer /= 3;
		} 
		else
		{
			this->sprite->tileIndex = 32;
			this->type = ENUM_GOTYPE_TURTLE_SAFE;
			this->timer *= 3;
		}

		this->counter = 0;
	}

	GO_Update_RacingCar(num);
}

void GO_Wrap(int num)
{
	GameObject* this = &g_GOFactory.GOList[num];

	unsigned int minWrap = -10;
	unsigned int maxWrap = -10;

	// if (this->enum_dir == ENUM_DIR_LEFT)
	// {
	// 	if (this->sprite->x < (480) &&  this->sprite->x > (400))
	// 	{
	// 		this->sprite->x = this->sprite->x - 180;
	// 	}
	// }
	// 	if (this->enum_dir == ENUM_DIR_RIGHT)
	// {
	// 	if (this->sprite->x > 300 &&  this->sprite->x < (350))
	// 	{
	// 		this->sprite->x = this->sprite->x + 180;
	// 	}
	// }

	if (this->sprite->x < (480) &&  this->sprite->x > (430))
	{
		this->sprite->x = this->sprite->x - 208;
	}
	else if (this->sprite->x > (272) && this->sprite->x < 320)
	{
		this->sprite->x = 208 + this->sprite->x;
	}


}