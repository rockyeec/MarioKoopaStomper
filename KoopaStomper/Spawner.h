#pragma once

#include <string>
#include <vector>
#include "Vector2.h"
#include "GameObject.h"
#include "Constants.h"

class Spawner
{
public:
	Spawner(std::vector<GameObject*>* mpEntities, const std::string& layout);
	~Spawner();


private:
	void Spawn(const std::string& layout);
	void SetUpGrid();

	template<typename T>
	void Instantiate(const int& i);

private:
	std::vector<GameObject*>* mpEntities;
	static constexpr int mGridSize = TILE_COL * TILE_ROW;
	Vector2f mGrid[mGridSize];
};