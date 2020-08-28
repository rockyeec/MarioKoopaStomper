#include "Input.h"

#include <iostream>

const bool Input::IsQuit()
{
	return GetInstance().mE.type == SDL_QUIT;
}

const void Input::Update()
{
	SDL_Event& e = GetInstance().mE;
	bool* buttons = GetInstance().buttons;

    SDL_PollEvent(&e);
	
	bool isKeyDown = e.type == SDL_KEYDOWN;

	switch (e.key.keysym.sym)
	{
	case SDLK_UP:
		buttons[(int)KeyCode::UP] = isKeyDown;
		break;

	case SDLK_DOWN:
		buttons[(int)KeyCode::DOWN] = isKeyDown;
		break;

	case SDLK_LEFT:
		buttons[(int)KeyCode::LEFT] = isKeyDown;
		break;

	case SDLK_RIGHT:
		buttons[(int)KeyCode::RIGHT] = isKeyDown;
		break;

	case SDLK_q:
		buttons[(int)KeyCode::Q] = isKeyDown;
		break;
	}
}

const bool Input::GetKey(const KeyCode& key)
{
	return GetInstance().buttons[(int)key];
}

Input::Input() 
	: 
	mE(SDL_Event()),
	buttons{ false }
{
	
}

Input& Input::GetInstance()
{
    static Input input;
    return input;
}
