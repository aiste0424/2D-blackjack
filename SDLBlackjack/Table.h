#pragma once
#include "Deck.h"
#include "Dealer.h"
#include "GameObject.h"
#include "Button.h"
#include <stack>
#include "Player.h"

class Table : public GameObject
{
public:

	enum class TableStates
	{
		TheDeal,
		CardAccepted,
		CardDeclined,
		IsBlackjack,
		IsDouble,
		DoesPlayerDouble
	};

	enum class ButtonSelected
	{
		None,
		Accept,
		Decline
	};

	void Initialize();
	void TheDeal();
	void Unload();
	virtual bool Render() override;
	virtual bool Update() override;

private:

	Player m_player;
	Dealer m_dealer;
	
	std::stack<Cards> m_mainDeck;
	Deck m_assembledCards; //avengers assemble

	Button m_acceptButton, m_declineButton;
	ButtonSelected m_buttonSelected = { ButtonSelected::None };
	
	TableStates m_tableStates = {TableStates::TheDeal};

	bool m_buttonPressed = false;

	//The Deal
	
	//Check if blackjack.
		//TRUE - reveal dealer's closed card. If the dealer has a blackjack - DRAW, else WIN.
		//FALSE - check if the player can double (check both the cards and the budget).
				 //if TRUE - ask the player if they want to double.
						//if TRUE - give player only one card. Then the dealer's turn.

	//If no blackjack and no double TRUE
		//Player pulls cards until they say no or go above 21 and LOSE.
		//After player's turn finishes, the dealer takes cards until the total score of 17.
		//If the dealer goes above 21, player WINS. If dealer's score is bigger than the player's, player LOSES.
		//If the player's score is bigger than the dealers, player wins.

	//depending on the outcome, pay the player or take away the bet.
	//check if player has enough money for another round. Ask if the player wants to play another match.
	//if half of the deck was used, reshuffle.
};

