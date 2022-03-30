#pragma once
#include <memory>
#include "GameState.h"

class Game
{

public:

	Game(GameState* initialState);
	bool Initialize();
	bool Run();
	void Shutdown();

private:

	std::unique_ptr<GameState> m_gameState;
};