#include "SpaceGame.h"
#include "Engine.h"

using namespace nu;

bool SpaceGame::Initialize()
{
	Game::Initialize();

	m_scene = new Scene();
	return true;
}

void SpaceGame::Update(float dt)
{
	switch (m_gamestate)
	{
	case SpaceGame::GameState::Title:
		if (Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE))
		{
			m_gamestate = GameState::StartGame;
		}
		break;
	case SpaceGame::GameState::StartGame:
		m_score = 0;
		m_lives = 3;
		m_gamestate = GameState::StartLevel;

		break;
	case SpaceGame::GameState::StartLevel:
		break;
	case SpaceGame::GameState::Game:
		break;
	case SpaceGame::GameState::GameOver:
		break;
	default:
		break;
	}


	Game::Update(dt);
}

void SpaceGame::Draw(const nu::Renderer& renderer)
{
	switch (m_gamestate)
	{
	case SpaceGame::GameState::Title:
		//Draw title
		break;
	case SpaceGame::GameState::StartGame:
		break;
	case SpaceGame::GameState::StartLevel:
		
		break;
	case SpaceGame::GameState::Game:
		//Draw score and lives
		break;
	case SpaceGame::GameState::GameOver:
		//Draw game over
		break;
	default:
		break;
	}
	Game::Draw(renderer);
}
