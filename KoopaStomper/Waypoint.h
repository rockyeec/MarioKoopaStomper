#pragma once
#include <vector>

#include "Arrow.h"
#include "GameObject.h"

class Arrow;

class Waypoint : public GameObject
{
public:
	Waypoint(std::vector<GameObject*>* mpEntities);

	void Interact();

private:
	std::vector<GameObject*>* mpEntities;
	int mState = 0;
	Vector2i mClips[3];
	Arrow* mpArrow;
};