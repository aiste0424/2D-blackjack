#pragma once
#include "Deck.h"
#include "Dealer.h"
#include "GameObject.h"
#include "Button.h"
#include <stack>
#include "Player.h"
#include "Text.h"
#include "Outcomes.h"

class Table : public GameObject
{
public:

	enum class TableStates
	{
		TheDeal,
		ShowButtons,
		Draw,
		PlayerWins,
		HouseWins, //aka dealer wins
	};

	//game states
	void TheDeal();
	void GiveCardToPlayer();
	void GiveCardToDealer();
	TableStates& GetTableStates();
	void Reset();

	void Initialize();
	virtual bool Render() override;
	virtual bool Update() override;
	void Unload();

	void SetText();

private:

	bool m_dealFinished = false;
	bool m_buttonPressed = false;
	bool m_hasPlayerDeclined = false;

	Player m_player;
	Dealer m_dealer;
	Outcomes m_outcomes;
	
	Deck m_assembledCards;
	std::stack<Cards> m_mainDeck;

	Button m_acceptButton, m_declineButton;

	TableStates m_tableStates = {TableStates::TheDeal};

	Sprite m_backOfCard;
	Sprite m_coveredCard;

	Text* m_text = new Text;
};