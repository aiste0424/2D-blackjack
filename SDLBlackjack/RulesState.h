#pragma once
#include "GameState.h"
#include "Button.h"
#include "Sprite.h"
#include "MainMenuState.h"


class RulesState : public GameState
{
public:
	
	virtual bool OnEnter();						//Load assets in this function
	virtual GameState* Update();				//Here we update all of our game mechanics
	virtual bool Render();						//Here we draw all of our scene's game objects
	virtual void OnExit();						//Unload assets in this function

private:
	
	Sprite m_rulesImage;
	Sprite m_payoutsImage;
	Button m_arrowBack;
	Button m_arrowLeftRight;
	bool m_isRulesSelected = false;
};

