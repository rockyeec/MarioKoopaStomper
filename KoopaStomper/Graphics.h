#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <vector>

class GameObject;
class Graphics
{
public:
	~Graphics();
	static void Update(std::vector<GameObject*>& objects);
	static SDL_Renderer* GetRenderer();

private:
	Graphics();
	static Graphics& GetInstance();

private:
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
};