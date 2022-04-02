#include "MainMenuState.h"
#include "RulesState.h"
#include "PlayState.h"

bool MainMenuState::OnEnter()
{
	auto InitializingBackgroundImages = [](Sprite& sprite, std::string filename, Vector2D spriteSize, Vector2D imageSize)
	{
		sprite.Load(filename);
		sprite.SetSpriteDimension(spriteSize);
		sprite.SetImageDimension(1, 1, imageSize);
	};

	InitializingBackgroundImages(m_mainMenuBackground, "Assets/Images/MainMenu/MainMenuImage.png",
								{ 1280, 720 }, { 1280, 720 });
	InitializingBackgroundImages(m_exitBackground, "Assets/Images/MainMenu/ExitGameImage.png",
								{ 512, 384 }, {256, 192});

	//Intitializing buttons, both normals and hovered
	auto InitializingButtons = [](Button& button, const std::string& filenameNormal, const std::string& filenameHovered,
								  const Vector2D& imageDimensions, const Vector2D& spriteDimensions, const Vector2D& buttonPosition)
	{
		button.SetNormalAttributes(filenameNormal, imageDimensions, spriteDimensions, {1, 1});
		button.SetHoveredAttributes(filenameHovered, imageDimensions, spriteDimensions, {1, 1});
		button.SetPosition(buttonPosition);
		button.SetDimension(spriteDimensions);
		button.SetButtonRect();
	};

	//calling lambdas
	InitializingButtons(m_startButton, "Assets/Images/MainMenu/StartNormal.png",
						"Assets/Images/MainMenu/StartHovered.png",
						{ 700, 700 }, {150, 150}, { 490, 285 });

	InitializingButtons(m_rulesButton, "Assets/Images/MainMenu/RulesNormal.png",
						"Assets/Images/MainMenu/RulesHovered.png",
						{ 700, 700 }, {150, 150}, { 490, 465 });

	InitializingButtons(m_exitButton, "Assets/Images/MainMenu/ExitNormal.png",
						"Assets/Images/MainMenu/ExitHovered.png",
						{ 700, 700 }, { 150, 150 }, {0, 0});

	InitializingButtons(m_no, "Assets/Images/UI/CloseButtonNormal.png",
						"Assets/Images/UI/CloseButtonHovered.png",
						{ 700, 700 }, { 100, 100 }, { 746, 410 });

	InitializingButtons(m_yes, "Assets/Images/UI/SelectButtonNormal.png",
						"Assets/Images/UI/SelectButtonHovered.png",
						{ 700, 700 }, { 100, 100 }, { 434, 410 });
	
	return true;
}

GameState* MainMenuState::Update()
{
	//starts the game if Update() == true
	if (m_imageOpen == MainMenuState::ImageOpen::MainMenu)
	{
		if (m_startButton.Update())
		{
			return new PlayState;
		}
		//opens the rules if Update() == true
		else if (m_rulesButton.Update())
		{
			return new RulesState;
		}
		else if (m_exitButton.Update())
		{
			m_imageOpen = MainMenuState::ImageOpen::Exit;
		}
	}
	else if (m_imageOpen == MainMenuState::ImageOpen::Exit)
	{
		if (m_yes.Update())
		{
			return nullptr;
		}
		else if (m_no.Update())
		{
			m_imageOpen = MainMenuState::ImageOpen::MainMenu;
		}
	}
	//otherwise stays in the same game state
	return this;
}

bool MainMenuState::Render()
{
	m_mainMenuBackground.Render(0, 0);
	m_startButton.Render();
	m_rulesButton.Render();
	m_exitButton.Render();

	if (m_imageOpen == MainMenuState::ImageOpen::Exit)
	{
		m_exitBackground.Render(384, 168);
		m_yes.Render();
		m_no.Render();
	}
	
	return true;
}

void MainMenuState::OnExit()
{
	m_mainMenuBackground.Unload();
	m_exitBackground.Unload();
	m_startButton.Shutdown();
	m_rulesButton.Shutdown();
	m_exitButton.Shutdown();
	m_yes.Shutdown();
	m_no.Shutdown();
}