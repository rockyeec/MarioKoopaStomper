#pragma once

#include "EnemyActor.h"

class LuigiEnemyActor : public EnemyActor
{
public:
	LuigiEnemyActor(std::vector<GameObject*>* mpEntities);

	void SubClassUpdate(const float& deltaTime);
};