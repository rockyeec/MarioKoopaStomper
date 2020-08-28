#include "Spawner.h"
#include "KoopaEnemyActor.h"
#include "LuigiEnemyActor.h"
#include "PlayerActor.h"
#include "Waypoint.h"

Spawner::Spawner(std::vector<GameObject*>* mpEntities, const std::string& layout)
	:
	mpEntities(mpEntities)
{
	SetUpGrid();
	Spawn(layout);
}

Spawner::~Spawner()
{
}

void Spawner::Spawn(const std::string& layout)
{
	const size_t& length = layout.length();
	for (size_t i = 0; i < length; i++)
	{
		switch (layout[i])
		{
		case 'k':
			Instantiate<KoopaEnemyActor>(i);
			break;

		case 'l':
			Instantiate<LuigiEnemyActor>(i);
			break;

		case 'p':
			Instantiate<PlayerActor>(i);
			break;

		case 'w':
			Instantiate<Waypoint>(i);
			break;
		}
	}
}

void Spawner::SetUpGrid()
{
	const int& startX = 0;//TILE_WIDTH / 2;
	const int& startY = 0;//TILE_HEIGHT / 2;
	for (size_t y = 0; y < TILE_ROW; y++)
	{
		for (size_t x = 0; x < TILE_COL; x++)
		{
			Vector2f& cell = mGrid[y * TILE_COL + x];
			cell.x = startX + (float)x * (float)TILE_WIDTH;
			cell.y = startY + (float)y * (float)TILE_HEIGHT;
		}
	}
}

template<typename T>
void Spawner::Instantiate(const int& i)
{
	T* e = new T(mpEntities);
	e->Start();
	e->EarlyUpdate();
	e->GetTransform().SetPosition(mGrid[i]);
	e->GetTransform().mStartPosition = mGrid[i];
}
