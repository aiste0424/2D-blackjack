#pragma once
#include "Input.h"
#include "Sprite.h"
#include "GameState.h"
#include "Button.h"

class MainMenuState : public GameState
{
public:

	virtual bool OnEnter();						//Load assets in this function
	virtual GameState* Update();				//Here we update all of our game mechanics
	virtual bool Render();						//Here we draw all of our scene's game objects
	virtual void OnExit();						//Unload assets in this function

private:

	Sprite m_backgroundSprite;
	Button m_startButton;
	Button m_rulesButton;
};
