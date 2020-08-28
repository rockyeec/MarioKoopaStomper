#pragma once
#include "Actor.h"

class EnemyActor : public Actor
{
public:
	EnemyActor(std::vector<GameObject*>* entityList);

protected:
	void Interact();
	void SubClassUpdate(const float& deltaTime);
	void SubClassFixedUPdate(const float& deltaTime);
	const bool IsStomp() const;

protected:
	float mOsciTimer = 0;
	float mOsciDuration = 1.69f;
	bool mIsOsci = false;
};