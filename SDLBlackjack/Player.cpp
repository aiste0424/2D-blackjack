#include "Player.h"
#include <iostream>

void Player::Initialize()
{
    //11 positions for 11 cards as 11 is max cards the player can get (for example 5x2 and ace)
    for (auto i = 0; i < 11; i++)
    {
        m_cardPositions.push_back(m_finalDestination);
        m_finalDestination.x += 120;
    }

    //Setting up the player's score counter
    m_score->SetPosition({ 20, 650 });
    m_score->SetDimension({ 200, 50 });
    m_score->SetScoreTextDimension();
    m_score->SetScore(0);

    m_deal.Load("DealAudio.ogg", "DealAudioPlayer");
    m_deal.SetSound("DealAudioPlayer");
    m_deal.SetVolume(1.0f);
}

void Player::AddCard(Cards& card)
{
    if (card.GetRank() == Cards::Rank::Ace)
    {
        if (m_score->GetScore() + card.GetValue() > 21)
        {
            card.SetValue(1);
        }
    }
    m_cards.push_back(card);
    m_cards.back().SetPosition({125, 266}); //the position of the deck image. The image will start moving from the deck.
    //Gets the card's value and adds it to the score which then updates on screen
    m_score->SetCardValue(m_cards.back().GetValue());
    m_score->UpdateScore();
    m_deal.Play();
}

bool Player::Update()
{
    //idk how I came up with this, but it works
    for (auto i = 0; i < m_cards.size(); i++)
    {
        if (m_isReadyToMove == true)
        {
            m_cards[i].SetCardState(Cards::CardState::Moving);
            m_isReadyToMove = false; //the next card cannot move until the one before is finished
        }
        //iterates through a vector of assigned positions for each card
        for (auto j = 0; j < m_cardPositions.size(); j++)
        {
            //if the cards' iterator is the same as the positions' iterator
            if (i == j)
            {
                //if the card is currently travelling
                if (m_cards[i].GetCardState() == Cards::CardState::Moving)
                {
                    //checks if the card's current x position does not equal its' assigned end goal position
                    if (m_cards[i].GetPosition().x != m_cardPositions[j].x)
                    {
                        //travel
                        m_cards[i].SetPosition({ m_cards[i].GetPosition().x + 5, m_cards[i].GetPosition().y });
                    }
                    //checks if the card's current y position does not equal its' assigned end goal position
                    else if (m_cards[i].GetPosition().y != m_cardPositions[j].y)
                    {
                        //travel
                        m_cards[i].SetPosition({ m_cards[i].GetPosition().x, m_cards[i].GetPosition().y + 4 });
                    }
                    //if the iterators are the same and the position equals to its assigned position, change's the
                    //card's state and it stops moving
                    else
                    {
                        m_cards[i].SetCardState(Cards::CardState::Finished);
                        m_isReadyToMove = true; //the next card is ready to move
                    }
                }
            } 
        }
    }

	return true;
}
//renders all the cards and the player's score
bool Player::Render()
{
    for (auto& m_cards : m_cards)
    {
        if (m_cards.GetCardState() != Cards::CardState::NoMovement)
        {
            m_cards.Render();
        }
    }
    
    m_score->Render();
	return true;
}
//checks if the mext card is allowed to start moving
bool Player::GetIsReadyToMove()
{
    return m_isReadyToMove;
}

Score* Player::GetScore()
{
    return m_score;
}

void Player::Reset()
{
    m_score->SetScore(0);
    m_cards.clear();
    m_isReadyToMove = true;
}

void Player::Unload()
{
    m_cards.clear();
    m_cardPositions.clear();
    m_score->Unload();
}