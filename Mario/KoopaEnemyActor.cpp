#include "KoopaEnemyActor.h"
#include "Random.h"

KoopaEnemyActor::KoopaEnemyActor(std::vector<GameObject*>* mpEntities)
	:
	EnemyActor(mpEntities)
{
	GetTexture().LoadFromFile("Resources/Images/Koopa.png", 1, 2);
	mMoveSpeed = 69.0f;
	mOsciDuration = Random::GetRandomFloat(1.69f, 3.69f);
	mpTransform->SetScale({ 1.369f });
	mpTransform->Grow(-Random::GetRandomFloat(0.0f, 0.69f));
}

void KoopaEnemyActor::Die()
{
	EnemyActor::Die();
	mTexture.SetSpriteClip(32, 0);
}
