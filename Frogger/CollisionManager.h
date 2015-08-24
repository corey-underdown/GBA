#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include "GOFactory.h"
#include "TextManager.h"
#include "BGManager.h"
#include "toolbox.h"

typedef struct
{
	int x;
	int y;
}Bounds;

int abs(int value);
void DetectCollision(GameObject* frogger);
void ManagerCollision(GameObject* frogger, GameObject* collision);
void DetectCollisionTiles(GameObject* frogger);
Bounds DetermineBounding(int shape, int size);
void CompleteDeath();

#endif