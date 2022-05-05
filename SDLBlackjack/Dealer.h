#pragma once
#include "Score.h"
#include "Deck.h"
#include <vector>

class Dealer
{
public:

	void ResetScore();
	void DrawCard();
	void GetScore(const Score& score);
	void AddCard(const Cards& card);

private:

	Score m_score;
	std::vector<Cards> m_cards;
};

