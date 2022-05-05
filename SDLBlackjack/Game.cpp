 #include "Game.h"
#include "Screen.h"
#include "Input.h"

Game::Game(GameState* initialState)
{
	m_gameState.reset(initialState);
}

bool Game::Initialize(const std::string& windowTitle, int width, int height)
{
	Screen::Instance()->Initialize(windowTitle, width, height);

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
		//If no switch is required then the current state's pointer is returned
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
		if (Input::Instance()->GetKeyDown() == SDLK_ESCAPE || Input::Instance()->IsWindowClosed())
		{
			m_gameState->OnExit();
			m_gameState = nullptr;
		}
	}
	return true;
}

void Game::Shutdown()
{
	Screen::Instance()->Shutdown();
	//Close down everything you initialized in init()
}
