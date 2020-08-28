#pragma once
#include "EnemyActor.h"

class KoopaEnemyActor : public EnemyActor
{
public:
	KoopaEnemyActor(std::vector<GameObject*>* mpEntities);

protected:
	void Die();
};