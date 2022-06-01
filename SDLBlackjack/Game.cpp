 #include "Game.h"
#include "Screen.h"
#include "Input.h"
#include "Text.h"
#include "Music.h"

Game::Game(GameState* initialState)
{
	m_gameState.reset(initialState);
}

bool Game::Initialize(const std::string& windowTitle, int width, int height)
{
	Screen::Instance()->Initialize(windowTitle, width, height);
	Text::Initialize();
	Music::Initialize();

	//Init music system
	return true;
}

bool Game::Run()
{
	m_gameState->OnEnter();

	while (m_gameState)  //will break if m_gameState == nullptr
	{
		Uint64 start = SDL_GetPerformanceCounter();
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

		//capping the frame rate to 60 FPS approx
		Uint64 end = SDL_GetPerformanceCounter();
		float elapsedMS = (end - start) / static_cast<float>(SDL_GetPerformanceFrequency());
		float delay = 16.666f - elapsedMS;
		SDL_Delay(static_cast<Uint32>(floor(delay)));
	}
	return true;
}

void Game::Shutdown()
{
	Screen::Instance()->Shutdown();
	Text::Shutdown();
	Music::Shutdown();
}