#include "Animation.h"

Animation::Animation()
	:
	mpClips(new std::vector<const Vector2i*>)
{
}

Animation::~Animation()
{
	for (const Vector2i*& pClip : *mpClips)
	{
		delete pClip;
	}
	delete mpClips;
}

void Animation::Initialize(Texture* texture)
{
	mpTexture = texture;
}

void Animation::Update(const float& deltaTime)
{
	mTimer += deltaTime;
	if (mTimer >= mDuration)
	{
		mTimer -= mDuration;
		mCurClip = (mCurClip + 1) % mpClips->size();
		mpTexture->SetSpriteClip(*(*mpClips)[mCurClip]);
	}
}

void Animation::AddClip(const Vector2i* clip)
{
	mpClips->push_back(clip);
}
