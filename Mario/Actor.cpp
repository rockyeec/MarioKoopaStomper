#include "Actor.h"
#include "Time.h"
#include "Mathf.h"
#include "Collisions.h"
#include "AudioManager.h"
#include "Camera.h"
#include "Level.h"

Actor::Actor(const Layer& layer, std::vector<GameObject*>* entityList)
	:
	GameObject(entityList),
	mKinematics(4.69f, 0.45f)
{
	mBox.mLayer = layer;
}

Actor::~Actor()
{
}

void Actor::Start()
{
	GameObject::Start();
}

void Actor::EarlyUpdate()
{
	GameObject::EarlyUpdate();
}

void Actor::FixedUpdate()
{
	if (mIsOutsideScreen)
		return;

	const float& deltaTime = Time::GetFixedDeltaTime();

	SubClassFixedUPdate(deltaTime);

	HandleJump();

	HandleMovement(deltaTime);

	HandleGravity(deltaTime);

	PerformMovement();	
}

void Actor::Update()
{
	if (mIsOutsideScreen)
		return;
    const float deltaTime = Time::GetDeltaTime();	

	if (mCanInput)
	{
		SubClassUpdate(deltaTime);
	}
	else if (mIsDead)
	{
		Spin(deltaTime);
	}
	HandleAnimations(deltaTime);

	if (mIsOutOfMap)
	{
		RemoveFromGame();
		return;
	}	
}


void Actor::SetHorizontal(const bool& left, const bool& right)
{
	const float& targetValue = float(right - left);
	const float slipperiness = 2.69f * Time::GetDeltaTime();
	mHorizontalInput = Mathf::MoveTowards(mHorizontalInput, targetValue, slipperiness);
	HandleFacing(targetValue);
}

void Actor::SetVertical(const bool& up, const bool& down)
{
	const float& targetValue = float(down - up);
	const float slipperiness = 2.69f * Time::GetDeltaTime();
	mVerticalInput = Mathf::MoveTowards(mVerticalInput, targetValue, slipperiness);
}

const bool Actor::IsHeadButt() const
{
	return false;
}

void Actor::HandleAnimations(const float& deltaTime)
{
}

void Actor::HandleJump()
{
	if (!mJump.mJumpButton)
	{
		const bool& onButtonRelease = mJump.mIsJump && mJump.mOldIsJumpButtonPress;
		if (onButtonRelease)
		{
			const bool& isNotFalling = mKinematics.mVelocity.y < 0;
			if (isNotFalling)
			{
				mKinematics.mVelocity.y *= 0.5f;
			}
		}
		mJump.mOldIsJumpButtonPress = false;
		return;
	}

	if (!mJump.mIsJump && !mJump.mOldIsJumpButtonPress)
	{
		Jump();
	}
	mJump.mOldIsJumpButtonPress = true;
}

void Actor::HandleMovement(const float& deltaTime)
{
	mKinematics.mVelocity.x = mHorizontalInput * deltaTime * mMoveSpeed;
	mKinematics.mVelocity.y += mVerticalInput * deltaTime * mMoveSpeed;
}

void Actor::HandleFacing(const float& input)
{
	if (input < 0.0f)
	{
		GetTexture().SetFlip(SDL_FLIP_HORIZONTAL);
	}
	else if (input > 0.0f)
	{
		GetTexture().SetFlip(SDL_FLIP_NONE);
	}
}

void Actor::HandleGravity(const float& deltaTime)
{
	if (!mJump.mIsOnGround)
	{
		mKinematics.mVelocity.y += (mKinematics.GetGravity() * deltaTime);
	}
}

void Actor::HandleGameBoundaries()
{
	const Vector2f intendedPosition = mpTransform->GetPosition() + mKinematics.mVelocity;
	const Vector2f& size = GetTexture().GetSizeFloat();
	const float newX = Mathf::Clamp<float>(0, GAME_WIDTH - size.x, intendedPosition.x);
	const float newY = Mathf::Clamp<float>(0, GAME_HEIGHT - size.y, intendedPosition.y);
	if (newX != intendedPosition.x)
	{
		//std::cout << "x out map\n";
		mKinematics.mVelocity.x = 0;
		mHorizontalInput = 0;
	}
	if (newY != intendedPosition.y)
	{
		//std::cout << "y out map\n";
		mKinematics.mVelocity.y = 0;
		mVerticalInput = 0;

		if (!mCanInput)
		{
			mIsOutOfMap = true;
		}
	}
}

void Actor::HandleCollisions()
{
	const BoxCollider oldBox = mBox;
	mBox.SetPosition(mpTransform->GetPosition() + mKinematics.mVelocity);
	Collisions::OccupyCell(mBox, oldBox);
	if (Collisions::IsCollide(mBox))
	{
		//std::cout << "collide\n";
		if (CheckGround())
		{
			if (IsStomp())
			{
				Stomp();
			}
			else
			{
				Land();
			}
		}
		if (CheckCeiling())
		{
			if (IsHeadButt())
			{
				HeadButt();
			}

			ClearVertical();
		}
		if (CheckLeft() || CheckRight())
		{			
			ClearHorizontal();
		}		
	}
	else
	{
		Fall();
	}
}

void Actor::PerformMovement()
{
	//if (mKinematics.mVelocity != 0)
	//{
		HandleGameBoundaries();
		HandleCollisions();
		mpTransform->Translate(mKinematics.mVelocity);		
	//}
}

void Actor::Jump()
{
	//std::cout << "Jumped\n";
	mJump.mIsJump = true;
	mJump.mIsOnGround = false;
	mKinematics.mVelocity.y = -mKinematics.GetJumpVelocity();
	AudioManager::PlayJump();
}

void Actor::Land()
{
	mJump.mIsOnGround = true;
	mJump.mIsJump = false;
	ClearVertical();
}

void Actor::Fall()
{
	mJump.mIsOnGround = false;
}

void Actor::Stomp()
{
	mJump.mIsJump = true;
	mJump.mIsOnGround = false;
	mKinematics.mVelocity.y = -mKinematics.GetJumpVelocity() / 2.0f;
	AudioManager::PlayStomp();
	mBox.mOther->mGameObject->Interact();
}

void Actor::Spin(const float& deltaTime)
{
	mpTransform->Rotate(deltaTime * 669.0f);
}

void Actor::Die()
{
	mBox.mLayer = Layer::IGNORE;
	mIsDead = true;
	mCanInput = false;
	ClearHorizontal();
	ClearVertical();
	mJump.mIsJump = true;
	mJump.mIsOnGround = false;
	mKinematics.mVelocity.y = -mKinematics.GetJumpVelocity() / 3.0f;
}

void Actor::HeadButt()
{
}

const bool Actor::CheckGround() const
{
	const float padding = 0.02f;
	const int pointCount = 3;
	const int gapCount = pointCount - 1;
	const float start = mpTransform->GetPosition().x + padding;
	const float gap = (mBox.GetSize().x - padding * 2) / gapCount;
	const float y = mBox.GetCenter().y + (mBox.GetSize().y / 2 + 0.005f);
	for (size_t i = 0; i < pointCount; i++)
	{
		const Vector2f point(start + i * gap, y);
		const bool& isFeetOnFloor = Collisions::GetCell(point).IsCollide(point);
		if (isFeetOnFloor)
		{
			return true;
		}
	}
	return false;
}

const bool Actor::CheckCeiling() const
{
	const float padding = 0.02f;
	const int pointCount = 3;
	const int gapCount = pointCount - 1;
	const float start = mpTransform->GetPosition().x + padding;
	const float gap = (mBox.GetSize().x - padding * 2) / gapCount;
	const float y = mBox.GetCenter().y - (mBox.GetSize().y / 2 + 0.005f);
	for (size_t i = 0; i < pointCount; i++)
	{
		const Vector2f point(start + i * gap, y);
		const bool& isHeadAgainstCeiling = Collisions::GetCell(point).IsCollide(point);
		if (isHeadAgainstCeiling)
		{
			return true;
		}
	}
	return false;
}

const bool Actor::CheckLeft() const
{
	const float padding = 0.02f;
	const int pointCount = 3;
	const int gapCount = pointCount - 1;
	const float start = mpTransform->GetPosition().y + padding;
	const float gap = (mBox.GetSize().y - padding * 2) / gapCount;
	const float x = mBox.GetCenter().x - (mBox.GetSize().x / 2 + 0.01f);
	for (size_t i = 0; i < pointCount; i++)
	{
		const Vector2f point(x, start + i * gap);
		const bool& isNoseAgainstWall = Collisions::GetCell(point).IsCollide(point);
		if (isNoseAgainstWall)
		{
			return true;
		}
	}
	return false;
}

const bool Actor::CheckRight() const
{
	const float padding = 0.02f;
	const int pointCount = 3;
	const int gapCount = pointCount - 1;
	const float start = mpTransform->GetPosition().y + padding;
	const float gap = (mBox.GetSize().y - padding * 2) / gapCount;
	const float x = mBox.GetCenter().x + (mBox.GetSize().x / 2 + 0.01f);
	for (size_t i = 0; i < pointCount; i++)
	{
		const Vector2f point(x, start + i * gap);
		const bool& isNoseAgainstWall = Collisions::GetCell(point).IsCollide(point);
		if (isNoseAgainstWall)
		{
			return true;
		}
	}
	return false;
}

void Actor::ClearHorizontal()
{
	mKinematics.mVelocity.x *= -0.3f;
	mHorizontalInput = 0.0f;
}

void Actor::ClearVertical()
{
	mKinematics.mVelocity.y = 0.0f;
	mVerticalInput = 0.0f;
}



Actor::Kinematics::Kinematics(const float& jumpHeight, const float& timeToApex)
{
	Evaluate(jumpHeight, timeToApex);
}

void Actor::Kinematics::Evaluate(const float& jumpHeight, const float& timeToApex)
{
	mGravity = 2 * jumpHeight / timeToApex / timeToApex;
	mJumpVelocity = mGravity * timeToApex;
}

const float& Actor::Kinematics::GetJumpVelocity() const
{
	return mJumpVelocity;
}

const float& Actor::Kinematics::GetGravity() const
{
	return mGravity;
}
