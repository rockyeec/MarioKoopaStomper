#pragma once
#include "Vector2.h"
#include <SDL.h>

class Texture
{
public:
	Texture();
	~Texture();
	
	void LoadFromFile(const char* path, const int& slice_rows = 1, const int& slice_cols = 1);
	void Free();
	void Render(const Vector2f& position, const float& angle);

	const Vector2f GetSizeFloat() const;
	const Vector2i GetOriSize() const;
	void SetSizeWithScale(const Vector2f& scale);
	void SetSize(const Vector2i& scale);
	void SetFlip(const int& flip);
	void SetSpriteClip(const int& x, const int& y);
	void SetSpriteClip(const Vector2i& v);

private:
	void SetSrcRectSize(const int& w, const int& h);
	void SetDstRectPosition(const Vector2f& position);

private:
	SDL_Texture* mTexture;
	int mFlip;
	SDL_Rect mSrcRect;
	SDL_Rect mDstRect;
};