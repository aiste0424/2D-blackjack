#include "RulesState.h"
#include <string>
#include "Vector2D.h"
bool RulesState::OnEnter()
{
	auto InitializingBackgroundImages = [](Sprite& sprite, const std::string& filename,
										   const Vector2D& spriteSize, const Vector2D& imageSize)
	{
		sprite.Load(filename);
		sprite.SetSpriteDimension(spriteSize);
		sprite.SetImageDimension(1, 1, imageSize);
	};

	auto InitializingButtons = [](Button& button, const std::string& filenameNormal, const std::string& filenameHovered,
		const Vector2D& imageSize, const Vector2D& buttonSize, const Vector2D& buttonPosition, const Vector2D& columnsRows)
	{
		button.SetNormalAttributes(filenameNormal, imageSize, buttonSize, columnsRows); //button position missing
		button.SetHoveredAttributes(filenameHovered, imageSize, buttonSize, columnsRows);
		button.SetDimension(buttonSize); //position and dimension needs to be set BEFORE buttonRect
		button.SetPosition(buttonPosition);
		button.SetButtonRect();
	};

	InitializingBackgroundImages(m_rulesImage, "Assets/Images/Rules/RulesPart1.png", { 1280, 720 }, { 1280, 720 });
	InitializingBackgroundImages(m_payoutsImage, "Assets/Images/Rules/RulesPart2.png", { 1280, 720 }, { 1280, 720 });

	InitializingButtons(m_closeButton, "Assets/Images/UI/CloseButtonNormal.png",
		"Assets/Images/UI/CloseButtonHovered.png", { 700, 700 }, { 100, 100 }, { 1180, 0 }, {1, 1});

	//button with the same sprite as the start button
	InitializingButtons(m_arrowsButton, "Assets/Images/MainMenu/StartNormal.png",
		"Assets/Images/MainMenu/StartHovered.png", { 700, 700 }, { 100, 100 }, { 1180, 620 }, {1, 1});

	//{0, 620}
	return true;
}

GameState* RulesState::Update()
{
	//back to main menu
	if (m_closeButton.Update())
	{
		return new MainMenuState;
	}
	//if rules are open and the button is pressed
	else if (m_arrowsButton.Update() && m_rulePages == RulePages::Rules)
	{
		m_rulePages = RulePages::Payouts;
		m_arrowsButton.SetPosition({ 0, 620 });
		m_arrowsButton.SetButtonRect();
		m_arrowsButton.SetIsFlipped(true);
	}
	else if (m_arrowsButton.Update() && m_rulePages == RulePages::Payouts)
	{
		m_rulePages = RulePages::Rules;
		m_arrowsButton.SetPosition({ 1180, 620 });
		m_arrowsButton.SetButtonRect();
		m_arrowsButton.SetIsFlipped(false);
	}

	return this;
}

bool RulesState::Render()
{
	if (m_rulePages == RulePages::Rules)
	{
		m_rulesImage.Render(0, 0);
	}
	else if (m_rulePages == RulePages::Payouts)
	{
		m_payoutsImage.Render(0, 0);
		
	}

	m_arrowsButton.Render();
	m_closeButton.Render();

	return true;
}

void RulesState::OnExit()
{
	m_rulesImage.Unload();
	m_payoutsImage.Unload();
	m_closeButton.Unload();
	m_arrowsButton.Unload();
}
