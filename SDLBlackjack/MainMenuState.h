#pragma once
#include "Sprite.h"
#include "GameState.h"
#include "Button.h"
#include "Vector2D.h"

class MainMenuState : public GameState
{
public:

	enum class ImageOpen
	{
		MainMenu,
		Exit
	};

	virtual bool OnEnter();						//Load assets in this function
	virtual GameState* Update();				//Here we update all of our game mechanics
	virtual bool Render();						//Here we draw all of our scene's game objects
	virtual void OnExit();						//Unload assets in this function

private:

	Sprite m_mainMenuBackground, m_exitBackground;
	Button m_startButton, m_rulesButton, m_exitButton;
	Button m_yes, m_no;
	ImageOpen m_imageOpen = {ImageOpen::MainMenu};
};