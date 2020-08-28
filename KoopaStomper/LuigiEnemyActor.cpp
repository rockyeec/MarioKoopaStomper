#include "LuigiEnemyActor.h"
#include "Random.h"

LuigiEnemyActor::LuigiEnemyActor(std::vector<GameObject*>* mpEntities)
	:
	EnemyActor(mpEntities)
{
	GetTexture().LoadFromFile("Resources/Images/Luigi.png");
	mMoveSpeed = 269.0f;
	mOsciDuration = Random::GetRandomFloat(1.69f, 2.69f);
	mpTransform->SetScale({ 1.369f });
	mpTransform->Grow(-Random::GetRandomFloat(0.0f, 0.69f));
}

void LuigiEnemyActor::SubClassUpdate(const float& deltaTime)
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
		mMoveSpeed = Random::GetRandomFloat(169.0f, 469.0f);
		mJump.mJumpButton = (Random::GetRandomInt(0, 10) < 3);
	}
	SetHorizontal(mIsOsci, !mIsOsci);

	mpTransform->Rotate(mHorizontalInput * mMoveSpeed / 500.0f);
}
