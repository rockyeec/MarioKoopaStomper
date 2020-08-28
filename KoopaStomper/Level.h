#pragma once

#include <vector>
#include <string>
#include "GameObject.h"


class Level
{
public:
	Level();

protected:
	void Initialize(std::vector<GameObject*>* mpEntities, const std::string& layout) const;
};

class FirstLevel : public Level
{
public:
	FirstLevel(std::vector<GameObject*>* mpEntities);
};

class SecondLevel : public Level
{
public:
	SecondLevel(std::vector<GameObject*>* mpEntities);
};

class ThirdLevel : public Level
{
public:
	ThirdLevel(std::vector<GameObject*>* mpEntities);
};

class ForthLevel : public Level
{
public:
	ForthLevel(std::vector<GameObject*>* mpEntities);
};

class LevelManager
{
public:
	static void LoadNextLevel(std::vector<GameObject*>* mpEntities);

private:
	LevelManager() = default;
	static LevelManager& GetInstance();

private:
	int mLevel = 0;
};
