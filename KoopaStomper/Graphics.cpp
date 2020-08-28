#include "Graphics.h"
#include "Constants.h"
#include "Background.h"
#include "Tile.h"

Graphics::Graphics()
{
	SDL_Init(SDL_INIT_VIDEO);

	mWindow = SDL_CreateWindow(
		"Koopa Stomper",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH, SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN);

	mRenderer = SDL_CreateRenderer(
		mWindow,
		-1,
		SDL_RENDERER_ACCELERATED);

	IMG_Init(IMG_INIT_PNG);
}

Graphics::~Graphics()
{
	SDL_DestroyWindow(mWindow);
	SDL_DestroyRenderer(mRenderer);

	IMG_Quit();
	SDL_Quit();
}


Graphics& Graphics::GetInstance()
{
	static Graphics graphics;
	return graphics;
}


void Graphics::Update(std::vector<GameObject*>& objects)
{
	SDL_Renderer* renderer = GetInstance().mRenderer;

	SDL_SetRenderDrawColor(renderer, 0x88, 0xCC, 0xFF, 0xFF);
	SDL_RenderClear(renderer);

	// background is ugly
	//Background::Render();

	TileMap::Render();

	for (GameObject*& object : objects)
	{
		object->Render();
	}

	SDL_RenderPresent(renderer);
}

SDL_Renderer* Graphics::GetRenderer()
{
	return GetInstance().mRenderer;
}
