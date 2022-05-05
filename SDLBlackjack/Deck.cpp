#include "Deck.h"
#include <time.h>
#include <string>
#include <iostream>

Deck::Deck()
{
	m_cardSprite.Load("Assets/Images/MainGame/DeckOfCardsPixel.png");
	m_cardSprite.SetSpriteDimension({ 126, 170 }); //on screen
	m_cardSprite.SetImageDimension(13, 4, { 1638, 680 }); //original file
	
	//changing variable from time_t to unsigned int because of a warning "Possible loss of data"
	srand(unsigned int(time(0)));

	m_randomSuit = 0;
	m_randomRank = 0;

	m_rankCounter = 1;
	m_rank = 0;
	m_value = 0;
	
	for (int i = 0; i < M_MAXSUIT; i++)
	{
		for (int j = 0; j < M_MAXRANK; j++)
		{
			m_deck[i][j].SetIsTaken(false);
			m_deck[i][j].SetSuit(static_cast<Cards::Suit>(i));
			m_deck[i][j].SetRank(static_cast<Cards::Rank>(j + 2));
			m_cardSprite.SetImageCel(j + 1, i + 1);
			m_deck[i][j].SetImage(m_cardSprite);

			//(j+2) instead of j, because Rank enums start from 2 and the loops & matrices start from 0.
			if ((j + 2) > static_cast<int>(Cards::Rank::Ten) && (j + 2) != static_cast<int>(Cards::Rank::Ace))
			{
				m_deck[i][j].SetValue(static_cast<int>(Cards::Rank::Ten));
			}
			//ace default value is 11
			else if ((j + 2) == static_cast<int>(Cards::Rank::Ace))
			{
				m_deck[i][j].SetValue(static_cast<int>(Cards::Rank::Jack));
			}
			//the rest values
			else
			{
				m_deck[i][j].SetValue((j + 2));
			}
		}
	}
}

Deck::~Deck()
{
	m_cardSprite.Unload();
}

void Deck::SetRandomSuit()
{
	m_randomSuit = rand() % M_MAXSUIT;
}

void Deck::SetRandomRank()
{
	m_randomRank = rand() % M_MAXRANK + 2;
}

int Deck::GetValue()
{
	return m_deck[m_randomSuit][m_randomRank].GetValue();
}

//for replayability purposes
void Deck::ResetCards()
{
	for (int i = 0; i < M_MAXSUIT; i++)
	{
		for (int j = 0; j < M_MAXRANK; j++)
		{
			m_deck[i][j].SetIsTaken(false);
		}
	}
}

Cards Deck::GetCard()
{
	SetRandomSuit();
	SetRandomRank();
	CardTaken();
	return m_selectedCard;
}

bool Deck::CardTaken()
{
	//while the card is taken, give another card
	while (m_deck[m_randomSuit][m_randomRank].GetIsTaken() == true)
	{
		m_randomSuit = rand() % M_MAXSUIT;
		m_randomRank = rand() % M_MAXRANK;
	}
	//if the card is picked, set to 'taken'
	//m_deck[m_randomSuit][m_randomRank].SetIsTaken(true);

	m_selectedCard = m_deck[m_randomSuit][m_randomRank];
	m_selectedCard.SetIsTaken(true);
	return true;
}
