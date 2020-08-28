#pragma once
#include "Texture.h"
#include "BoxCollider.h"
#include "GameObject.h"
#include "Constants.h"
#include <string>


class TileMap
{
private:
	class Tile : public GameObject
	{
	public:
		Tile();
		~Tile();
	};

public:
	~TileMap();

	static void Initialize(const std::string& layout);
	static void Render();
	static void Clear();

private:
	TileMap();
	static TileMap& GetInstance();
	static void SetTile(const int& i, const char& c);
	static Tile& GetTile(const float& x, const float& y);

private:
	static constexpr int gridLength = TILE_COL * TILE_ROW;
	Tile* mGrid[gridLength];
};