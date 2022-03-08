#pragma once
#include "Cards.h"
#include "Sprite.h"

class Deck
{
public:

	Deck();

	void SetRandomSuit();
	void SetRandomRank();
	void SetSprite();

	int GetValue();

	void CardTaken(); //checks if a card was taken, if yes, sets it to 'taken'
	void ResetCards(); //resets 'taken' to false for replayability purposes

private:

	//variables for a random position in the matrix
	int m_randomSuit;
	int m_randomRank;

	const int m_maxSuit = 4;
	const  int m_maxRank = 78;
	const int m_decksUsed = 6;

	Cards m_deck[4][78];

	int m_rank;
	int m_value;
	int m_rankCounter;

	Sprite m_sprite;
};
