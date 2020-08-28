#include "Waypoint.h"
#include "Level.h"

Waypoint::Waypoint(std::vector<GameObject*>* mpEntities)
	:
	GameObject(mpEntities),
	mpEntities(mpEntities),
	mClips { Vector2i()},
	mpArrow(new Arrow(*this, mpEntities))
{
	mTexture.LoadFromFile("Resources/Images/PowBlock.png", 1, 3);
	mBox.mLayer = Layer::NEXT_LEVEL;

	mClips[0] = { 64, 0 };
	mClips[1] = { 32, 0 };

	mTexture.SetSpriteClip(mClips[0]);
}


void Waypoint::Interact()
{
	mTexture.SetSpriteClip(mClips[++mState]);

	if (mState == 3)
		LevelManager::LoadNextLevel(mpEntities);
}