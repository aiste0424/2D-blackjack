#include "Deck.h"
#include <time.h>
#include <string>
#include <iostream>

Deck::Deck()
{
	//changing variable from time_t to unsigned int because of a warning "Possible loss of data"
	srand(unsigned int(time(0)));

	m_randomSuit = 0;
	m_randomRank = 0;

	m_rankCounter = 1;
	m_rank = 0;
	m_value = 0;

	//initializing the correct card suits, ranks and values
	for (int i = 0; i < m_maxSuit; i++)
	{
		//ranks and values are reset to 2 every time a new row begins
		m_rank = 2;
		m_value = 2;
		for (int j = 0; j < m_maxRank; j++)
		{
			m_deck[i][j].SetIsTaken(false);
			m_deck[i][j].SetSuit(static_cast<Cards::Suit>(i));
			m_deck[i][j].SetRank(static_cast<Cards::Rank>((m_rank)));

			//jack, queen and king have a value of 10.
			if ((m_value) > static_cast<int>(Cards::Rank::Ten) && (m_value) != static_cast<int>(Cards::Rank::Ace))
			{
				m_deck[i][j].SetValue(static_cast<int>(Cards::Rank::Ten));
			}
			//ace default value is 11
			else if ((m_value) == static_cast<int>(Cards::Rank::Ace))
			{
				m_deck[i][j].SetValue(static_cast<int>(Cards::Rank::Jack));
			}
			//the rest of the values
			else
			{
				m_deck[i][j].SetValue((m_value));
			}

			//each card is repeated 6 times, because there are 6 decks being used
			if (m_rankCounter == m_decksUsed)
			{
				//ranks and values are increased by one every 6 times
				m_rankCounter = 1;
				m_rank++;
				m_value++;
			}
			else
			{
				m_rankCounter++;
			}
		}
	}
}

void Deck::SetRandomSuit()
{
	m_randomSuit = rand() % m_maxSuit;
}

void Deck::SetRandomRank()
{
	m_randomRank = rand() % m_maxRank;
}

void Deck::SetSprite()
{
}

int Deck::GetValue()
{
	return m_deck[m_randomSuit][m_randomRank].GetValue();
}

//for replayability purposes
void Deck::ResetCards()
{
	for (int i = 0; i < m_maxSuit; i++)
	{
		for (int j = 0; j < m_maxRank; j++)
		{
			m_deck[i][j].SetIsTaken(false);
		}
	}
}

void Deck::CardTaken()
{
	//while the card is taken, give another card
	while (m_deck[m_randomSuit][m_randomRank].GetIsTaken() == true)
	{
		m_randomSuit = rand() % m_maxSuit;
		m_randomRank = rand() % m_maxRank;
	}
	//if the card is picked, set to 'taken'
	m_deck[m_randomSuit][m_randomRank].SetIsTaken(true);
}
