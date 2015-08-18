#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include "GOFactory.h"
#include "TextManager.h"

int abs(int value);
void DetectCollision(GameObject* frogger);
void ManagerCollision(GameObject* frogger, GameObject* collision);
void DetectCollisionTiles(GameObject* frogger);

#endif