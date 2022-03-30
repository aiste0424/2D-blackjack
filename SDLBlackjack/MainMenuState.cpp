#include "MainMenuState.h"
#include "RulesState.h"
#include "PlayState.h"
#include "Vector2D.h"
#include <iostream>
#include <string>

bool MainMenuState::OnEnter()
{
	//Initializing background images
	m_backgroundSprite.Load("Assets/Images/MainMenu/MainMenuImage.png");   //Load image
	m_backgroundSprite.SetSpriteDimension(1280, 720);                     //The size of the image on the screen
	m_backgroundSprite.SetImageDimension(1, 1, 1920, 1080);               //The size of the image in the folder
	
	//Intitializing buttons, both normals and hovered
	auto InitializingButtons = [](Button& button, std::string filenameNormal, std::string filenameHovered,
								  Vector2D imageSize, Vector2D buttonSize, Vector2D buttonPosition)
	{
		button.SetNormalAttributes(filenameNormal, imageSize, buttonPosition);
		button.SetHoveredAttributes(filenameHovered, imageSize, buttonPosition);
		button.SetPosition(buttonPosition);
		button.SetDimension(buttonSize);
		button.SetButtonRect();
	};

	//calling lambdas
	InitializingButtons(m_startButton, "Assets/Images/MainMenu/StartButton.png", "Assets/Images/MainMenu/StartHoveredButton.png",
						{1920, 1080}, {300, 150}, {490, 285});
	InitializingButtons(m_rulesButton, "Assets/Images/MainMenu/RulesButton.png", "Assets/Images/MainMenu/RulesHoveredButton.png",
						{ 1920, 1080 }, {300, 150}, {490, 445});
	
	return true;
}

GameState* MainMenuState::Update()
{
	//starts the game if Update() == true
	if (m_startButton.Update())
	{
		return new PlayState;
	}
	//opens the rules if Update() == true
	else if (m_rulesButton.Update())
	{
		return new RulesState;
	}
	//otherwise stays in the same game state
	return this;
}

bool MainMenuState::Render()
{
	m_backgroundSprite.Render(0, 0, 0.0);
	m_startButton.Render(Button::FacingDirection::Default);
	m_rulesButton.Render(Button::FacingDirection::Default);
	return true;
}

void MainMenuState::OnExit()
{
	m_backgroundSprite.Unload();
	m_startButton.Shutdown();
	m_rulesButton.Shutdown();
}