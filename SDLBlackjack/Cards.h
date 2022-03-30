#pragma once
#include "Sprite.h"

class Cards
{
public:

	enum class Suit
	{
		//the allignment is the same as in the DeckOfCards.png. DO NOT TOUCH
		Clubs,
		Diamonds,
		Hearts,
		Spades
	};

	//the allignment is the same as in the DeckOfCards.png. DO NOT TOUCH
	enum class Rank
	{
		Ace = 1,
		Two,
		Three,
		Four,
		Five,
		Six,
		Seven,
		Eight,
		Nine,
		Ten,
		Jack,
		Queen,
		King
	};

	Cards();

	void SetSuit(Suit suit);
	void SetRank(Rank rank);
	void SetValue(int value);
	void SetIsTaken(bool taken);
	void SetImage(Sprite& sprite);

	Suit GetSuit();
	Rank GetRank();
	int GetValue();
	bool GetIsTaken();

private:

	Suit m_suit;
	Rank m_rank;
	int m_value;
	bool m_isTaken;
	Sprite m_sprite;
};
