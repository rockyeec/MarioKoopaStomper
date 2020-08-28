#include "Game.h"
#include "Input.h"
#include "Graphics.h"
#include "Time.h"
#include "Camera.h"
#include "PlayerActor.h"
#include "Background.h"
#include "EnemyActor.h"
#include "Tile.h"
#include <string>
#include "AudioManager.h"
#include "Level.h"


Game::Game()
	:
	mpEntities(new std::vector<GameObject*>)
{
	AudioManager::Initialize();
}

Game::~Game()
{
	for (GameObject*& entity : *mpEntities)
	{
		delete entity;
	}
	mpEntities->clear();
	delete mpEntities;
}

void Game::Run()
{	
	Start();

	do
	{
		Time::Update();

		Input::Update();

		Game::EarlyUpdate();
		
		Game::FixedUpdate();

		Game::Update();

		Game::LateUpdate();

		Graphics::Update(*mpEntities);

	} while (!IsQuit());
}

bool Game::IsQuit() const
{
	return Input::GetKey(KeyCode::Q) || Input::IsQuit();
}

void Game::Start()
{
	LevelManager::LoadNextLevel(mpEntities);
}

void Game::EarlyUpdate()
{
	for (GameObject*& entity : *mpEntities)
	{
		entity->EarlyUpdate();
	}
}

void Game::Update()
{
	for (GameObject*& entity : *mpEntities)
	{
		entity->Update();
	}	
}

void Game::FixedUpdate()
{
	mFixedUpdateTimer += Time::GetDeltaTime();

	const float& fixedDeltaTime = Time::GetFixedDeltaTime();
	while (mFixedUpdateTimer >= fixedDeltaTime)
	{
		mFixedUpdateTimer -= fixedDeltaTime;

		for (GameObject*& entity : *mpEntities)
		{
			entity->FixedUpdate();
		}
	}
}

void Game::LateUpdate()
{
	for (size_t i = 0; i < mpEntities->size(); i++)
	{
		(*mpEntities)[i]->LateUpdate();
	}
}
