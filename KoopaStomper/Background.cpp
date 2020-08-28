#include "Background.h"
#include "Constants.h"
#include "Camera.h"
#include <SDL.h>

Background::Background()
	:
	mTexture()
{
	mTexture.LoadFromFile("Resources/Images/bg.png");
	const Vector2i& oriSize = mTexture.GetOriSize();
	mRelativeScreenSize = { 
		oriSize.x * SCREEN_WIDTH / GAME_WIDTH,
		oriSize.y * SCREEN_HEIGHT / GAME_HEIGHT
	};
}

Background::~Background()
{
}

Background& Background::GetInstance()
{
	static Background background;
	return background;
}

void Background::CalculateClipPosition()
{
	const Vector2f& camPos = Camera::GetPosition();

	mClipPosition.x = (int)camPos.x;
	mClipPosition.y = (int)camPos.y;
}

void Background::Render()
{
	/*GetInstance().CalculateClipPosition();

	SDL_Rect dstRect = { 0, 0 , SCREEN_WIDTH, SCREEN_HEIGHT };
	SDL_Rect srcRect = { 
		GetInstance().mClipPosition.x,
		GetInstance().mClipPosition.y,
		GetInstance().mRelativeScreenSize.x,
		GetInstance().mRelativeScreenSize.y };

	GetInstance().mTexture.SetSrcRectPosition(GetInstance().mClipPosition.x, GetInstance().mClipPosition.y);

	GetInstance().mTexture.Render({ 0 }, 0.0f);*/
}
