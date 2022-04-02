#pragma once
#include "GameState.h"
#include "Button.h"
#include "Sprite.h"
#include "MainMenuState.h"


class RulesState : public GameState
{
public:

	enum class RulePages
	{
		Rules,
		Payouts
	};
	
	virtual bool OnEnter();						//Load assets in this function
	virtual GameState* Update();				//Here we update all of our game mechanics
	virtual bool Render();						//Here we draw all of our scene's game objects
	virtual void OnExit();						//Unload assets in this function

private:
	
	Sprite m_rulesImage, m_payoutsImage;
	Button m_closeButton, m_arrowLeft, m_arrowRight;
	RulePages m_rulePages = {RulePages::Rules};
};

