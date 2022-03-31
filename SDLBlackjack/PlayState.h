#pragma once
#include "GameState.h"
#include "Sprite.h"
#include "Deck.h"
#include "Button.h"

class PlayState : public GameState
{
public:

	virtual bool OnEnter();       //Load assets in this function
	virtual GameState* Update();  //Here we update all of our game mechanics
	virtual bool Render();        //Here we draw all of our scene's game objects
	virtual void OnExit();        //Unload assets in this function

private:

	Sprite m_backgroundImage;
	Deck m_deck;
	Button m_buttonGetCard;
};

