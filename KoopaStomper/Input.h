#pragma once
#include <SDL.h>


// key mapping is in Input::Update()
enum class KeyCode
{
	UP = 0,
	DOWN,
	LEFT,
	RIGHT,
	Q,

	TOTAL
};

class Input
{
public:
	static const bool IsQuit();
	static const void Update();
	static const bool GetKey(const KeyCode& key);

private:
	Input();
	static Input& GetInstance();

private:
	SDL_Event mE;
	bool buttons[(int)KeyCode::TOTAL];
};