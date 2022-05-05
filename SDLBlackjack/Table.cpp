#include "Table.h"
#include <iostream>

void Table::Initialize()
{
	auto InitializingButtons = [](Button& button, const std::string& filenameNormal, const std::string& filenameHovered,
		const Vector2D& imageSize, const Vector2D& buttonSize, const Vector2D& buttonPosition)
	{
		button.SetNormalAttributes(filenameNormal, imageSize, buttonSize, { 1, 1 }); //button position missing
		button.SetHoveredAttributes(filenameHovered, imageSize, buttonSize, { 1, 1 });
		button.SetDimension(buttonSize); //position and dimension needs to be set BEFORE buttonRect
		button.SetPosition(buttonPosition);
		button.SetButtonRect();
	};

	InitializingButtons(m_acceptButton, "Assets/Images/UI/SelectButtonNormal.png",
		"Assets/Images/UI/SelectButtonHovered.png", { 700, 700 }, { 100, 100 }, { 200, 200 });

	InitializingButtons(m_declineButton, "Assets/Images/UI/CloseButtonNormal.png",
		"Assets/Images/UI/CloseButtonHovered.png", { 700, 700 }, { 100, 100 }, { 400, 400 });

	//putting all the cards into a stack
	for (int i = 0; i < 52; i++)
	{
		m_mainDeck.push(m_assembledCards.GetCard());
	}
}

void Table::TheDeal()
{
	//deals 2 cards to the player and 2 cards to the dealer
	for (auto i = 0; i < 2; i++)
	{
		m_player.AddCard(m_mainDeck.top());
		m_mainDeck.pop();
		m_dealer.AddCard(m_mainDeck.top());
		m_mainDeck.pop();
	}
}

bool Table::Update()
{
	if (m_buttonPressed == false)
	{
		if (m_acceptButton.Update())
		{
			m_buttonSelected = Table::ButtonSelected::Accept;
			TheDeal();
			m_buttonPressed = true;
		}
		else if (m_declineButton.Update())
		{
			m_buttonSelected = Table::ButtonSelected::Decline;
			m_buttonPressed = true;
		}
		else
		{
			m_buttonSelected = Table::ButtonSelected::None;
		}
	}

	return true;
}

bool Table::Render()
{
	if (m_buttonPressed == false)
	{
		m_acceptButton.Render();
		m_declineButton.Render();
	}
	
	m_player.Render();
	return true;
}

void Table::Unload()
{
	m_acceptButton.Unload();
	m_declineButton.Unload();
}