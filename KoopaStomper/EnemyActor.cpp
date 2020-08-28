#include "EnemyActor.h"
#include "Random.h"

EnemyActor::EnemyActor(std::vector<GameObject*>* entityList)
	:
	Actor(Layer::ENEMY, entityList)
{	
}

void EnemyActor::Interact()
{
	Die();
}

void EnemyActor::SubClassUpdate(const float& deltaTime)
{
	if (mOsciTimer < mOsciDuration)
	{
		mOsciTimer += deltaTime;
	}
	else
	{
		mOsciTimer -= mOsciDuration;
		mIsOsci = !mIsOsci;
		mOsciDuration = Random::GetRandomFloat(1.69f, 3.69f);

		mJump.mJumpButton = (Random::GetRandomInt(0, 10) < 3);
	}
	SetHorizontal(mIsOsci, !mIsOsci);
}

void EnemyActor::SubClassFixedUPdate(const float& deltaTime)
{
}

const bool EnemyActor::IsStomp() const
{
	if (mBox.mOther == NULL)
		return false;

	return mBox.mOther->mLayer == Layer::PLAYER;
}

