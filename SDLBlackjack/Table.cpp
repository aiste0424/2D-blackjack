#include "Table.h"
#include <iostream>

void Table::Initialize()
{
	//============================Initializing buttons
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
		"Assets/Images/UI/SelectButtonHovered.png", { 700, 700 }, { 100, 100 }, { 440, 320 });

	InitializingButtons(m_declineButton, "Assets/Images/UI/CloseButtonNormal.png",
		"Assets/Images/UI/CloseButtonHovered.png", { 700, 700 }, { 100, 100 }, { 740, 320 });

	//================================Initializing an image of the back of a card
	m_backOfCard.Load("Assets/Images/MainGame/DeckImage.png");
	m_backOfCard.SetImageDimension(1, 1, { 128, 170 });
	m_backOfCard.SetSpriteDimension({ 128, 170 });

	m_text->Load("Assets/Fonts/PixelFont.ttf", 100);
	m_text->SetDimension(500, 50);
	m_text->SetColor(255, 245, 109, 250);

	//================================putting all the cards into a stack
	for (int i = 0; i < 52; i++)
	{
		m_mainDeck.push(m_assembledCards.GetCard());
	}

	//Initializing player and dealer
	m_player.Initialize();
	m_dealer.Initialize();
}

const Table::TableStates& Table::GetTableStates() const
{
	return m_tableStates;
}

void Table::SetTableStates(TableStates& tableState)
{
	m_tableStates = tableState;
}

void Table::TheDeal()
{
	m_mainDeck.top().SetCardState(Cards::CardState::Moving);
	m_player.AddCard(m_mainDeck.top());
	m_mainDeck.pop();
	
	m_mainDeck.top().SetCardState(Cards::CardState::Moving);
	m_dealer.AddCard(m_mainDeck.top());
	m_mainDeck.pop();

	m_player.AddCard(m_mainDeck.top());
	m_mainDeck.pop();

	m_coveredCard = m_mainDeck.top().GetImage();
	m_mainDeck.top().SetImage(m_backOfCard);
	m_dealer.AddCard(m_mainDeck.top());
	m_mainDeck.pop();
}

void Table::GiveCardToPlayer()
{
	m_mainDeck.top().SetCardState(Cards::CardState::Moving);
	m_player.AddCard(m_mainDeck.top());
	m_mainDeck.pop();
	m_tableStates = TableStates::ShowButtons;
}

bool Table::IsDouble()
{
	return false;
}

bool Table::Update()
{
	//when the game starts
	if (m_tableStates == TableStates::TheDeal && m_buttonPressed == false && m_assembledCards.GetIsStackBuilt() == true)
	{
		if (m_acceptButton.Update() == true)
		{
			TheDeal();
			m_buttonPressed = true;
		}
	}
	//when the dealer's covered card gets in place
	if (m_dealer.GetCoveredCardPlaced() == true && m_tableStates == TableStates::TheDeal)
	{
		m_tableStates = TableStates::ShowButtons;
		SetText();
		m_buttonPressed = false;
	}
	//option to choose whether to take an extra card or not
	if (m_tableStates == TableStates::ShowButtons)
	{
		if (m_acceptButton.Update() == true)
		{
			GiveCardToPlayer();
			m_tableStates = TableStates::CardAccepted;
			m_buttonPressed = true;
		}
		else if (m_declineButton.Update() == true)
		{
			m_tableStates = TableStates::CardDeclined;
			m_buttonPressed = true;
		}
	}
	
	m_player.Update();
	m_dealer.Update();
	return true;
}

void Table::SetButtonPressed(bool buttonPressed)
{
	buttonPressed = m_buttonPressed;
}

void Table::SetText()
{
	if (m_tableStates == TableStates::ShowButtons)
	{
		m_text->SetText("Would you like another card?");
	}
}

bool Table::Render()
{
	m_player.Render();
	m_dealer.Render();
	if (m_tableStates == TableStates::TheDeal)
	{
		m_acceptButton.Render();
	}
	else if (m_tableStates == TableStates::ShowButtons)
	{
		m_acceptButton.Render();
		m_declineButton.Render();
		m_text->Render(410, 250);
	}


	return true;
}

void Table::Unload()
{
	m_coveredCard.Unload();
	m_backOfCard.Unload();
	m_acceptButton.Unload();
	m_declineButton.Unload();
}