#pragma once
#include "Actor.h"
#include "Animation.h"

class PlayerActor : public Actor
{
private:
	struct MarioAnimations
	{
		Animation idle;
		Animation run;
		Animation jump;
		Animation* curAnimation = &idle;
	};

public:
	PlayerActor(std::vector<GameObject*>* entityList);
	~PlayerActor();
	void Start();
	void EarlyUpdate();
	void LateUpdate();
	void RemoveFromGame();

protected:
	void Jump();
	void Fall();
	void HeadButt();

protected:
	void Interact();
	void SubClassUpdate(const float& deltaTime);
	void SubClassFixedUPdate(const float& deltaTime);
	const bool IsStomp() const;
	const bool IsHeadButt() const;
	const bool IsWaypoint() const;

private:
	void HandleMovementInput(const float& deltaTime);
	void MakeCameraFollow(const float& deltaTime) const;
	void InitializeAnimations();
	void HandleAnimations(const float& deltaTime);
	const bool IsFalling() const;

private:
	MarioAnimations mAnimations;
	bool mIsHeadButt = false;
};