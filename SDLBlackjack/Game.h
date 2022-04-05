#pragma once
#include <memory>
#include <string>
#include "GameState.h"

class Game
{

public:

	Game(GameState* initialState);
	bool Initialize(const std::string& windowTitle);
	bool Run();
	void Shutdown();

private:

	std::unique_ptr<GameState> m_gameState;
};