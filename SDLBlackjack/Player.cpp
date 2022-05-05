#include "Player.h"
#include <iostream>

void Player::DrawCard()
{
    m_score.SetCardValue(m_cards.back().GetValue());
    m_score.UpdateScore();
    m_score.PrintScore();
}

int Player::GetScore()
{
    return m_score.GetScore();
}

void Player::AddCard(const Cards& card)
{
    m_cards.push_back(card);
    m_positionIncrementX += 150;
    m_cards.back().SetPosition({m_positionIncrementX, 520});
}

Player::Choice Player::GetChoice()
{
	return m_choice;
}

void Player::ResetScore()
{
    m_score.SetScore(0);
}

bool Player::Update()
{
    for (auto& cards : m_cards)
    {
        if (cards.GetHasCardMoved() == true)
        {

        }
    }
	return true;
}

bool Player::Render()
{
    for (auto& cards : m_cards)
    {
        cards.Render();
    }
    
	return true;
}