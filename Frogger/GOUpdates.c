#include "GOUpdates.h"
#include "GOFactory.h"
#include "Input.h"

void GO_Update_Default(int this, float dt)
{

}


void GO_Update_Frogger(int num, float dt)
{
	
	GameObject* this = &g_GOFactory.GOList[num];

	if(isKeyDown(KEY_RIGHT))
		this->sprite->x += 16;
	if(isKeyDown(KEY_LEFT))
		this->sprite->x -= 16;
	if(isKeyDown(KEY_UP))
		this->sprite->y -= 16;
	if(isKeyDown(KEY_DOWN))
		this->sprite->y += 16;


}

void GO_Update_RacingCar(int num, float dt)
{
	GameObject* this = &g_GOFactory.GOList[num];
	this->sprite->x++;
	if(this->sprite->x >= SCREEN_WIDTH + 16)
		this->sprite->x = 0;
}