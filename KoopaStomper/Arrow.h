#pragma once
#include "Waypoint.h"
#include "GameObject.h"
#include "Vector2.h"

class Waypoint;

class Arrow : public GameObject
{
public:
	Arrow(const Waypoint& waypoint, std::vector<GameObject*>* mpEntites);
	void Update();

private:
	const Waypoint& mpWaypoint;

	const Vector2f mBig = { 2.69f };
	const Vector2f mSmall = { 1.69f };
	const Vector2f* mCurOri = &mSmall;
	const Vector2f* mCurTarget = &mBig;
	float mElapsed = 0.0f;
	float mDuration = 0.25f;

};