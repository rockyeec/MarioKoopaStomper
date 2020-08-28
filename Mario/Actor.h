#pragma once

#include "GameObject.h"
#include "Waypoint.h"

class Actor : public GameObject
{
private:
	class Kinematics
	{
	public:
		Kinematics(const float& jumpHeight, const float& timeToApex);
		void Evaluate(const float& jumpHeight, const float& timeToApex);
		const float& GetJumpVelocity() const;
		const float& GetGravity() const;

	public:
		Vector2f mVelocity = { 0 };

	private:
		float mGravity = 0;
		float mJumpVelocity = 0;
		float mTimeToApex = 0;
		float mJumpHeight = 0;
	};

	struct JumpAttributes
	{
		bool mIsOnGround = false;
		bool mIsJump = false;
		bool mOldIsJumpButtonPress = false;
		bool mJumpButton = false;
	};

	enum class HitDirection
	{
		TOP = 0,
		BOTTOM = 1,
		LEFT = 3,
		RIGHT = 4
	};
public:
	Actor(const Layer& layer, std::vector<GameObject*>* entityList);
	~Actor();
	void Start();
	void EarlyUpdate();
	void FixedUpdate();
	void Update();	

private:
	void HandleMovement(const float& deltaTime);
	void HandleFacing(const float& input);
	void HandleGravity(const float& deltaTime);
	void HandleGameBoundaries();
	void HandleCollisions();
	void PerformMovement();

protected:
	virtual void Jump();
	virtual void Land();
	virtual void Fall();
	virtual void Stomp();
	virtual void Die();
	virtual void HeadButt();
	virtual void Spin(const float& deltaTime);

private:
	const bool CheckGround() const;
	const bool CheckCeiling() const;
	const bool CheckLeft() const;
	const bool CheckRight() const;

protected:
	void HandleJump();
	void SetHorizontal(const bool& left, const bool& right);
	void SetVertical(const bool& up, const bool& down);
	void ClearHorizontal();
	void ClearVertical();

protected:
	virtual void SubClassUpdate(const float& deltaTime) = 0;
	virtual void SubClassFixedUPdate(const float& deltaTime) = 0;
	virtual const bool IsStomp() const = 0;
	virtual const bool IsHeadButt() const;
	virtual void HandleAnimations(const float& deltaTime);

protected:
	JumpAttributes mJump;
	Kinematics mKinematics;
	float mMoveSpeed = 169.69f;
	bool mIsDead = false;
	bool mCanInput = true;
	float mHorizontalInput = 0;
	float mVerticalInput = 0;
	bool mIsOutOfMap = false;
	bool mIsNextLevel = false;
};