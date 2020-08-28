#pragma once

#include "Vector2.h"
#include "Constants.h"
#include <vector>
#include "BoxCollider.h"

class Cell
{
public:
	Cell();
	~Cell();

	const bool IsCollide(const Vector2f& point) const;
	const bool IsCollide(const BoxCollider& other) const;
	void Add(BoxCollider* box);
	void Remove(const BoxCollider* box);
	void Clear();

private:
	const bool IsContains(const BoxCollider* box) const;

private:
	std::vector<BoxCollider*>* mpBoxes;
};

class Collisions
{
public:
	~Collisions();
	static void Clear();
	static void OccupyCell(BoxCollider& box, const BoxCollider& oldBox);
	static bool IsCollide(BoxCollider& box);
	static Cell& GetCell(const Vector2f& position);

private:
	Collisions();
	static Collisions& GetInstance();

private:
	static constexpr int factor = 1;
	static constexpr int cellCol = TILE_COL / factor;
	static constexpr int cellRow = TILE_ROW / factor;
	static constexpr int cellWidth = TILE_WIDTH   * factor;
	static constexpr int cellHeight = TILE_HEIGHT * factor;
	static constexpr int gridLength = cellCol * cellRow;
	Cell mGrid[gridLength];
};