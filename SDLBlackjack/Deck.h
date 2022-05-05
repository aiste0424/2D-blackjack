#pragma once
#include "Cards.h"
#include "Sprite.h"
#include "Screen.h"

class Deck
{
public:

	Deck();
	~Deck();

	void SetRandomSuit();
	void SetRandomRank();

	int GetValue();

	bool CardTaken(); //checks if a card was taken, if yes, sets it to 'taken'
	void ResetCards(); //resets 'taken' to false for replayability purposes

	Cards GetCard();

private:

	//variables for a random position in the matrix
	int m_randomSuit;
	int m_randomRank;

	const int M_MAXSUIT = 4;
	const int M_MAXRANK = 13;
	//const int m_decksUsed = 6;
	
	Cards m_deck[4][13];
	Cards m_selectedCard;

	int m_rank;
	int m_value;
	int m_rankCounter;

	Sprite m_cardSprite;
};
