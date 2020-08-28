#include "Tile.h"
#include "Camera.h"
#include "Mathf.h"

TileMap::Tile::Tile()
	: 
	GameObject(NULL)
{
	mTexture.LoadFromFile("Resources/Images/tile.png");
	mIsOutsideScreen = false;
	mpTransform->SetScale(Vector2f(float(TILE_WIDTH), float(TILE_HEIGHT)) / mTexture.GetSizeFloat());
}

TileMap::Tile::~Tile()
{
}

TileMap::TileMap()
	:
	mGrid{ NULL }
{	
}

TileMap& TileMap::GetInstance()
{
	static TileMap tileMap;
	return tileMap;
}

TileMap::~TileMap()
{
}

void TileMap::Initialize(const std::string& layout)
{
	const size_t& length = layout.length();
	for (size_t i = 0; i < length; i++)
	{
		SetTile(i, layout[i]);
	}
}

void TileMap::Render()
{
	const size_t rows = SCREEN_HEIGHT / TILE_HEIGHT + 2;
	const size_t cols = SCREEN_WIDTH / TILE_WIDTH + 2;
	const Vector2f start = Camera::GetPosition() - Vector2f(float(TILE_WIDTH / 2), float(TILE_HEIGHT / 2));
	for (size_t y = 0; y < rows; y++)
	{
		for (size_t x = 0; x < cols; x++)
		{
			Tile& tile = GetTile(start.x + x * TILE_WIDTH, start.y + y * TILE_HEIGHT);
			if (&tile != NULL)
			{
				tile.Render();
			}
		}
	}
}

void TileMap::Clear()
{
	const size_t& length = gridLength;
	for (size_t i = 0; i < length; i++)
	{
		Tile*& tile = GetInstance().mGrid[i];
		delete tile;
		tile = NULL;
	}
}

void TileMap::SetTile(const int& i, const char& c)
{
	if (c == '#')
	{
		Tile* tile = new Tile();

		const Vector2f pos(float(i % TILE_COL * TILE_WIDTH) , float(i / TILE_COL * TILE_HEIGHT) );

		tile->GetTransform().SetPosition(pos);

		tile->Start();

		GetInstance().mGrid[i] = tile;
	}
}

TileMap::Tile& TileMap::GetTile(const float& x, const float& y)
{
	const Vector2i pos(
		int(roundf(x)) / TILE_WIDTH  ,
		int(roundf(y)) / TILE_HEIGHT );

	const int index =Mathf::Clamp(0, gridLength - 1, pos.y * TILE_COL + pos.x);
	return *(GetInstance().mGrid[index]);
}