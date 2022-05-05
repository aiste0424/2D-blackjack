#pragma once
#include "GameState.h"
#include "Sprite.h"
#include "Table.h"

class PlayState : public GameState
{
public:

	enum class GameStage
	{
		TheDeal, //dealing the first 4 cards
		ExtraCard, //asks player if they want an extra card
		DeclinedCard, //what happens after the player denies a card
		AcceptedCard //what happens after the player accepts an extra card
	};

	virtual bool OnEnter();       //Load assets in this function
	virtual GameState* Update();  //Here we update all of our game mechanics
	virtual bool Render();        //Here we draw all of our scene's game objects
	virtual void OnExit();        //Unload assets in this function

private:

	Sprite m_backgroundImage;
	Sprite m_deckImage1, m_deckImage2;
	Table m_table;
};

