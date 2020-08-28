#pragma once

#include "GameObject.h"
#include <vector>

class Game
{
public:
	Game();
	~Game();
	void Run();

private:
	bool IsQuit() const;
	void Start();
	void EarlyUpdate();
	void Update();
	void FixedUpdate();
	void LateUpdate();

private:
	std::vector<GameObject*>* mpEntities;
	float mFixedUpdateTimer = 0.0f;
};