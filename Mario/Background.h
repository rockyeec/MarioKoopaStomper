#pragma once
#include "Texture.h"

class Background
{
public:
	~Background();
	static void Render();

private:
	Background();
	static Background& GetInstance();
	void CalculateClipPosition();

private:
	Texture mTexture;
	Vector2i mRelativeScreenSize;
	Vector2i mClipPosition;
};