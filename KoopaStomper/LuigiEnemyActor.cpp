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
