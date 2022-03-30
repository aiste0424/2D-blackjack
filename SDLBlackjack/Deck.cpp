#include "Deck.h"
#include <time.h>
#include <string>
#include <iostream>

Deck::Deck()
{
	m_sprite.Load("Assets/Images/DeckOfCards.png");
	m_sprite.SetSpriteDimension(148, 230); //on screen
	m_sprite.SetImageDimension(13, 5, 1924, 1150); //original file
	
	//changing variable from time_t to unsigned int because of a warning "Possible loss of data"
	srand(unsigned int(time(0)));

	m_randomSuit = 0;
	m_randomRank = 0;

	m_rankCounter = 1;
	m_rank = 0;
	m_value = 0;
	for (int i = 1; i <= m_maxSuit; i++)
	{
		for (int j = 1; j <= m_maxRank; j++)
		{
			m_deck[i][j].SetIsTaken(false);
			m_deck[i][j].SetSuit(static_cast<Cards::Suit>(i));
			m_deck[i][j].SetRank(static_cast<Cards::Rank>((j)));

			if (j > static_cast<int>(Cards::Rank::Ten))
			{
				m_deck[i][j].SetValue(static_cast<int>(Cards::Rank::Ten));
			}
			else if (j == 1) //Ace default value is 11
			{
				m_deck[i][j].SetValue(11);
			}
			//the rest of the values
			else
			{
				m_deck[i][j].SetValue((j));
			}
			std::cout << m_deck[i][j].GetValue() << std::endl;
		}
	}
}

Deck::~Deck()
{
	m_sprite.Unload();
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
	m_sprite.SetImageCel(m_randomRank, m_randomSuit);
}

void Deck::RenderSprite()
{
	//m_sprite.Render(0, 0, 0.0);
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
