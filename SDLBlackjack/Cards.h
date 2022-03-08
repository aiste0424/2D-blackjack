#pragma once

class Cards
{
public:

	enum class Suit
	{
		//the allignment is the same as in the m_deck[][] matrix. DO NOT TOUCH
		Clubs,
		Hearts,
		Spades,
		Diamonds
	};

	//starts from 2, because card values start from 2 (easier to get the values)
	enum class Rank
	{
		Two = 2,
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
		King,
		Ace
	};

	Cards();

	void SetSuit(Suit suit);
	void SetRank(Rank rank);
	void SetValue(int value);
	void SetIsTaken(bool taken);

	Suit GetSuit();
	Rank GetRank();
	int GetValue();
	bool GetIsTaken();

private:

	Suit m_suit;
	Rank m_rank;
	int m_value;
	bool m_isTaken;
};
