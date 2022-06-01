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
	//================================Loading font
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

void Table::TheDeal()
{
	//the first stage of the game. Player and dealer get two cards each
	//the dealer's second card is hidden.
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
	m_outcomes.IsBlackjack(m_player, m_dealer);
	if (m_outcomes.GetIsBlackjackStates() == Outcomes::IsBlackjackStates::PlayerWins)
	{
		m_tableStates = TableStates::PlayerWins;
		SetText();
	}
	else if (m_outcomes.GetIsBlackjackStates() == Outcomes::IsBlackjackStates::DealerWins)
	{
		m_tableStates = TableStates::HouseWins;
		SetText();
	}
	else if (m_outcomes.GetIsBlackjackStates() == Outcomes::IsBlackjackStates::Draw)
	{
		m_tableStates = TableStates::Draw;
		SetText();
	}
}

void Table::GiveCardToPlayer()
{
	m_mainDeck.top().SetCardState(Cards::CardState::Moving);
	m_player.AddCard(m_mainDeck.top());
	m_mainDeck.pop();
	if (m_player.GetScore()->GetScore() > 21 && m_player.GetIsReadyToMove() == true)
	{
		m_tableStates = TableStates::HouseWins;
		SetText();
	}
}

void Table::GiveCardToDealer()
{
	if (m_dealer.GetScore()->GetScore() >= 17 && m_hasPlayerDeclined == true)
	{
		if (m_outcomes.Lose(m_player, m_dealer) == true)
		{
			m_tableStates = TableStates::HouseWins;
			SetText();
		}
		else if (m_outcomes.Win(m_player, m_dealer) == true)
		{
			m_tableStates = TableStates::PlayerWins;
			SetText();
		}
		else if (m_outcomes.Draw(m_player, m_dealer) == true)
		{
			m_tableStates = TableStates::Draw;
			SetText();
		}
	}
	else
	{
		m_mainDeck.top().SetCardState(Cards::CardState::Moving);
		m_dealer.AddCard(m_mainDeck.top());
		m_mainDeck.pop();
	}
}

Table::TableStates& Table::GetTableStates()
{
	return m_tableStates;
}

bool Table::Update()
{
	m_player.Update();
	m_dealer.Update();

	//by default m_tableStates = TheDeal. Woeks when the player presses the button and the stack of cards is fully built
	if (m_assembledCards.GetIsStackBuilt() == true &&
		m_tableStates == TableStates::TheDeal &&
		m_buttonPressed == false)
	{
		if (m_acceptButton.Update() == true) //if the button is pressed before any cards are given
		{
			TheDeal(); //start giving out cards
			m_buttonPressed = true; //button is pressed, therefore don't render it in the Render() function
		}
	}

	//if the dealer's second card is in place
	if (m_dealer.GetCoveredCardPlaced() == true &&
		m_tableStates == TableStates::TheDeal)
	{
		m_tableStates = TableStates::ShowButtons;
		SetText();
		m_buttonPressed = false; //show buttons
	}
	//option to choose whether to take an extra card or not
	if (m_tableStates == TableStates::ShowButtons &&
		m_player.GetIsReadyToMove() == true &&
		m_player.GetScore()->GetScore() < 21)
	{
		if (m_acceptButton.Update() == true)
		{
			GiveCardToPlayer();
			m_buttonPressed = true;
		}
		else if (m_declineButton.Update() == true)
		{
			m_hasPlayerDeclined = true;
			m_buttonPressed = true;
		}
	}
	if (m_dealer.GetIsReadyToMove() == true &&
		m_hasPlayerDeclined == true || m_player.GetScore()->GetScore() == 21)
	{
		GiveCardToDealer();
	}

	return true;
}

void Table::SetText()
{
	if (m_tableStates == TableStates::ShowButtons)
	{
		m_text->SetText("Would you like another card?");
	}
	else if (m_tableStates == TableStates::Draw)
	{
		m_text->SetText("It's a draw!");
	}
	else if (m_tableStates == TableStates::PlayerWins)
	{
		m_text->SetText("Congratulations! You won!");
	}
	else if (m_tableStates == TableStates::HouseWins)
	{
		m_text->SetText("The house won. Better luck next time");
	}
}

bool Table::Render()
{
	m_player.Render();
	m_dealer.Render();
	//render only one button when you start the game
	if (m_tableStates == TableStates::TheDeal &&
		m_player.GetIsReadyToMove() == true)
	{
		m_acceptButton.Render();
	}
	else if (m_tableStates == TableStates::ShowButtons &&
		m_hasPlayerDeclined == false &&
		m_player.GetIsReadyToMove() == true)
	{
		m_acceptButton.Render();
		m_declineButton.Render();
		m_text->Render(410, 250);
	}

	if (m_hasPlayerDeclined == true)
	{
		m_dealer.GetScore()->Render();
		m_coveredCard.Render(m_dealer.GetCards()[1].GetPosition().x, m_dealer.GetCards()[1].GetPosition().y);
	}
	if (m_tableStates != TableStates::ShowButtons &&
		m_tableStates != TableStates::TheDeal &&
		m_player.GetIsReadyToMove() == true &&
		m_dealer.GetIsReadyToMove() == true)
	{
		m_text->Render(410, 250);
		m_coveredCard.Render(m_dealer.GetCards()[1].GetPosition().x, m_dealer.GetCards()[1].GetPosition().y);
	}

	return true;
}

void Table::Unload()
{
	m_coveredCard.Unload();
	m_backOfCard.Unload();
	m_acceptButton.Unload();
	m_declineButton.Unload();
	m_player.Unload();
	m_dealer.Unload();
}

void Table::Reset()
{
	m_assembledCards.ResetCards();
	for (int i = 0; i < 52; i++)
	{
		m_mainDeck.push(m_assembledCards.GetCard());
	}
	m_tableStates = TableStates::TheDeal;
	m_dealFinished = false;
	m_buttonPressed = false;
	m_hasPlayerDeclined = false;
} //will try to implement it for the showcase, not enough time