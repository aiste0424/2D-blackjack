#include <SDL.h>
#include "Screen.h"
#include "Input.h"
#include "Sprite.h"


int main(int argc, char* argv[])
{
	bool isGameRunning = true;
	Screen screen;
	Sprite cards;
	Input input;
	
	
	if (!screen.Initialize("Chibi Rascal"))
	{
		return 0;
	}
	cards.Load("Assets/Images/DeckOfCards.png", screen);
	cards.SetSpriteDimension(148, 230);
	cards.SetImageDimension(13, 5, 1924, 1150);
	cards.IsAnimated(false);

	while (isGameRunning)
	{
		if (input.IsWindowClosed())
		{
			isGameRunning = false;
		}
		if (input.GetKeyDown() == SDLK_ESCAPE)
		{
			isGameRunning = false;
		}
		
		screen.Clear();
		cards.Render(0, 0, 0.0, screen);
		input.Update();
		screen.Present();
	}
	cards.Unload();
	screen.Shutdown();
	return 0;
}