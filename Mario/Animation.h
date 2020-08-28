#pragma once

#include "Texture.h"
#include <vector>

class Animation
{
public:
	Animation();
	~Animation();
	void Initialize(Texture* texture);
	void Update(const float& deltaTime);
	void AddClip(const Vector2i* clip);

private:
	Texture* mpTexture = NULL;
	std::vector<const Vector2i*>* mpClips;
	int mCurClip = 0;
	float mTimer = 0.0f;
	float mDuration = 0.1f;
};