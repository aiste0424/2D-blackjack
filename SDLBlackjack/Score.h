#pragma once
#include "Deck.h"
#include "Cards.h"

class Score
{
public:

	Score();

	int GetScore();
	void SetScore(int score);
	void PrintScore();
	void UpdateScore();

	void SetCardValue(int value);

private:

	int m_cardValue;
	int m_score;
};
