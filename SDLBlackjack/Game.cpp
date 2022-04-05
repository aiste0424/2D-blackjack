 #include "Game.h"
#include "Screen.h"
#include "Input.h"

Game::Game(GameState* initialState)
{
	m_gameState.reset(initialState);
}

bool Game::Initialize(const std::string& windowTitle)
{
	Screen::Instance()->Initialize(windowTitle);

	//Init music system
	//Init Font system
	//Init third-party libraries
	return true;
}

bool Game::Run()
{
	m_gameState->OnEnter();

	while (m_gameState)  //will break if m_gameState == nullptr
	{
		Screen::Instance()->Clear();
		Input::Instance()->Update();
		
		//checking delta time

		//updating the current game state

		//current game state will return a pointer to a different state if a switch is required 
		//If no switch is required then the current states pointer is returned
		GameState* nextState = m_gameState->Update();

		m_gameState->Render();
		Screen::Instance()->Present();

		//This will only run if a switch is required
		if (nextState != m_gameState.get())
		{
			m_gameState->OnExit();
			m_gameState.reset(nextState);

			if (m_gameState)
			{
				m_gameState->OnEnter();
			}
		}

		//rendering the screen
	}
	return true;
}

void Game::Shutdown()
{
	Screen::Instance()->Shutdown();
	//Close down everything you initialized in init()
}
