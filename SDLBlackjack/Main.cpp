#include <memory>
#include "Game.h"
#include "MainMenuState.h"

int main(int argc, char* argv[])
{
	std::unique_ptr<Game> game = std::make_unique<Game>(new MainMenuState);
	//TODO - change window to fullscreen, adjust all the elements
	if (game->Initialize("Blackjack", 1280, 720))
	{
		game->Run();
		game->Shutdown();
	}

	return 0;
}