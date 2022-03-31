#include "RulesState.h"
#include <string>
#include "Vector2D.h"
bool RulesState::OnEnter()
{
	auto InitializingBackgroundImages = [](Sprite& sprite, std::string filename, Vector2D spriteSize, Vector2D imageSize)
	{
		sprite.Load(filename);
		sprite.SetSpriteDimension(spriteSize);
		sprite.SetImageDimension(1, 1, imageSize);
	};

	auto InitializingButtons = [](Button& button, const std::string& filenameNormal, const std::string& filenameHovered,
		const Vector2D& imageSize, const Vector2D& buttonSize, const Vector2D& buttonPosition, double angle, const Vector2D& columnsRows)
	{
		button.SetNormalAttributes(filenameNormal, imageSize, buttonSize, columnsRows); //button position missing
		button.SetHoveredAttributes(filenameHovered, imageSize, buttonSize, columnsRows);
		button.SetDimension(buttonSize); //position and dimension needs to be set BEFORE buttonRect
		button.SetPosition(buttonPosition);
		button.SetButtonRect();
		button.SetAngle(angle);
	};

	InitializingBackgroundImages(m_rulesImage, "Assets/Images/Rules/RulesPart1.png", { 1280, 720 }, { 1920, 1080 });
	InitializingBackgroundImages(m_payoutsImage, "Assets/Images/Rules/RulesPart2.png", { 1280, 720 }, { 1920, 1080 });

	InitializingButtons(m_arrowBack, "Assets/Images/Rules/ArrowBackNormal.png",
		"Assets/Images/Rules/ArrowBackHovered.png", { 450, 500 }, { 100, 100 }, { 1180, 0 },
		static_cast<double>(FacingDirection::Default), {1, 1});

	InitializingButtons(m_arrowLeftRight, "Assets/Images/Rules/ArrowSidesNormal.png",
		"Assets/Images/Rules/ArrowSidesHovered.png", { 700, 700 }, { 150, 150 }, { 1130, 570 },
		static_cast<double>(FacingDirection::Left), {1, 1});

	return true;
}

GameState* RulesState::Update()
{
	//back to main menu
	if (m_arrowBack.Update())
	{
		return new MainMenuState;
	}
	//if rules are open and the button is pressed
	else if (m_arrowLeftRight.Update() && m_rulePages == RulePages::Rules)
	{
		m_rulePages = RulePages::Payouts;
		m_arrowLeftRight.SetAngle(static_cast<double>(FacingDirection::Right));
		m_arrowLeftRight.SetPosition({ 0, 570 });
		m_arrowLeftRight.SetButtonRect();
	}
	else if (m_arrowLeftRight.Update() && m_rulePages == RulePages::Payouts)
	{
		m_rulePages = RulePages::Rules;
		m_arrowLeftRight.SetAngle(static_cast<double>(FacingDirection::Left));
		m_arrowLeftRight.SetPosition({ 1130, 570 });
		m_arrowLeftRight.SetButtonRect();
	}
	return this;
}

bool RulesState::Render()
{
	if (m_rulePages == RulePages::Rules)
	{
		m_rulesImage.Render(0, 0, 0.0);
	}
	else
	{
		m_payoutsImage.Render(0, 0, 0.0);
	}

	m_arrowBack.Render();
	m_arrowLeftRight.Render();

	return true;
}

void RulesState::OnExit()
{
	m_rulesImage.Unload();
	m_payoutsImage.Unload();
	m_arrowBack.Shutdown();
	m_arrowLeftRight.Shutdown();
}
